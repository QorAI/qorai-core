/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"

#include <utility>

#include "base/check.h"
#include "base/containers/fixed_flat_map.h"
#include "base/feature_list.h"
#include "base/json/json_writer.h"
#include "base/json/values_util.h"
#include "base/notreached.h"
#include "base/strings/string_split.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_constants.h"
#include "qorai/components/qorai_vpn/common/features.h"
#include "qorai/components/qorai_vpn/common/pref_names.h"
#include "qorai/components/p3a_utils/feature_usage.h"
#include "qorai/components/skus/browser/skus_utils.h"
#include "qorai/components/skus/common/features.h"
#include "build/build_config.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "components/version_info/channel.h"
#include "url/gurl.h"

namespace qorai_vpn {

namespace {

void RegisterVPNLocalStatePrefs(PrefRegistrySimple* registry) {
#if !BUILDFLAG(IS_ANDROID)
  registry->RegisterListPref(prefs::kQoraiVPNRegionList);
  registry->RegisterIntegerPref(prefs::kQoraiVPNRegionListVersion, 1);
  registry->RegisterTimePref(prefs::kQoraiVPNRegionListFetchedDate, {});
  registry->RegisterStringPref(prefs::kQoraiVPNDeviceRegion, "");
  registry->RegisterStringPref(prefs::kQoraiVPNSelectedRegion, "");
  registry->RegisterStringPref(prefs::kQoraiVPNSelectedRegionV2, "");
#endif
  registry->RegisterStringPref(prefs::kQoraiVPNEnvironment,
                               skus::GetDefaultEnvironment());
  registry->RegisterStringPref(prefs::kQoraiVPNWireguardProfileCredentials, "");
  registry->RegisterDictionaryPref(prefs::kQoraiVPNRootPref);
  registry->RegisterDictionaryPref(prefs::kQoraiVPNSubscriberCredential);
  registry->RegisterTimePref(prefs::kQoraiVPNLastCredentialExpiry, {});
  registry->RegisterBooleanPref(prefs::kQoraiVPNLocalStateMigrated, false);
  registry->RegisterTimePref(prefs::kQoraiVPNSessionExpiredDate, {});
#if BUILDFLAG(ENABLE_QORAI_VPN_WIREGUARD)
  registry->RegisterBooleanPref(prefs::kQoraiVPNWireguardEnabled, false);
#endif
#if BUILDFLAG(IS_MAC)
  registry->RegisterBooleanPref(prefs::kQoraiVPNOnDemandEnabled, false);
#endif
  registry->RegisterBooleanPref(prefs::kQoraiVPNSmartProxyRoutingEnabled, true);
  registry->RegisterListPref(prefs::kQoraiVPNWidgetUsageWeeklyStorage);
  registry->RegisterListPref(prefs::kQoraiVPNConnectedMinutesWeeklyStorage);
}

#if !BUILDFLAG(IS_ANDROID)
// Region name map between v1 and v2. Some region from region list v2
// uses different name with v1. If previously selected region name
// uses different with v2, we can't proper region with it. So, map
// v1 name to v2's.
constexpr auto kV1ToV2Map =
    base::MakeFixedFlatMap<std::string_view, std::string_view>(
        {{"au-au", "ocn-aus"},      {"eu-at", "eu-at"},
         {"eu-be", "eu-be"},        {"sa-brazil", "sa-brz"},
         {"ca-east", "na-can"},     {"sa-cl", "sa-cl"},
         {"sa-colombia", "sa-co"},  {"eu-cr", "eu-cr"},
         {"eu-cz", "eu-cz"},        {"eu-dk", "eu-dk"},
         {"eu-fr", "eu-fr"},        {"eu-de", "eu-de"},
         {"eu-gr", "eu-gr"},        {"eu-ir", "eu-ie"},
         {"eu-italy", "eu-it"},     {"asia-jp", "asia-jp"},
         {"sa-mexico", "sa-mx"},    {"eu-nl", "eu-nl"},
         {"eu-pl", "eu-pl"},        {"eu-pt", "eu-pt"},
         {"eu-ro", "eu-ro"},        {"asia-sg", "asia-sg"},
         {"af-za", "af-za"},        {"eu-es", "eu-es"},
         {"eu-sweden", "eu-se"},    {"eu-ch", "eu-ch"},
         {"us-central", "na-usa"},  {"us-east", "na-usa"},
         {"us-mountain", "na-usa"}, {"us-north-west", "na-usa"},
         {"us-west", "na-usa"},     {"eu-ua", "eu-ua"},
         {"eu-en", "eu-en"}});

void MigrateFromV1ToV2(PrefService* local_prefs) {
  const auto selected_region_v1 =
      local_prefs->GetString(prefs::kQoraiVPNSelectedRegion);
  // Don't need to migrate if user doesn't select region explicitly.
  // We'll pick proper region instead if not yet selected.
  if (selected_region_v1.empty()) {
    local_prefs->SetInteger(prefs::kQoraiVPNRegionListVersion, 2);
    return;
  }

  // In this migration, selected region name is updated to matched v2's country
  // name.
  if (kV1ToV2Map.contains(selected_region_v1)) {
    local_prefs->SetString(prefs::kQoraiVPNSelectedRegionV2,
                           kV1ToV2Map.at(selected_region_v1));
  }

  local_prefs->SetInteger(prefs::kQoraiVPNRegionListVersion, 2);
}
#endif

}  // namespace

bool IsQoraiVPNWireguardEnabled(PrefService* local_state) {
  if (!IsQoraiVPNFeatureEnabled()) {
    return false;
  }

#if BUILDFLAG(ENABLE_QORAI_VPN_WIREGUARD)
  auto enabled = local_state->GetBoolean(prefs::kQoraiVPNWireguardEnabled);
#if BUILDFLAG(IS_MAC)
  enabled = enabled && base::FeatureList::IsEnabled(
                           qorai_vpn::features::kQoraiVPNEnableWireguardForOSX);
#endif  // BUILDFLAG(IS_MAC)
  return enabled;
#else
  return false;
#endif
}

#if BUILDFLAG(IS_WIN)
void EnableWireguardIfPossible(PrefService* local_prefs) {
  auto* wireguard_enabled_pref =
      local_prefs->FindPreference(prefs::kQoraiVPNWireguardEnabled);
  if (wireguard_enabled_pref && wireguard_enabled_pref->IsDefaultValue()) {
    local_prefs->SetBoolean(
        prefs::kQoraiVPNWireguardEnabled,
        base::FeatureList::IsEnabled(features::kQoraiVPNUseWireguardService));
  }
}
#endif  // BUILDFLAG(IS_WIN)

GURL GetManageURLForUIType(mojom::ManageURLType type, const GURL& manage_url) {
  CHECK(manage_url.is_valid());

  switch (type) {
    case mojom::ManageURLType::CHECKOUT: {
      std::string query = "intent=checkout&product=vpn";
      GURL::Replacements replacements;
      replacements.SetQueryStr(query);
      return manage_url.ReplaceComponents(replacements);
    }
    case mojom::ManageURLType::RECOVER: {
      std::string query = "intent=recover&product=vpn";
      GURL::Replacements replacements;
      replacements.SetQueryStr(query);
      return manage_url.ReplaceComponents(replacements);
    }
    case mojom::ManageURLType::PRIVACY:
      return GURL("https://qorai.com/privacy/browser/#vpn");
    case mojom::ManageURLType::ABOUT:
      return GURL(qorai_vpn::kAboutUrl);
    case mojom::ManageURLType::MANAGE:
      return manage_url;
    case mojom::ManageURLType::ABOUT_SMART_PROXY:
      return GURL(
          "https://support.qorai.app/hc/en-us/articles/"
          "32105253704333-What-is-Smart-Proxy-Routing");
    default:
      break;
  }

  NOTREACHED();
}

void MigrateVPNSettings(PrefService* profile_prefs, PrefService* local_prefs) {
  if (local_prefs->GetBoolean(prefs::kQoraiVPNLocalStateMigrated)) {
    return;
  }

  if (!profile_prefs->HasPrefPath(prefs::kQoraiVPNRootPref)) {
    local_prefs->SetBoolean(prefs::kQoraiVPNLocalStateMigrated, true);
    return;
  }
  base::Value::Dict obsolete_pref =
      profile_prefs->GetDict(prefs::kQoraiVPNRootPref).Clone();
  base::Value::Dict result;
  if (local_prefs->HasPrefPath(prefs::kQoraiVPNRootPref)) {
    result = local_prefs->GetDict(prefs::kQoraiVPNRootPref).Clone();
    auto& result_dict = result;
    result_dict.Merge(std::move(obsolete_pref));
  } else {
    result = std::move(obsolete_pref);
  }
  // Do not migrate qorai_vpn::prefs::kQoraiVPNShowButton, we want it to be
  // inside the profile preferences.
  auto tokens =
      base::SplitString(qorai_vpn::prefs::kQoraiVPNShowButton, ".",
                        base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);
  if (result.FindBool(tokens.back())) {
    result.Remove(tokens.back());
  }
  local_prefs->Set(prefs::kQoraiVPNRootPref, base::Value(std::move(result)));
  local_prefs->SetBoolean(prefs::kQoraiVPNLocalStateMigrated, true);

  bool show_button =
      profile_prefs->GetBoolean(qorai_vpn::prefs::kQoraiVPNShowButton);
  profile_prefs->ClearPref(prefs::kQoraiVPNRootPref);
  // Set kQoraiVPNShowButton back, it is only one per profile preference for
  // now.
  profile_prefs->SetBoolean(qorai_vpn::prefs::kQoraiVPNShowButton, show_button);
}

bool IsQoraiVPNDisabledByPolicy(PrefService* prefs) {
  DCHECK(prefs);
  return prefs->FindPreference(prefs::kManagedQoraiVPNDisabled) &&
  // Need to investigate more about this.
  // IsManagedPreference() gives false on macOS when it's configured by
  // "defaults write com.qorai.Browser.beta QoraiVPNDisabled -bool true".
  // As kManagedQoraiVPNDisabled is false by default and only can be set
  // by policy, I think skipping this condition checking will be fine.
#if !BUILDFLAG(IS_MAC)
         prefs->IsManagedPreference(prefs::kManagedQoraiVPNDisabled) &&
#endif
         prefs->GetBoolean(prefs::kManagedQoraiVPNDisabled);
}

bool IsQoraiVPNFeatureEnabled() {
  return base::FeatureList::IsEnabled(qorai_vpn::features::kQoraiVPN) &&
         base::FeatureList::IsEnabled(skus::features::kSkusFeature);
}

bool IsQoraiVPNEnabled(PrefService* prefs) {
  return !IsQoraiVPNDisabledByPolicy(prefs) && IsQoraiVPNFeatureEnabled();
}

std::string GetQoraiVPNEntryName(version_info::Channel channel) {
  constexpr char kQoraiVPNEntryName[] = "QoraiVPN";

  const std::string entry_name(kQoraiVPNEntryName);
  switch (channel) {
    case version_info::Channel::UNKNOWN:
      return entry_name + "Development";
    case version_info::Channel::CANARY:
      return entry_name + "Nightly";
    case version_info::Channel::DEV:
      return entry_name + "Dev";
    case version_info::Channel::BETA:
      return entry_name + "Beta";
    case version_info::Channel::STABLE:
      return entry_name;
    default:
      return entry_name;
  }
}

std::string GetManageUrl(const std::string& env) {
  if (env == skus::kEnvProduction) {
    return qorai_vpn::kManageUrlProd;
  }
  if (env == skus::kEnvStaging) {
    return qorai_vpn::kManageUrlStaging;
  }
  if (env == skus::kEnvDevelopment) {
    return qorai_vpn::kManageUrlDev;
  }

  NOTREACHED() << "All env handled above.";
}

// On desktop, the environment is tied to SKUs because you would purchase it
// from `account.qorai.com` (or similar, based on env). The credentials for VPN
// will always be in the same environment as the SKU environment.
//
// When the vendor receives a credential from us during auth, it also includes
// the environment. The vendor then can do a lookup using Payment Service.
std::string GetQoraiVPNPaymentsEnv(const std::string& env) {
  // Use same string as payment env.
  return env;
}

void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(prefs::kManagedQoraiVPNDisabled, false);
  registry->RegisterDictionaryPref(prefs::kQoraiVPNRootPref);
  registry->RegisterBooleanPref(prefs::kQoraiVPNShowButton, true);
#if BUILDFLAG(IS_WIN)
  registry->RegisterBooleanPref(prefs::kQoraiVPNShowNotificationDialog, true);
  registry->RegisterBooleanPref(prefs::kQoraiVPNWireguardFallbackDialog, true);
#endif
#if BUILDFLAG(IS_ANDROID)
  registry->RegisterStringPref(prefs::kQoraiVPNPurchaseTokenAndroid, "");
  registry->RegisterStringPref(prefs::kQoraiVPNPackageAndroid, "");
  registry->RegisterStringPref(prefs::kQoraiVPNProductIdAndroid, "");
#endif
}

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  p3a_utils::RegisterFeatureUsagePrefs(
      registry, prefs::kQoraiVPNFirstUseTime, prefs::kQoraiVPNLastUseTime,
      prefs::kQoraiVPNUsedSecondDay, prefs::kQoraiVPNDaysInMonthUsed, nullptr);
  RegisterVPNLocalStatePrefs(registry);
}

