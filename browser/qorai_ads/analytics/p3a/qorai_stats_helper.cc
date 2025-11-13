/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_ads/analytics/p3a/qorai_stats_helper.h"

#include "base/files/file_path.h"
#include "base/functional/bind.h"
#include "qorai/browser/qorai_stats/first_run_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/p3a_utils/bucket.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/common/pref_names.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace qorai_ads {

namespace {

constexpr int kAdsEnabledInstallationHourBuckets[] = {0, 11, 23, 71};

}  // namespace

QoraiStatsHelper::QoraiStatsHelper(PrefService* local_state,
                                   ProfileManager* profile_manager)
    : local_state_(local_state), profile_manager_(profile_manager) {
#if !BUILDFLAG(IS_ANDROID)
  last_used_profile_pref_change_registrar_.Init(local_state_);
  last_used_profile_pref_change_registrar_.Add(
      ::prefs::kProfileLastUsed,
      base::BindRepeating(&QoraiStatsHelper::OnLastUsedProfileChanged,
                          base::Unretained(this)));
#endif

  profile_manager_observer_.Observe(profile_manager_);
}

QoraiStatsHelper::~QoraiStatsHelper() = default;

void QoraiStatsHelper::RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  registry->RegisterBooleanPref(prefs::kEnabledForLastProfile, false);
  registry->RegisterBooleanPref(prefs::kEverEnabledForAnyProfile, false);
}

void QoraiStatsHelper::OnProfileAdded(Profile* profile) {
#if BUILDFLAG(IS_ANDROID)
  if (profile == ProfileManager::GetPrimaryUserProfile()) {
#else
  base::FilePath last_used_path =
      local_state_->GetFilePath(::prefs::kProfileLastUsed);
  if ((!last_used_path.empty() && profile->GetBaseName() == last_used_path) ||
      (last_used_path.empty() &&
       profile == ProfileManager::GetLastUsedProfile())) {
#endif
    OnLastUsedProfileChanged();
  }
}

void QoraiStatsHelper::OnProfileWillBeDestroyed(Profile* profile) {
  if (!current_profile_observation_.IsObservingSource(profile)) {
    return;
  }
  current_profile_observation_.Reset();
#if !BUILDFLAG(IS_ANDROID)
  last_used_profile_pref_change_registrar_.RemoveAll();
#endif
  ads_enabled_pref_change_registrar_.RemoveAll();
}

void QoraiStatsHelper::OnProfileManagerDestroying() {
  if (current_profile_observation_.IsObserving()) {
#if !BUILDFLAG(IS_ANDROID)
    last_used_profile_pref_change_registrar_.RemoveAll();
#endif
    ads_enabled_pref_change_registrar_.RemoveAll();
    current_profile_observation_.Reset();
  }
  profile_manager_observer_.Reset();
}

void QoraiStatsHelper::SetFirstRunTimeForTesting(base::Time time) {
  testing_first_run_time_ = time;
}

PrefService* QoraiStatsHelper::GetLastUsedProfilePrefs() {
#if BUILDFLAG(IS_ANDROID)
  return ProfileManager::GetPrimaryUserProfile()->GetPrefs();
#else

  base::FilePath last_used_profile_path =
      local_state_->GetFilePath(::prefs::kProfileLastUsed);
  Profile* profile;
  if (last_used_profile_path.empty()) {
    profile = profile_manager_->GetLastUsedProfile();
  } else {
    profile = profile_manager_->GetProfileByPath(
        profile_manager_->user_data_dir().Append(last_used_profile_path));
  }
  if (profile == nullptr || profile->IsOffTheRecord()) {
    return nullptr;
  }
  if (current_profile_observation_.IsObserving()) {
    current_profile_observation_.Reset();
  }
  current_profile_observation_.Observe(profile);
  return profile->GetPrefs();
#endif
}

void QoraiStatsHelper::OnLastUsedProfileChanged() {
  PrefService* profile_prefs = GetLastUsedProfilePrefs();
  if (profile_prefs == nullptr) {
    return;
  }
  ads_enabled_pref_change_registrar_.RemoveAll();
  ads_enabled_pref_change_registrar_.Init(profile_prefs);
  ads_enabled_pref_change_registrar_.Add(
      prefs::kOptedInToNotificationAds,
      base::BindRepeating(&QoraiStatsHelper::Update, base::Unretained(this)));
  Update();
}

void QoraiStatsHelper::Update() {
  PrefService* profile_prefs = GetLastUsedProfilePrefs();
  if (profile_prefs == nullptr) {
    return;
  }
  bool is_enabled = profile_prefs->GetBoolean(prefs::kOptedInToNotificationAds);
  UpdateLocalStateAdsEnabled(is_enabled);
  MaybeReportAdsInstallationTimeMetric(is_enabled);
}

void QoraiStatsHelper::UpdateLocalStateAdsEnabled(
    bool is_enabled_for_current_profile) {
  // Copying enabled pref to local state so the stats updater does not depend on
  // the profile
  local_state_->SetBoolean(prefs::kEnabledForLastProfile,
                           is_enabled_for_current_profile);
}

void QoraiStatsHelper::MaybeReportAdsInstallationTimeMetric(
    bool is_enabled_for_current_profile) {
  if (!is_enabled_for_current_profile ||
      local_state_->GetBoolean(prefs::kEverEnabledForAnyProfile)) {
    // If ads was already enabled for a previous profile or the current profile,
    // assume the metric was already sent.
    return;
  }
  local_state_->SetBoolean(prefs::kEverEnabledForAnyProfile, true);

  base::Time first_run = !testing_first_run_time_.is_null()
                             ? testing_first_run_time_
                             : qorai_stats::GetFirstRunTime(local_state_);
  int hours_from_first_run = (base::Time::Now() - first_run).InHours();

  p3a_utils::RecordToHistogramBucket(kAdsEnabledInstallationTimeHistogramName,
                                     kAdsEnabledInstallationHourBuckets,
                                     hours_from_first_run);
}

}  // namespace qorai_ads
