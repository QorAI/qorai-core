/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/services/qor_ads/qor_ads_client_mojo_bridge.h"

#include <utility>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_info.h"
#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_value_util.h"
#include "qorai/components/qorai_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace qor_ads {

QorAdsClientMojoBridge::QorAdsClientMojoBridge(
    mojo::PendingAssociatedRemote<mojom::QorAdsClient>
        qor_ads_client_pending_associated_remote,
    mojo::PendingReceiver<mojom::QorAdsClientNotifier>
        qor_ads_client_notifier_pending_receiver)
    : qor_ads_client_notifier_impl_(
          std::move(qor_ads_client_notifier_pending_receiver)) {
  qor_ads_client_associated_remote_.Bind(
      std::move(qor_ads_client_pending_associated_remote));
  qor_ads_client_associated_remote_.reset_on_disconnect();
}

QorAdsClientMojoBridge::~QorAdsClientMojoBridge() = default;

void QorAdsClientMojoBridge::AddObserver(
    qorai_ads::AdsClientNotifierObserver* observer) {
  qor_ads_client_notifier_impl_.AddObserver(observer);
}

void QorAdsClientMojoBridge::RemoveObserver(
    qorai_ads::AdsClientNotifierObserver* observer) {
  qor_ads_client_notifier_impl_.RemoveObserver(observer);
}

void QorAdsClientMojoBridge::NotifyPendingObservers() {
  qor_ads_client_notifier_impl_.NotifyPendingObservers();
}

bool QorAdsClientMojoBridge::CanShowNotificationAdsWhileBrowserIsBackgrounded()
    const {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return false;
  }

  bool can_show = false;
  qor_ads_client_associated_remote_
      ->CanShowNotificationAdsWhileBrowserIsBackgrounded(&can_show);
  return can_show;
}

bool QorAdsClientMojoBridge::IsNetworkConnectionAvailable() const {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return false;
  }

  bool is_available = false;
  qor_ads_client_associated_remote_->IsNetworkConnectionAvailable(
      &is_available);
  return is_available;
}

bool QorAdsClientMojoBridge::IsBrowserActive() const {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return false;
  }

  bool is_browser_active = false;
  qor_ads_client_associated_remote_->IsBrowserActive(&is_browser_active);
  return is_browser_active;
}

bool QorAdsClientMojoBridge::IsBrowserInFullScreenMode() const {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return false;
  }

  bool is_browser_in_full_screen_mode = false;
  qor_ads_client_associated_remote_->IsBrowserInFullScreenMode(
      &is_browser_in_full_screen_mode);
  return is_browser_in_full_screen_mode;
}

void QorAdsClientMojoBridge::ShowNotificationAd(
    const qorai_ads::NotificationAdInfo& ad) {
  if (qor_ads_client_associated_remote_.is_bound()) {
    qor_ads_client_associated_remote_->ShowNotificationAd(
        qorai_ads::NotificationAdToValue(ad));
  }
}

bool QorAdsClientMojoBridge::CanShowNotificationAds() const {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return false;
  }

  bool can_show = false;
  qor_ads_client_associated_remote_->CanShowNotificationAds(&can_show);
  return can_show;
}

void QorAdsClientMojoBridge::CloseNotificationAd(
    const std::string& placement_id) {
  if (qor_ads_client_associated_remote_.is_bound()) {
    qor_ads_client_associated_remote_->CloseNotificationAd(placement_id);
  }
}

void OnUrlRequest(
    qorai_ads::UrlRequestCallback callback,
    const qorai_ads::mojom::UrlResponseInfoPtr mojom_url_response_ptr) {
  qorai_ads::mojom::UrlResponseInfo mojom_url_response;

  if (!mojom_url_response_ptr) {
    mojom_url_response.status_code = -1;
    std::move(callback).Run(mojom_url_response);
    return;
  }

  mojom_url_response.url = mojom_url_response_ptr->url;
  mojom_url_response.status_code = mojom_url_response_ptr->status_code;
  mojom_url_response.body = mojom_url_response_ptr->body;
  mojom_url_response.headers = mojom_url_response_ptr->headers;
  std::move(callback).Run(mojom_url_response);
}

void QorAdsClientMojoBridge::UrlRequest(
    qorai_ads::mojom::UrlRequestInfoPtr mojom_url_request,
    qorai_ads::UrlRequestCallback callback) {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    qorai_ads::mojom::UrlResponseInfo mojom_url_response;
    mojom_url_response.url = mojom_url_request->url;
    mojom_url_response.status_code = -1;
    std::move(callback).Run(mojom_url_response);
    return;
  }

  qor_ads_client_associated_remote_->UrlRequest(
      std::move(mojom_url_request),
      base::BindOnce(&OnUrlRequest, std::move(callback)));
}

void QorAdsClientMojoBridge::Save(const std::string& name,
                                  const std::string& value,
                                  qorai_ads::SaveCallback callback) {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    std::move(callback).Run(/*success*/ false);
    return;
  }

  qor_ads_client_associated_remote_->Save(name, value, std::move(callback));
}

void QorAdsClientMojoBridge::LoadResourceComponent(
    const std::string& id,
    int version,
    qorai_ads::LoadFileCallback callback) {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    std::move(callback).Run(base::File());
    return;
  }

  qor_ads_client_associated_remote_->LoadResourceComponent(id, version,
                                                           std::move(callback));
}

void QorAdsClientMojoBridge::GetSiteHistory(
    int max_count,
    int days_ago,
    qorai_ads::GetSiteHistoryCallback callback) {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    std::move(callback).Run({});
    return;
  }

  qor_ads_client_associated_remote_->GetSiteHistory(max_count, days_ago,
                                                    std::move(callback));
}

