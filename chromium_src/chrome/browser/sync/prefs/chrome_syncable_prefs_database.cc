/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/sync/prefs/chrome_syncable_prefs_database.h"

#include <optional>
#include <string_view>

#include "base/containers/fixed_flat_map.h"

namespace browser_sync {
namespace {
namespace qorai_syncable_prefs_ids {
enum {
  // Starts at 300000 to avoid clashing with the Chromium's syncable_prefs_ids:
  // chrome_syncable_prefs_database.cc starts at 100000
  // ios_chrome_syncable_prefs_database.cc starts at 200000
  kProfileContentSettingsExceptionsShieldsAds = 300000,
  kProfileContentSettingsExceptionsTrackers = 300001,
  kProfileContentSettingsExceptionsHttpsUpgrades = 300002,
  kProfileContentSettingsExceptionsHttpUpgradableResources = 300003,
  kProfileContentSettingsExceptionsReferrers = 300004,
  kProfileContentSettingsExceptionsShieldsCookiesV3 = 300005,
  kProfileContentSettingsExceptionsCosmeticFiltering = 300006,
  kProfileContentSettingsExceptionsFingerprintingV2 = 300007,
  kProfileContentSettingsExceptionsQoraiShields = 300008,
  kProfileContentSettingsExceptionsQoraiSpeedreader = 300009,
  kProfileDefaultContentSettingValuesShieldsAds = 300010,
  kProfileDefaultContentSettingValuesTrackers = 300011,
  kProfileDefaultContentSettingValuesHttpsUpgrades = 300012,
  kProfileDefaultContentSettingValuesHttpUpgradableResources = 300013,
  kProfileDefaultContentSettingValuesReferrers = 300014,
  kProfileDefaultContentSettingValuesShieldsCookiesV3 = 300015,
  kProfileDefaultContentSettingValuesCosmeticFiltering = 300016,
  kProfileDefaultContentSettingValuesFingerprintingV2 = 300017,
  kProfileDefaultContentSettingValuesQoraiShields = 300018,
  kProfileDefaultContentSettingValuesQoraiSpeedreader = 300019,
  kProfileContentSettingsPartitionedExceptionsShieldsAds = 300020,
  kProfileContentSettingsPartitionedExceptionsTrackers = 300021,
  kProfileContentSettingsPartitionedExceptionsHttpsUpgrades = 300022,
  kProfileContentSettingsPartitionedExceptionsHttpUpgradableResources = 300023,
  kProfileContentSettingsPartitionedExceptionsReferrers = 300024,
  kProfileContentSettingsPartitionedExceptionsShieldsCookiesV3 = 300025,
  kProfileContentSettingsPartitionedExceptionsCosmeticFiltering = 300026,
  kProfileContentSettingsPartitionedExceptionsFingerprintingV2 = 300027,
  kProfileContentSettingsPartitionedExceptionsQoraiShields = 300028,
  kProfileContentSettingsPartitionedExceptionsQoraiSpeedreader = 300029,
};
}  // namespace qorai_syncable_prefs_ids

const auto& QoraiSyncablePreferences() {
  static constexpr auto kQoraiSyncablePrefsAllowList = base::MakeFixedFlatMap<
      std::string_view, sync_preferences::SyncablePrefMetadata>({
      {"profile.content_settings.exceptions.qoraiShields",
       {qorai_syncable_prefs_ids::kProfileContentSettingsExceptionsQoraiShields,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.exceptions.qoraiSpeedreader",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsExceptionsQoraiSpeedreader,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.exceptions.cosmeticFilteringV2",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsExceptionsCosmeticFiltering,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.exceptions.fingerprintingV2",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsExceptionsFingerprintingV2,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.exceptions.httpUpgradableResources",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsExceptionsHttpUpgradableResources,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.exceptions.httpsUpgrades",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsExceptionsHttpsUpgrades,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.exceptions.referrers",
       {qorai_syncable_prefs_ids::kProfileContentSettingsExceptionsReferrers,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.exceptions.shieldsAds",
       {qorai_syncable_prefs_ids::kProfileContentSettingsExceptionsShieldsAds,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.exceptions.shieldsCookiesV3",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsExceptionsShieldsCookiesV3,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.exceptions.trackers",
       {qorai_syncable_prefs_ids::kProfileContentSettingsExceptionsTrackers,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.default_content_setting_values.qoraiShields",
       {qorai_syncable_prefs_ids::
            kProfileDefaultContentSettingValuesQoraiShields,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kNone}},
      {"profile.default_content_setting_values.qoraiSpeedreader",
       {qorai_syncable_prefs_ids::
            kProfileDefaultContentSettingValuesQoraiSpeedreader,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kNone}},
      {"profile.default_content_setting_values.cosmeticFilteringV2",
       {qorai_syncable_prefs_ids::
            kProfileDefaultContentSettingValuesCosmeticFiltering,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kNone}},
      {"profile.default_content_setting_values.fingerprintingV2",
       {qorai_syncable_prefs_ids::
            kProfileDefaultContentSettingValuesFingerprintingV2,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kNone}},
      {"profile.default_content_setting_values.httpUpgradableResources",
       {qorai_syncable_prefs_ids::
            kProfileDefaultContentSettingValuesHttpUpgradableResources,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kNone}},
      {"profile.default_content_setting_values.httpsUpgrades",
       {qorai_syncable_prefs_ids::
            kProfileDefaultContentSettingValuesHttpsUpgrades,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kNone}},
      {"profile.default_content_setting_values.referrers",
       {qorai_syncable_prefs_ids::kProfileDefaultContentSettingValuesReferrers,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kNone}},
      {"profile.default_content_setting_values.shieldsAds",
       {qorai_syncable_prefs_ids::kProfileDefaultContentSettingValuesShieldsAds,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kNone}},
      {"profile.default_content_setting_values.shieldsCookiesV3",
       {qorai_syncable_prefs_ids::
            kProfileDefaultContentSettingValuesShieldsCookiesV3,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kNone}},
      {"profile.default_content_setting_values.trackers",
       {qorai_syncable_prefs_ids::kProfileDefaultContentSettingValuesTrackers,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kNone}},
      {"profile.content_settings.partitioned_exceptions.qoraiShields",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsPartitionedExceptionsQoraiShields,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.partitioned_exceptions.qoraiSpeedreader",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsPartitionedExceptionsQoraiSpeedreader,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.partitioned_exceptions.cosmeticFilteringV2",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsPartitionedExceptionsCosmeticFiltering,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.partitioned_exceptions.fingerprintingV2",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsPartitionedExceptionsFingerprintingV2,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.partitioned_exceptions."
       "httpUpgradableResources",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsPartitionedExceptionsHttpUpgradableResources,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.partitioned_exceptions.httpsUpgrades",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsPartitionedExceptionsHttpsUpgrades,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.partitioned_exceptions.referrers",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsPartitionedExceptionsReferrers,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.partitioned_exceptions.shieldsAds",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsPartitionedExceptionsShieldsAds,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.partitioned_exceptions.shieldsCookiesV3",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsPartitionedExceptionsShieldsCookiesV3,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
      {"profile.content_settings.partitioned_exceptions.trackers",
       {qorai_syncable_prefs_ids::
            kProfileContentSettingsPartitionedExceptionsTrackers,
        syncer::PREFERENCES, sync_preferences::PrefSensitivity::kNone,
        sync_preferences::MergeBehavior::kMergeableDict}},
  });
  return kQoraiSyncablePrefsAllowList;
}
}  // namespace
}  // namespace browser_sync

#define GetSyncablePrefMetadata GetSyncablePrefMetadata_ChromiumImpl
#include <chrome/browser/sync/prefs/chrome_syncable_prefs_database.cc>
#undef GetSyncablePrefMetadata

namespace browser_sync {

std::optional<sync_preferences::SyncablePrefMetadata>
ChromeSyncablePrefsDatabase::GetSyncablePrefMetadata(
    std::string_view pref_name) const {
  const auto it = QoraiSyncablePreferences().find(pref_name);
  if (it != QoraiSyncablePreferences().end()) {
    return it->second;
  }
  return GetSyncablePrefMetadata_ChromiumImpl(pref_name);
}

}  // namespace browser_sync
