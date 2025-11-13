// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_QORAI_SHIELDS_P3A_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_QORAI_SHIELDS_P3A_H_

#include "qorai/components/qorai_shields/core/common/qorai_shields_settings_values.h"

class PrefRegistrySimple;
class PrefService;
class HostContentSettingsMap;

namespace qorai_shields {

inline constexpr char kUsagePrefName[] = "qorai_shields.p3a_usage";
inline constexpr char kFirstReportedPrefName[] =
    "qorai_shields.p3a_first_reported_v2";  // DEPRECATED
inline constexpr char kFirstReportedRevisionPrefName[] =
    "qorai_shields.p3a_first_reported_revision";

inline constexpr char kAdsStrictCountPrefName[] =
    "qorai_shields.p3a_ads_strict_domain_count";
inline constexpr char kAdsStandardCountPrefName[] =
    "qorai_shields.p3a_ads_standard_domain_count";
inline constexpr char kAdsAllowCountPrefName[] =
    "qorai_shields.p3a_ads_allow_domain_count";
inline constexpr char kFPStrictCountPrefName[] =
    "qorai_shields.p3a_fp_strict_domain_count";
inline constexpr char kFPStandardCountPrefName[] =
    "qorai_shields.p3a_fp_standard_domain_count";
inline constexpr char kFPAllowCountPrefName[] =
    "qorai_shields.p3a_fp_allow_domain_count";

inline constexpr char kAdsSettingHistogramName[] =
    "Qorai.Shields.AdBlockSetting";
inline constexpr char kFingerprintSettingHistogramName[] =
    "Qorai.Shields.FingerprintBlockSetting";
inline constexpr char kUsageStatusHistogramName[] = "Qorai.Shields.UsageStatus";
inline constexpr char kDomainAdsSettingsAboveHistogramName[] =
    "Qorai.Shields.DomainAdsSettingsAboveGlobal";
inline constexpr char kDomainAdsSettingsBelowHistogramName[] =
    "Qorai.Shields.DomainAdsSettingsBelowGlobal";
inline constexpr char kDomainFPSettingsAboveHistogramName[] =
    "Qorai.Shields.DomainFingerprintSettingsAboveGlobal";
inline constexpr char kDomainFPSettingsBelowHistogramName[] =
    "Qorai.Shields.DomainFingerprintSettingsBelowGlobal";
inline constexpr char kForgetFirstPartyHistogramName[] =
    "Qorai.Shields.ForgetFirstParty";
// Note: append-only enumeration! Never remove any existing values, as this enum
// is used to bucket a UMA histogram, and removing values breaks that.
enum ShieldsIconUsage {
  kNeverClicked,
  kClicked,
  kShutOffShields,
  kChangedPerSiteShields,
  kSize,
};

// We save latest value to local state and compare new values with it.
// The idea is to write to a histogram only the highest value (e.g. we are
// not interested in |kClicked| event if the user already turned off shields.
// Sine P3A sends only latest written values, these is enough for our current
// goals.
void MaybeRecordShieldsUsageP3A(ShieldsIconUsage usage,
                                PrefService* local_state);

// Records to global ads setting histogram: Qorai.Shields.AdBlockSetting
void RecordShieldsAdsSetting(ControlType setting);

// Records to global FP setting histogram: Qorai.Shields.FingerprintBlockSetting
void RecordShieldsFingerprintSetting(ControlType setting);

// To be called when the global setting changes.
// Will update domain setting count histograms.
void RecordShieldsDomainSettingCounts(PrefService* profile_prefs,
                                      bool is_fingerprint,
                                      ControlType global_setting);

// To be called when a domain setting changes.
// Will update internal pref counts and update domain setting count histograms.
void RecordShieldsDomainSettingCountsWithChange(PrefService* profile_prefs,
                                                bool is_fingerprint,
                                                ControlType global_setting,
                                                ControlType* prev_setting,
                                                ControlType new_setting);

// Records global "forget me when I close this site" setting,
// and any per-site exceptions.
void RecordForgetFirstPartySetting(HostContentSettingsMap* map);

void RegisterShieldsP3ALocalPrefs(PrefRegistrySimple* local_state);

void RegisterShieldsP3AProfilePrefs(PrefRegistrySimple* registry);
void RegisterShieldsP3AProfilePrefsForMigration(PrefRegistrySimple* registry);
void MigrateObsoleteProfilePrefs(PrefService* profile_prefs);

// To be called at initialization. Will count all domain settings and
// record to all histograms, if executed for the first time.
void MaybeRecordInitialShieldsSettings(
    PrefService* profile_prefs,
    HostContentSettingsMap* map,
    ControlType cosmetic_filtering_control_type,
    ControlType fingerprinting_control_type);

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_QORAI_SHIELDS_P3A_H_