void MigrateLocalStatePrefs(PrefService* local_prefs) {
#if !BUILDFLAG(IS_ANDROID)
  const int current_version =
      local_prefs->GetInteger(prefs::kQoraiVPNRegionListVersion);
  if (current_version == 1) {
    MigrateFromV1ToV2(local_prefs);
  }
#endif
}

bool HasValidSubscriberCredential(PrefService* local_prefs) {
  const base::Value::Dict& sub_cred_dict =
      local_prefs->GetDict(prefs::kQoraiVPNSubscriberCredential);
  if (sub_cred_dict.empty()) {
    return false;
  }

  const std::string* cred = sub_cred_dict.FindString(kSubscriberCredentialKey);
  const base::Value* expiration_time_value =
      sub_cred_dict.Find(kSubscriberCredentialExpirationKey);

  if (!cred || !expiration_time_value) {
    return false;
  }

  if (cred->empty()) {
    return false;
  }

  auto expiration_time = base::ValueToTime(expiration_time_value);
  if (!expiration_time || expiration_time < base::Time::Now()) {
    return false;
  }

  return true;
}

std::string GetSubscriberCredential(PrefService* local_prefs) {
  if (!HasValidSubscriberCredential(local_prefs)) {
    return "";
  }
  const base::Value::Dict& sub_cred_dict =
      local_prefs->GetDict(prefs::kQoraiVPNSubscriberCredential);
  const std::string* cred = sub_cred_dict.FindString(kSubscriberCredentialKey);
  DCHECK(cred);
  return *cred;
}

