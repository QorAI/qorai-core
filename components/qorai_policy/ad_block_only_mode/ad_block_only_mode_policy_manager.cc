/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_policy/ad_block_only_mode/ad_block_only_mode_policy_manager.h"

#include "base/feature_list.h"
#include "base/no_destructor.h"
#include "qorai/components/qorai_policy/ad_block_only_mode/buildflags/buildflags.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_shields/core/common/pref_names.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/policy/policy_constants.h"
#include "components/prefs/pref_service.h"

namespace qorai_policy {

// static
AdBlockOnlyModePolicyManager* AdBlockOnlyModePolicyManager::GetInstance() {
  static base::NoDestructor<AdBlockOnlyModePolicyManager> instance;
  return instance.get();
}

void AdBlockOnlyModePolicyManager::Init(PrefService* local_state) {
  CHECK(local_state) << "AdBlockOnlyModePolicyManager local state should exist";

  local_state_ = local_state;

  pref_change_registrar_.Init(local_state_);
  pref_change_registrar_.Add(
      qorai_shields::prefs::kAdBlockOnlyModeEnabled,
      base::BindRepeating(
          &AdBlockOnlyModePolicyManager::OnAdBlockOnlyModeChanged,
          base::Unretained(this)));

  OnAdBlockOnlyModeChanged();
}

void AdBlockOnlyModePolicyManager::Shutdown() {
  pref_change_registrar_.RemoveAll();
  observers_.Clear();
  local_state_ = nullptr;
}

void AdBlockOnlyModePolicyManager::AddObserver(QoraiPolicyObserver* observer) {
  observers_.AddObserver(observer);

  if (local_state_) {
    // Notify the observer to fetch Ad Block Only mode policies.
    observer->OnQoraiPoliciesReady();
  }
}

void AdBlockOnlyModePolicyManager::RemoveObserver(
    QoraiPolicyObserver* observer) {
  observers_.RemoveObserver(observer);
}

AdBlockOnlyModePolicies AdBlockOnlyModePolicyManager::GetPolicies() const {
  if (!base::FeatureList::IsEnabled(
          qorai_shields::features::kAdblockOnlyMode)) {
    return {};
  }

  if (!local_state_ || !local_state_->GetBoolean(
                           qorai_shields::prefs::kAdBlockOnlyModeEnabled)) {
    return {};
  }

  return GetPoliciesImpl();
}

AdBlockOnlyModePolicyManager::AdBlockOnlyModePolicyManager() = default;

AdBlockOnlyModePolicyManager::~AdBlockOnlyModePolicyManager() = default;

void AdBlockOnlyModePolicyManager::OnAdBlockOnlyModeChanged() {
  observers_.Notify(&QoraiPolicyObserver::OnQoraiPoliciesReady);
}

AdBlockOnlyModePolicies AdBlockOnlyModePolicyManager::GetPoliciesImpl() const {
#if BUILDFLAG(ENABLE_AD_BLOCK_ONLY_MODE_POLICIES)
  AdBlockOnlyModePolicies policies;

  // Allow JavaScript globally.
  policies.emplace(policy::key::kDefaultJavaScriptSetting,
                   base::Value(CONTENT_SETTING_ALLOW));

  // Allow all cookies.
  policies.emplace(policy::key::kDefaultCookiesSetting,
                   base::Value(CONTENT_SETTING_ALLOW));

  // Do not block third-party cookies.
  policies.emplace(policy::key::kBlockThirdPartyCookies, base::Value(false));

  // Disable Qorai Fingerprinting protection.
  policies.emplace(policy::key::kDefaultQoraiFingerprintingV2Setting,
                   base::Value(CONTENT_SETTING_ALLOW));

  // Disable language fingerprinting reduction.
  policies.emplace(policy::key::kQoraiReduceLanguageEnabled,
                   base::Value(false));

  // Disable De-AMP.
  policies.emplace(policy::key::kQoraiDeAmpEnabled, base::Value(false));

  // Disable URL debouncing.
  policies.emplace(policy::key::kQoraiDebouncingEnabled, base::Value(false));

  // Disable Qorai Tracking Query Parameters Filtering.
  policies.emplace(policy::key::kQoraiTrackingQueryParametersFilteringEnabled,
                   base::Value(false));

  // Disable Qorai Global Privacy Control.
  policies.emplace(policy::key::kQoraiGlobalPrivacyControlEnabled,
                   base::Value(false));

  return policies;
#else
  return {};
#endif  // BUILDFLAG(ENABLE_AD_BLOCK_ONLY_MODE_POLICIES)
}

}  // namespace qorai_policy
