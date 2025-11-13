/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"

#include <algorithm>
#include <optional>

#include "base/base64.h"
#include "base/check.h"
#include "base/check_is_test.h"
#include "base/functional/bind.h"
#include "base/json/json_reader.h"
#include "base/json/json_writer.h"
#include "base/logging.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "base/time/time.h"
#include "qorai/components/qorai_vpn/browser/api/qorai_vpn_api_helper.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service_helper.h"
#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_region_data_helper.h"
#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_region_data_manager.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_constants.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "qorai/components/qorai_vpn/common/pref_names.h"
#include "qorai/components/skus/browser/skus_utils.h"
#include "qorai/components/version_info/version_info.h"
#include "components/grit/qorai_components_strings.h"
#include "components/prefs/pref_service.h"
#include "components/version_info/version_info.h"
#include "net/cookies/cookie_inclusion_status.h"
#include "net/cookies/cookie_util.h"
#include "net/cookies/parsed_cookie.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"
#include "ui/base/l10n/l10n_util.h"
#include "url/url_util.h"

namespace qorai_vpn {

using ConnectionState = mojom::ConnectionState;
using PurchasedState = mojom::PurchasedState;

QoraiVpnService::QoraiVpnService(
    QoraiVPNConnectionManager* connection_manager,
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
    PrefService* local_prefs,
    PrefService* profile_prefs,
    base::WeakPtr<misc_metrics::UptimeMonitor> uptime_monitor,
    base::RepeatingCallback<mojo::PendingRemote<skus::mojom::SkusService>()>
        skus_service_getter)
    : local_prefs_(local_prefs),
      profile_prefs_(profile_prefs),
      skus_service_getter_(skus_service_getter),
      api_request_(new QoraiVpnAPIRequest(url_loader_factory)),
      qorai_vpn_metrics_(local_prefs, profile_prefs, uptime_monitor, this) {
  DCHECK(IsQoraiVPNFeatureEnabled());
#if !BUILDFLAG(IS_ANDROID)
  DCHECK(connection_manager);
  connection_manager_ = connection_manager;
  observed_.Observe(connection_manager_);
  policy_pref_change_registrar_.Init(profile_prefs_);
  policy_pref_change_registrar_.Add(
      prefs::kManagedQoraiVPNDisabled,
      base::BindRepeating(&QoraiVpnService::OnPreferenceChanged,
                          base::Unretained(this)));

  smart_proxy_routing_enabled_.Init(
      prefs::kQoraiVPNSmartProxyRoutingEnabled, local_prefs_,
      base::BindRepeating(&QoraiVpnService::OnPreferenceChanged,
                          base::Unretained(this)));
#endif  // !BUILDFLAG(IS_ANDROID)

  CheckInitialState();
}

QoraiVpnService::~QoraiVpnService() = default;

bool QoraiVpnService::IsQoraiVPNEnabled() const {
  return ::qorai_vpn::IsQoraiVPNEnabled(profile_prefs_);
}

void QoraiVpnService::CheckInitialState() {
  if (HasValidSubscriberCredential(local_prefs_)) {
    ScheduleSubscriberCredentialRefresh();

#if BUILDFLAG(IS_ANDROID)
    SetPurchasedState(GetCurrentEnvironment(), PurchasedState::PURCHASED);
    // Android has its own region data managing logic.
#else
    if (connection_manager_->GetRegionDataManager().IsRegionDataReady()) {
      SetPurchasedState(GetCurrentEnvironment(), PurchasedState::PURCHASED);
    } else {
      SetPurchasedState(GetCurrentEnvironment(), PurchasedState::LOADING);
      // Not sure this can happen when user is already purchased user.
      // To make sure before set as purchased user, however, trying region fetch
      // and then set as a purchased user after we get valid region data.
      wait_region_data_ready_ = true;
    }
    connection_manager_->GetRegionDataManager().FetchRegionDataIfNeeded();
#endif
  } else if (HasValidSkusCredential(local_prefs_)) {
    // If we have valid skus creds during the startup, we can try to get subs
    // credential in advance.
    ReloadPurchasedState();
  } else {
    // Try to reload purchased state if cached credential is not valid because
    // it could be invalidated when not running.
    if (HasSubscriberCredential(local_prefs_)) {
      VLOG(2) << __func__ << " "
              << "Try to reload purchased as invalid credential is stored.";
      ClearSubscriberCredential(local_prefs_);
      ReloadPurchasedState();
    } else {
      ClearSubscriberCredential(local_prefs_);
    }
  }
}

#if BUILDFLAG(IS_ANDROID)
mojo::PendingRemote<qorai_vpn::mojom::ServiceHandler>
QoraiVpnService::MakeRemote() {
  mojo::PendingRemote<qorai_vpn::mojom::ServiceHandler> remote;
  receivers_.Add(this, remote.InitWithNewPipeAndPassReceiver());
  return remote;
}
#endif  // BUILDFLAG(IS_ANDROID)

std::string QoraiVpnService::GetCurrentEnvironment() const {
  return local_prefs_->GetString(prefs::kQoraiVPNEnvironment);
}

bool QoraiVpnService::is_purchased_user() const {
  return GetPurchasedInfoSync().state == mojom::PurchasedState::PURCHASED;
}

void QoraiVpnService::ReloadPurchasedState() {
  LoadPurchasedState(skus::GetDomain("vpn", GetCurrentEnvironment()));
}

void QoraiVpnService::BindInterface(
    mojo::PendingReceiver<mojom::ServiceHandler> receiver) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  receivers_.Add(this, std::move(receiver));
}