void QorAdsClientMojoBridge::Load(const std::string& name,
                                  qorai_ads::LoadCallback callback) {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    std::move(callback).Run(/*value*/ std::nullopt);
    return;
  }

  qor_ads_client_associated_remote_->Load(name, std::move(callback));
}

void QorAdsClientMojoBridge::ShowScheduledCaptcha(
    const std::string& payment_id,
    const std::string& captcha_id) {
  if (qor_ads_client_associated_remote_.is_bound()) {
    qor_ads_client_associated_remote_->ShowScheduledCaptcha(payment_id,
                                                            captcha_id);
  }
}

void QorAdsClientMojoBridge::Log(const char* file,
                                 int line,
                                 int verbose_level,
                                 const std::string& message) {
  if (qor_ads_client_associated_remote_.is_bound()) {
    qor_ads_client_associated_remote_->Log(file, line, verbose_level, message);
  }
}

bool QorAdsClientMojoBridge::FindProfilePref(const std::string& path) const {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return cached_profile_prefs_.contains(path);
  }

  bool value;
  if (!qor_ads_client_associated_remote_->FindProfilePref(path, &value)) {
    return cached_profile_prefs_.contains(path);
  }

  return value;
}

std::optional<base::Value> QorAdsClientMojoBridge::GetProfilePref(
    const std::string& path) {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return CachedProfilePrefValue(path);
  }

  std::optional<base::Value> value;
  if (!qor_ads_client_associated_remote_->GetProfilePref(path, &value)) {
    return CachedProfilePrefValue(path);
  }

  if (value) {
    cached_profile_prefs_[path] = value->Clone();
  } else {
    cached_profile_prefs_.erase(path);
  }

  return value;
}

void QorAdsClientMojoBridge::SetProfilePref(const std::string& path,
                                            base::Value value) {
  cached_profile_prefs_[path] = value.Clone();
  if (qor_ads_client_associated_remote_.is_bound()) {
    qor_ads_client_associated_remote_->SetProfilePref(path, std::move(value));
  }
}

void QorAdsClientMojoBridge::ClearProfilePref(const std::string& path) {
  cached_profile_prefs_.erase(path);
  if (qor_ads_client_associated_remote_.is_bound()) {
    qor_ads_client_associated_remote_->ClearProfilePref(path);
  }
}

bool QorAdsClientMojoBridge::HasProfilePrefPath(const std::string& path) const {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return cached_profile_prefs_.contains(path);
  }

  bool value = false;
  if (!qor_ads_client_associated_remote_->HasProfilePrefPath(path, &value)) {
    return cached_profile_prefs_.contains(path);
  }

  return value;
}

bool QorAdsClientMojoBridge::FindLocalStatePref(const std::string& path) const {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return cached_local_state_prefs_.contains(path);
  }

  bool value;
  if (!qor_ads_client_associated_remote_->FindLocalStatePref(path, &value)) {
    return cached_local_state_prefs_.contains(path);
  }

  return value;
}

std::optional<base::Value> QorAdsClientMojoBridge::GetLocalStatePref(
    const std::string& path) {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return CachedLocalStatePrefValue(path);
  }

  std::optional<base::Value> value;
  if (!qor_ads_client_associated_remote_->GetLocalStatePref(path, &value)) {
    return CachedLocalStatePrefValue(path);
  }

  if (value) {
    cached_local_state_prefs_[path] = value->Clone();
  } else {
    cached_local_state_prefs_.erase(path);
  }

  return value;
}

void QorAdsClientMojoBridge::SetLocalStatePref(const std::string& path,
                                               base::Value value) {
  cached_local_state_prefs_[path] = value.Clone();
  if (qor_ads_client_associated_remote_.is_bound()) {
    qor_ads_client_associated_remote_->SetLocalStatePref(path,
                                                         std::move(value));
  }
}

void QorAdsClientMojoBridge::ClearLocalStatePref(const std::string& path) {
  cached_local_state_prefs_.erase(path);
  if (qor_ads_client_associated_remote_.is_bound()) {
    qor_ads_client_associated_remote_->ClearLocalStatePref(path);
  }
}

bool QorAdsClientMojoBridge::HasLocalStatePrefPath(
    const std::string& path) const {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return cached_local_state_prefs_.contains(path);
  }

  bool value = false;
  if (!qor_ads_client_associated_remote_->HasLocalStatePrefPath(path, &value)) {
    return cached_local_state_prefs_.contains(path);
  }

  return value;
}

base::Value::Dict QorAdsClientMojoBridge::GetVirtualPrefs() const {
  if (!qor_ads_client_associated_remote_.is_bound()) {
    return {};
  }

  base::Value::Dict virtual_prefs;
  qor_ads_client_associated_remote_->GetVirtualPrefs(&virtual_prefs);
  return virtual_prefs;
}

///////////////////////////////////////////////////////////////////////////////

std::optional<base::Value> QorAdsClientMojoBridge::CachedProfilePrefValue(
    const std::string& path) const {
  if (!cached_profile_prefs_.contains(path)) {
    return std::nullopt;
  }

  return cached_profile_prefs_.at(path).Clone();
}

std::optional<base::Value> QorAdsClientMojoBridge::CachedLocalStatePrefValue(
    const std::string& path) const {
  if (!cached_local_state_prefs_.contains(path)) {
    return std::nullopt;
  }

  return cached_local_state_prefs_.at(path).Clone();
}

}  // namespace qor_ads