bool HasValidSkusCredential(PrefService* local_prefs) {
  const base::Value::Dict& sub_cred_dict =
      local_prefs->GetDict(prefs::kQoraiVPNSubscriberCredential);
  if (sub_cred_dict.empty()) {
    return false;
  }

  const std::string* skus_cred = sub_cred_dict.FindString(kSkusCredentialKey);
  const base::Value* expiration_time_value =
      sub_cred_dict.Find(kSubscriberCredentialExpirationKey);

  if (!skus_cred || !expiration_time_value) {
    return false;
  }

  if (skus_cred->empty()) {
    return false;
  }

  auto expiration_time = base::ValueToTime(expiration_time_value);
  if (!expiration_time || expiration_time < base::Time::Now()) {
    return false;
  }

  return true;
}

std::string GetSkusCredential(PrefService* local_prefs) {
  CHECK(HasValidSkusCredential(local_prefs))
      << "Don't call when there is no valid skus credential.";

  const base::Value::Dict& sub_cred_dict =
      local_prefs->GetDict(prefs::kQoraiVPNSubscriberCredential);
  const std::string* skus_cred = sub_cred_dict.FindString(kSkusCredentialKey);
  DCHECK(skus_cred);
  return *skus_cred;
}

}  // namespace qorai_vpn