#if !BUILDFLAG(IS_ANDROID)
void QoraiVpnService::OnConnectionStateChanged(mojom::ConnectionState state) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  VLOG(2) << __func__ << " " << state;
#if BUILDFLAG(IS_WIN)
  if (delegate_) {
    delegate_->WriteConnectionState(state);
  }
#endif
  // Ignore connection state change request for non purchased user.
  // This can be happened when user controls vpn via os settings.
  if (!is_purchased_user()) {
    return;
  }

  if (state == ConnectionState::CONNECTED) {
    // If user connected vpn from the system and launched the browser
    // we detected it was disabled by policies and disabling it.
    if (IsQoraiVPNDisabledByPolicy(profile_prefs_)) {
      connection_manager_->Disconnect();
      return;
    }
#if BUILDFLAG(IS_WIN)
    // Run tray process each time we establish connection. System tray icon
    // manages self state to be visible/hidden due to settings.
    if (delegate_) {
      delegate_->ShowQoraiVpnStatusTrayIcon();
    }
#endif
    qorai_vpn_metrics_.RecordAllMetrics(true);
  }

  for (const auto& obs : observers_) {
    obs->OnConnectionStateChanged(state);
  }
}

void QoraiVpnService::OnRegionDataReady(bool success) {
  VLOG(2) << __func__ << " success - " << success << ", is waiting? "
          << wait_region_data_ready_;
  if (!wait_region_data_ready_) {
    return;
  }

  wait_region_data_ready_ = false;

  // Happened weird state while waiting region data.
  // Don't update purchased if current state is not loading state.
  if (GetPurchasedInfoSync().state != PurchasedState::LOADING) {
    return;
  }

  SetPurchasedState(GetCurrentEnvironment(), success ? PurchasedState::PURCHASED
                                                     : PurchasedState::FAILED);
}

void QoraiVpnService::OnSelectedRegionChanged(const std::string& region_name) {
  const auto region_ptr = GetRegionPtrWithNameFromRegionList(
      region_name, connection_manager_->GetRegionDataManager().GetRegions());
  region_ptr->is_automatic = IsCurrentRegionSelectedAutomatically(region_ptr);
  for (const auto& obs : observers_) {
    obs->OnSelectedRegionChanged(region_ptr.Clone());
  }
}

mojom::ConnectionState QoraiVpnService::GetConnectionState() const {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  return connection_manager_->GetConnectionState();
}

bool QoraiVpnService::IsConnected() const {
  if (!is_purchased_user()) {
    return false;
  }

  return GetConnectionState() == ConnectionState::CONNECTED;
}

void QoraiVpnService::Connect() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  if (!is_purchased_user()) {
    return;
  }

  connection_manager_->Connect();
}

void QoraiVpnService::Disconnect() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  if (!is_purchased_user()) {
    return;
  }

  connection_manager_->Disconnect();
}

void QoraiVpnService::ToggleConnection() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  if (!is_purchased_user()) {
    return;
  }

  connection_manager_->ToggleConnection();
}

void QoraiVpnService::GetConnectionState(GetConnectionStateCallback callback) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  const auto state = connection_manager_->GetConnectionState();
  VLOG(2) << __func__ << " : " << state;
  std::move(callback).Run(state);
}

void QoraiVpnService::GetSelectedRegion(GetSelectedRegionCallback callback) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  VLOG(2) << __func__;

  auto region_name =
      connection_manager_->GetRegionDataManager().GetSelectedRegion();
  auto region_ptr = GetRegionPtrWithNameFromRegionList(
      region_name, connection_manager_->GetRegionDataManager().GetRegions());
  region_ptr->is_automatic = IsCurrentRegionSelectedAutomatically(region_ptr);
  std::move(callback).Run(std::move(region_ptr));
}

void QoraiVpnService::SetSelectedRegion(mojom::RegionPtr region_ptr) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  VLOG(2) << __func__ << " : " << region_ptr->name;
  connection_manager_->SetSelectedRegion(region_ptr->name);
}

void QoraiVpnService::ClearSelectedRegion() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  connection_manager_->SetSelectedRegion("");
}

void QoraiVpnService::GetProductUrls(GetProductUrlsCallback callback) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  std::move(callback).Run(mojom::ProductUrls::New(
      kFeedbackUrl, kAboutUrl, GetManageUrl(GetCurrentEnvironment())));
}

void QoraiVpnService::CreateSupportTicket(
    const std::string& email,
    const std::string& subject,
    const std::string& body,
    CreateSupportTicketCallback callback) {
  auto internal_callback =
      base::BindOnce(&QoraiVpnService::OnCreateSupportTicket,
                     weak_ptr_factory_.GetWeakPtr(), std::move(callback));
  api_request_->CreateSupportTicket(
      std::move(internal_callback), email, subject, body,
      ::qorai_vpn::GetSubscriberCredential(local_prefs_));
}

void QoraiVpnService::GetSupportData(GetSupportDataCallback callback) {
  std::string qorai_version =
      version_info::GetQoraiVersionWithoutChromiumMajorVersion();

  std::move(callback).Run(qorai_version, std::string(version_info::GetOSType()),
                          connection_manager_->GetHostname(),
                          GetTimeZoneName());
}

void QoraiVpnService::ResetConnectionState() {
  connection_manager_->ResetConnectionState();
}

void QoraiVpnService::EnableOnDemand(bool enable) {
#if BUILDFLAG(IS_MAC)
  local_prefs_->SetBoolean(prefs::kQoraiVPNOnDemandEnabled, enable);

  // If not connected, do nothing because on-demand bit will
  // be applied when new connection starts. Whenever new connection starts,
  // we create os vpn entry.
  if (IsConnected()) {
    VLOG(2) << __func__ << " : reconnect to apply on-demand config(" << enable
            << "> to current connection";
    Connect();
  }
#endif
}

void QoraiVpnService::GetOnDemandState(GetOnDemandStateCallback callback) {
#if BUILDFLAG(IS_MAC)
  std::move(callback).Run(
      /*available*/ true,
      /*enabled*/ local_prefs_->GetBoolean(prefs::kQoraiVPNOnDemandEnabled));
#else
  std::move(callback).Run(false, false);
#endif
}

void QoraiVpnService::EnableSmartProxyRouting(bool enable) {
  local_prefs_->SetBoolean(prefs::kQoraiVPNSmartProxyRoutingEnabled, enable);

  // If not connected, do nothing because smart proxy routing bit will
  // be applied when new connection starts. Whenever new connection starts,
  // we create os vpn entry.
  if (IsConnected()) {
    VLOG(2) << __func__ << " : reconnect to apply smart proxy routing config("
            << enable << "> to current connection";
    Connect();
  }
}

void QoraiVpnService::GetSmartProxyRoutingState(
    GetSmartProxyRoutingStateCallback callback) {
  std::move(callback).Run(
      local_prefs_->GetBoolean(prefs::kQoraiVPNSmartProxyRoutingEnabled));
}

// NOTE(bsclifton): Desktop uses API to create a ticket.
// Android and iOS directly send an email.
void QoraiVpnService::OnCreateSupportTicket(
    CreateSupportTicketCallback callback,
    const std::string& ticket,
    bool success) {
  std::move(callback).Run(success, ticket);
}

void QoraiVpnService::OnPreferenceChanged(const std::string& pref_name) {
  if (pref_name == prefs::kManagedQoraiVPNDisabled) {
    if (IsQoraiVPNDisabledByPolicy(profile_prefs_)) {
      connection_manager_->Disconnect();
    }
    return;
  }

  if (pref_name == prefs::kQoraiVPNSmartProxyRoutingEnabled) {
    const bool enabled = smart_proxy_routing_enabled_.GetValue();
    for (const auto& obs : observers_) {
      obs->OnSmartProxyRoutingStateChanged(enabled);
    }
    return;
  }
}

void QoraiVpnService::UpdatePurchasedStateForSessionExpired(
    const std::string& env) {
  // Double check that we don't set session expired state for fresh user.
  if (!connection_manager_->GetRegionDataManager().IsRegionDataReady()) {
    VLOG(1) << __func__ << " : Treat it as not purchased state for fresh user.";
    SetPurchasedState(env, PurchasedState::NOT_PURCHASED);
    return;
  }

  // If expiry is in the future, the person ran out of credentials.
  // This should only happen if communication bewteen client and VPN provider
  // is lost after the credential is redeemed (multiple times).
  //
  // It's safe to check this first because kQoraiVPNLastCredentialExpiry is only
  // set after getting a valid credential. If the session is expired, this value
  // might be set but would be in the past.
  const auto last_credential_expiry =
      local_prefs_->GetTime(prefs::kQoraiVPNLastCredentialExpiry);
  if (!last_credential_expiry.is_null() &&
      last_credential_expiry > base::Time::Now()) {
    std::string expiry_message;
    base::TimeDelta delta = (last_credential_expiry - base::Time::Now());
    if (delta.InHours() == 0) {
      expiry_message = absl::StrFormat(
          "Out of credentials; check again in %d minutes.", delta.InMinutes());
    } else {
      int delta_hours = delta.InHours();
      base::TimeDelta delta_minutes = (delta - base::Hours(delta_hours));
      expiry_message = absl::StrFormat(
          "Out of credentials; check again in %d hours %d minutes.",
          delta_hours, delta_minutes.InMinutes());
    }
    VLOG(2) << __func__ << " : " << expiry_message;
    SetPurchasedState(env, PurchasedState::OUT_OF_CREDENTIALS,
                      l10n_util::GetStringUTF8(
                          IDS_QORAI_VPN_MAIN_PANEL_OUT_OF_CREDENTIALS_CONTENT));
    return;
  }

  const auto session_expired_time =
      local_prefs_->GetTime(prefs::kQoraiVPNSessionExpiredDate);
  // If it's not cached, it means this session expiration is first time since
  // last purchase because this cache is cleared when we get valid credential
  // summary.
  if (session_expired_time.is_null()) {
    local_prefs_->SetTime(prefs::kQoraiVPNSessionExpiredDate,
                          base::Time::Now());
    SetPurchasedState(env, PurchasedState::SESSION_EXPIRED);
    return;
  }

  // Weird state. Maybe we don't see this condition.
  // Just checking for safe.
  if (session_expired_time > base::Time::Now()) {
    SetPurchasedState(env, PurchasedState::NOT_PURCHASED);
    return;
  }

  // Keep session expired state 30 days at most.
  constexpr int kSessionExpiredCheckingDurationInDays = 30;
  if ((base::Time::Now() - session_expired_time).InDays() >
      kSessionExpiredCheckingDurationInDays) {
    SetPurchasedState(env, PurchasedState::NOT_PURCHASED);
    return;
  }

  // Expiry is in the past - they ran out of credentials completely.
  // They'll need to login to account.qorai.com again.
  SetPurchasedState(env, PurchasedState::SESSION_EXPIRED);
}

bool QoraiVpnService::IsCurrentRegionSelectedAutomatically(
    const qorai_vpn::mojom::RegionPtr& region) {
  const auto selected_region_name =
      local_prefs_->GetString(prefs::kQoraiVPNSelectedRegionV2);

  if (region->region_precision == qorai_vpn::mojom::kRegionPrecisionCountry &&
      selected_region_name.empty()) {
    return true;
  }

  return false;
}

#endif  // !BUILDFLAG(IS_ANDROID)

void QoraiVpnService::GetAllRegions(GetAllRegionsCallback callback) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
#if BUILDFLAG(IS_ANDROID)
  api_request_->GetServerRegions(
      base::BindOnce(&QoraiVpnService::OnFetchRegionList,
                     base::Unretained(this), std::move(callback)),
      qorai_vpn::mojom::kRegionPrecisionCityByCountry);
#else
  std::vector<mojom::RegionPtr> regions;
  for (const auto& region :
       connection_manager_->GetRegionDataManager().GetRegions()) {
    regions.push_back(region.Clone());
  }
  std::move(callback).Run(std::move(regions));
#endif
}

#if BUILDFLAG(IS_ANDROID)
void QoraiVpnService::OnFetchRegionList(GetAllRegionsCallback callback,
                                        const std::string& region_list,
                                        bool success) {
  std::optional<base::Value::List> value = base::JSONReader::ReadList(
      region_list, base::JSON_PARSE_CHROMIUM_EXTENSIONS);
  if (value) {
    auto new_regions = ParseRegionList(*value);
    std::vector<mojom::RegionPtr> regions;
    for (const auto& region : new_regions) {
      regions.push_back(region.Clone());
    }
    std::move(callback).Run(std::move(regions));
  }
}

void QoraiVpnService::GetPurchaseToken(GetPurchaseTokenCallback callback) {
  std::string purchase_token_string = "";
  std::string package_string = "com.qorai.browser";
  std::string product_id_string = "qorai-firewall-vpn-premium";

  // Get the Android purchase token (for Google Play Store).
  // The value for this is validated on the account.qorai.com side
  auto* purchase_token =
      profile_prefs_->FindPreference(prefs::kQoraiVPNPurchaseTokenAndroid);
  if (purchase_token && !purchase_token->IsDefaultValue()) {
    purchase_token_string =
        profile_prefs_->GetString(prefs::kQoraiVPNPurchaseTokenAndroid);
  }

  // Package name is important; for real users, it'll be the Release package.
  // For testing we do have the ability to use the Nightly package.
  auto* package =
      profile_prefs_->FindPreference(prefs::kQoraiVPNPackageAndroid);
  if (package && !package->IsDefaultValue()) {
    package_string = profile_prefs_->GetString(prefs::kQoraiVPNPackageAndroid);
  }

  auto* product_id =
      profile_prefs_->FindPreference(prefs::kQoraiVPNProductIdAndroid);
  if (product_id && !product_id->IsDefaultValue()) {
    product_id_string =
        profile_prefs_->GetString(prefs::kQoraiVPNProductIdAndroid);
  }

  base::Value::Dict response;
  response.Set("type", "android");
  response.Set("raw_receipt", purchase_token_string);
  response.Set("package", package_string);
  response.Set("subscription_id", product_id_string);

  std::string response_json;
  base::JSONWriter::Write(response, &response_json);
  std::move(callback).Run(base::Base64Encode(response_json));
}
#endif  // BUILDFLAG(IS_ANDROID)

void QoraiVpnService::AddObserver(
    mojo::PendingRemote<mojom::ServiceObserver> observer) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  observers_.Add(std::move(observer));
}

mojom::PurchasedInfo QoraiVpnService::GetPurchasedInfoSync() const {
  return purchased_state_.value_or(
      mojom::PurchasedInfo(mojom::PurchasedState::NOT_PURCHASED, std::nullopt));
}

void QoraiVpnService::GetPurchasedState(GetPurchasedStateCallback callback) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  std::move(callback).Run(GetPurchasedInfoSync().Clone());
}

void QoraiVpnService::LoadPurchasedState(const std::string& domain) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  if (!skus::DomainIsForProduct(domain, "vpn")) {
    VLOG(2) << __func__ << ": LoadPurchasedState called for non-vpn product";
    return;
  }

  auto requested_env = skus::GetEnvironmentForDomain(domain);
  if (GetCurrentEnvironment() == requested_env &&
      GetPurchasedInfoSync().state == PurchasedState::LOADING) {
    VLOG(2) << __func__ << ": Loading in-progress";
    return;
  }

  SetPurchasedState(requested_env, PurchasedState::LOADING);

  if (HasValidSubscriberCredential(local_prefs_)) {
#if BUILDFLAG(IS_ANDROID)
    SetPurchasedState(requested_env, PurchasedState::PURCHASED);
#else
    if (connection_manager_->GetRegionDataManager().IsRegionDataReady()) {
      VLOG(2) << __func__
              << ": Set as a purchased user as we have valid subscriber "
                 "credentials & region data";
      SetPurchasedState(requested_env, PurchasedState::PURCHASED);
    } else {
      VLOG(2) << __func__ << ": Wait till we get valid region data.";
      // TODO(simonhong): Make purchases state independent from region data.
      wait_region_data_ready_ = true;
    }
    connection_manager_->GetRegionDataManager().FetchRegionDataIfNeeded();
#endif
    return;
  }

  if (HasValidSkusCredential(local_prefs_)) {
    // We can reach here if we fail to get subscriber credential from guardian.
    VLOG(2) << __func__
            << " Try to get subscriber credential with valid cached skus "
               "credential.";

    if (GetCurrentEnvironment() != requested_env) {
      SetCurrentEnvironment(requested_env);
    }

    api_request_->GetSubscriberCredentialV12(
        base::BindOnce(&QoraiVpnService::OnGetSubscriberCredentialV12,
                       base::Unretained(this),
                       GetExpirationTimeForSkusCredential(local_prefs_)),
        GetSkusCredential(local_prefs_),
        GetQoraiVPNPaymentsEnv(GetCurrentEnvironment()));
    return;
  }

  VLOG(2) << __func__
          << ": Checking purchased state as we doesn't have valid skus or "
             "subscriber credentials";

  RequestCredentialSummary(domain);
}

void QoraiVpnService::RequestCredentialSummary(const std::string& domain) {
  // As we request new credential, clear cached value.
  ClearSubscriberCredential(local_prefs_);

  EnsureMojoConnected();
  skus_service_->CredentialSummary(
      domain, base::BindOnce(&QoraiVpnService::OnCredentialSummary,
                             base::Unretained(this), domain));
}

void QoraiVpnService::OnCredentialSummary(const std::string& domain,
                                          skus::mojom::SkusResultPtr summary) {
  if (!skus::DomainIsForProduct(domain, "vpn")) {
    VLOG(2) << __func__ << ": CredentialSummary called for non-vpn product";
    return;
  }

  auto env = skus::GetEnvironmentForDomain(domain);
  std::string summary_string_trimmed;
  base::TrimWhitespaceASCII(summary->message, base::TrimPositions::TRIM_ALL,
                            &summary_string_trimmed);
  if (summary_string_trimmed.length() == 0) {
    // no credential found; person needs to login
    VLOG(1) << __func__ << " : No credential found; user needs to login!";
    SetPurchasedState(env, PurchasedState::NOT_PURCHASED);
    return;
  }

  std::optional<base::Value::Dict> records = base::JSONReader::ReadDict(
      summary->message, base::JSONParserOptions::JSON_PARSE_RFC);

  // Early return when summary is invalid or it's empty dict.
  if (!records) {
    VLOG(1) << __func__ << " : Got invalid credential summary!";
    SetPurchasedState(env, PurchasedState::FAILED);
    return;
  }

  // Empty dict - clean user.
  if (records->empty()) {
    SetPurchasedState(env, PurchasedState::NOT_PURCHASED);
    return;
  }

  if (IsValidCredentialSummary(*records)) {
    VLOG(1) << __func__ << " : Active credential found!";
    // if a credential is ready, we can present it
    EnsureMojoConnected();
    skus_service_->PrepareCredentialsPresentation(
        domain, "*",
        base::BindOnce(&QoraiVpnService::OnPrepareCredentialsPresentation,
                       base::Unretained(this), domain));
#if !BUILDFLAG(IS_ANDROID)
    // Clear expired state data as we have active credentials.
    local_prefs_->SetTime(prefs::kQoraiVPNSessionExpiredDate, {});
#endif
  } else if (IsValidCredentialSummaryButNeedActivation(*records)) {
    // Need to activate from account. Treat as not purchased till activated.
    VLOG(1) << __func__ << " : Need to activate vpn from account.";
    SetPurchasedState(env, PurchasedState::NOT_PURCHASED);
  } else {
    // When reaches here, remained_credential is zero. We can treat it as
    // user's current purchase is expired.
    VLOG(1) << __func__ << " : don't have remained credential.";
#if BUILDFLAG(IS_ANDROID)
    VLOG(1) << __func__ << " : Treat it as not purchased state in android.";
    SetPurchasedState(env, PurchasedState::NOT_PURCHASED);
#else
    VLOG(1) << __func__ << " : Treat it as session expired state in desktop.";
    UpdatePurchasedStateForSessionExpired(env);
#endif
  }
}

void QoraiVpnService::OnPrepareCredentialsPresentation(
    const std::string& domain,
    skus::mojom::SkusResultPtr credential_as_cookie) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  auto env = skus::GetEnvironmentForDomain(domain);
  // Credential is returned in cookie format.
  net::CookieInclusionStatus status;
  net::ParsedCookie credential_cookie(credential_as_cookie->message, &status);
  // TODO(bsclifton): have a better check / logging.
  // should these failed states be considered NOT_PURCHASED?
  // or maybe it can be considered FAILED status?
  if (!credential_cookie.IsValid()) {
    VLOG(1) << __func__ << " : FAILED credential_cookie.IsValid";
    // TODO(simonhong): Set as NOT_PURCHASED.
    // It seems we're not using this state.
    SetPurchasedState(env, PurchasedState::FAILED);
    return;
  }
  if (!status.IsInclude()) {
    VLOG(1) << __func__ << " : FAILED status.IsInclude";
    SetPurchasedState(env, PurchasedState::FAILED);
    return;
  }

  if (!credential_cookie.Expires()) {
    VLOG(1) << __func__ << " : FAILED cookie doesn't have expired date.";
    SetPurchasedState(env, PurchasedState::FAILED);
    return;
  }

  // Credential value received needs to be URL decoded.
  // That leaves us with a Base64 encoded JSON blob which is the credential.
  const std::string encoded_credential = credential_cookie.Value();
  const auto time =
      net::cookie_util::ParseCookieExpirationTime(*credential_cookie.Expires());
  url::RawCanonOutputT<char16_t> unescaped;
  url::DecodeURLEscapeSequences(
      encoded_credential, url::DecodeURLMode::kUTF8OrIsomorphic, &unescaped);
  std::string credential;
  base::UTF16ToUTF8(unescaped.data(), unescaped.length(), &credential);
  if (credential.empty()) {
    SetPurchasedState(env, PurchasedState::NOT_PURCHASED);
    return;
  }

  // Early return when it's already expired.
  if (time < base::Time::Now()) {
    SetPurchasedState(
        GetCurrentEnvironment(), PurchasedState::FAILED,
        l10n_util::GetStringUTF8(IDS_QORAI_VPN_PURCHASE_CREDENTIALS_EXPIRED));
    return;
  }

  SetSkusCredential(local_prefs_, credential, time);

  if (GetCurrentEnvironment() != env) {
    // Change environment because we have successfully authorized with new one.
    SetCurrentEnvironment(env);
  }

  api_request_->GetSubscriberCredentialV12(
      base::BindOnce(&QoraiVpnService::OnGetSubscriberCredentialV12,
                     base::Unretained(this), time),
      credential, GetQoraiVPNPaymentsEnv(GetCurrentEnvironment()));
}

void QoraiVpnService::OnGetSubscriberCredentialV12(
    const base::Time& expiration_time,
    const std::string& subscriber_credential,
    bool success) {
  if (!success) {
    VLOG(2) << __func__ << " : failed to get subscriber credential";
#if BUILDFLAG(IS_ANDROID)
    SetPurchasedState(GetCurrentEnvironment(), PurchasedState::NOT_PURCHASED);
#else
    const bool token_no_longer_valid =
        subscriber_credential == kTokenNoLongerValid;

    // If we get an error "token no longer valid", this means the credential
    // has been consumed and is no good.
    //
    // We can try one more time to get a fresh credential (total of two tries).
    if (token_no_longer_valid && !IsRetriedSkusCredential(local_prefs_)) {
      VLOG(2) << __func__
              << " : Re-trying to fetch subscriber-credential by fetching "
                 "newer skus-credential.";
      RequestCredentialSummary(skus::GetDomain("vpn", GetCurrentEnvironment()));
      SetSkusCredentialFetchingRetried(local_prefs_, true);
      return;
    }

    // We can set the state as FAILED and do not attempt to get another
    // credential. The cached credential will eventually expire and user will
    // fetch a new one.
    //
    // There could be two reasons for this.

    // 1. We've already tried two credentials (the retry failed).
    if (token_no_longer_valid && IsRetriedSkusCredential(local_prefs_)) {
      VLOG(2) << __func__
              << " : Got TokenNoLongerValid again with retried skus credential";
      SetPurchasedState(
          GetCurrentEnvironment(), PurchasedState::FAILED,
          l10n_util::GetStringUTF8(IDS_QORAI_VPN_PURCHASE_TOKEN_NOT_VALID));
      return;
    }

    // 2. The cached credential is considered good but vendor side has an error.
    // That could be a network outage or a server side error on vendor side.
    SetPurchasedState(GetCurrentEnvironment(), PurchasedState::FAILED,
                      l10n_util::GetStringUTF8(
                          IDS_QORAI_VPN_PURCHASE_CREDENTIALS_FETCH_FAILED));
#endif
    return;
  }

  // Clear retrying flags as we got valid subscriber-credential.
  SetSkusCredentialFetchingRetried(local_prefs_, false);

  // Previously cached skus credential is cleared and fetched subscriber
  // credential is cached.
  SetSubscriberCredential(local_prefs_, subscriber_credential, expiration_time);

  // Launch one-shot timer for refreshing subscriber_credential before it's
  // expired.
  ScheduleSubscriberCredentialRefresh();

#if BUILDFLAG(IS_ANDROID)
  SetPurchasedState(GetCurrentEnvironment(), PurchasedState::PURCHASED);
#else
  if (connection_manager_->GetRegionDataManager().IsRegionDataReady()) {
    SetPurchasedState(GetCurrentEnvironment(), PurchasedState::PURCHASED);
  } else {
    wait_region_data_ready_ = true;
  }
  connection_manager_->GetRegionDataManager().FetchRegionDataIfNeeded();
#endif
}

void QoraiVpnService::ScheduleSubscriberCredentialRefresh() {
  if (subs_cred_refresh_timer_.IsRunning()) {
    subs_cred_refresh_timer_.Stop();
  }

  const auto expiration_time = GetExpirationTime(local_prefs_);
  if (!expiration_time) {
    return;
  }

  auto expiration_time_delta = *expiration_time - base::Time::Now();
  VLOG(2) << "Schedule subscriber credential fetching after "
          << expiration_time_delta;
  subs_cred_refresh_timer_.Start(
      FROM_HERE, expiration_time_delta,
      base::BindOnce(&QoraiVpnService::RefreshSubscriberCredential,
                     base::Unretained(this)));
}

void QoraiVpnService::RefreshSubscriberCredential() {
  VLOG(2) << "Refresh subscriber credential";

  // Clear current credentials to get newer one.
  ClearSubscriberCredential(local_prefs_);
  ReloadPurchasedState();
}

#if BUILDFLAG(IS_ANDROID)
void QoraiVpnService::RecordAndroidBackgroundP3A(int64_t session_start_time_ms,
                                                 int64_t session_end_time_ms) {
  qorai_vpn_metrics_.RecordAndroidBackgroundP3A(session_start_time_ms,
                                                session_end_time_ms);
}
#endif

void QoraiVpnService::SetPurchasedState(
    const std::string& env,
    PurchasedState state,
    const std::optional<std::string>& description) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  if (GetPurchasedInfoSync().state == state || env != GetCurrentEnvironment()) {
    return;
  }

  VLOG(2) << __func__ << " : " << state;
  purchased_state_ = mojom::PurchasedInfo(state, description);

  for (const auto& obs : observers_) {
    obs->OnPurchasedStateChanged(state, description);
  }

#if !BUILDFLAG(IS_ANDROID)
  if (state == PurchasedState::PURCHASED) {
    connection_manager_->CheckConnection();

    // Some platform needs to install services to run vpn.
    connection_manager_->MaybeInstallSystemServices();
  }
#endif
}

void QoraiVpnService::SetCurrentEnvironment(const std::string& env) {
  local_prefs_->SetString(prefs::kQoraiVPNEnvironment, env);
  purchased_state_.reset();
}

void QoraiVpnService::EnsureMojoConnected() {
  if (!skus_service_) {
    auto pending = skus_service_getter_.Run();
    skus_service_.Bind(std::move(pending));
  }
  DCHECK(skus_service_);
  skus_service_.set_disconnect_handler(base::BindOnce(
      &QoraiVpnService::OnMojoConnectionError, base::Unretained(this)));
}

void QoraiVpnService::OnMojoConnectionError() {
  skus_service_.reset();
  EnsureMojoConnected();
}

void QoraiVpnService::Shutdown() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  skus_service_.reset();
  observers_.Clear();
  api_request_.reset();
  subs_cred_refresh_timer_.Stop();

#if !BUILDFLAG(IS_ANDROID)
  observed_.Reset();
  receivers_.Clear();
#endif  // !BUILDFLAG(IS_ANDROID)
}

void QoraiVpnService::GetTimezonesForRegions(ResponseCallback callback) {
  api_request_->GetTimezonesForRegions(std::move(callback));
}

void QoraiVpnService::GetHostnamesForRegion(
    ResponseCallback callback,
    const std::string& region,
    const std::string& region_precision) {
  api_request_->GetHostnamesForRegion(std::move(callback), region,
                                      region_precision);
}

void QoraiVpnService::GetProfileCredentials(
    ResponseCallback callback,
    const std::string& subscriber_credential,
    const std::string& hostname) {
  api_request_->GetProfileCredentials(std::move(callback),
                                      subscriber_credential, hostname);
}

void QoraiVpnService::GetWireguardProfileCredentials(
    ResponseCallback callback,
    const std::string& subscriber_credential,
    const std::string& public_key,
    const std::string& hostname) {
  api_request_->GetWireguardProfileCredentials(
      std::move(callback), subscriber_credential, public_key, hostname);
}

void QoraiVpnService::VerifyCredentials(
    ResponseCallback callback,
    const std::string& hostname,
    const std::string& client_id,
    const std::string& subscriber_credential,
    const std::string& api_auth_token) {
  api_request_->VerifyCredentials(std::move(callback), hostname, client_id,
                                  subscriber_credential, api_auth_token);
}

void QoraiVpnService::InvalidateCredentials(
    ResponseCallback callback,
    const std::string& hostname,
    const std::string& client_id,
    const std::string& subscriber_credential,
    const std::string& api_auth_token) {
  api_request_->InvalidateCredentials(std::move(callback), hostname, client_id,
                                      subscriber_credential, api_auth_token);
}

void QoraiVpnService::VerifyPurchaseToken(ResponseCallback callback,
                                          const std::string& purchase_token,
                                          const std::string& product_id,
                                          const std::string& product_type,
                                          const std::string& bundle_id) {
  api_request_->VerifyPurchaseToken(std::move(callback), purchase_token,
                                    product_id, product_type, bundle_id);
}

void QoraiVpnService::GetSubscriberCredential(
    ResponseCallback callback,
    const std::string& product_type,
    const std::string& product_id,
    const std::string& validation_method,
    const std::string& purchase_token,
    const std::string& bundle_id) {
  api_request_->GetSubscriberCredential(std::move(callback), product_type,
                                        product_id, validation_method,
                                        purchase_token, bundle_id);
}

void QoraiVpnService::GetSubscriberCredentialV12(ResponseCallback callback) {
  // Caller can get valid subscriber credential only in purchased state.
  // Otherwise, false is passed to |callback| as success param.
  std::move(callback).Run(::qorai_vpn::GetSubscriberCredential(local_prefs_),
                          HasValidSubscriberCredential(local_prefs_));
}

}  // namespace qorai_vpn
