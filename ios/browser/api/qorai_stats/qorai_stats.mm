/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/api/qorai_stats/qorai_stats.h"

#include "base/memory/raw_ptr.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/sys_string_conversions.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_stats/browser/qorai_stats_updater_util.h"
#include "qorai/components/qorai_stats/browser/buildflags.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/webcompat_reporter/buildflags/buildflags.h"
#include "components/prefs/pref_service.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

NSString* const kQoraiStatsAPIKey = @BUILDFLAG(QORAI_STATS_API_KEY);
NSString* const kWebcompatReportEndpoint =
    @BUILDFLAG(WEBCOMPAT_REPORT_ENDPOINT);

@implementation QoraiStats {
  raw_ptr<PrefService> _localPrefs;
  raw_ptr<PrefService> _profilePrefs;
}

- (instancetype)initWithBrowserState:(ProfileIOS*)profile {
  if ((self = [super init])) {
    _profilePrefs = profile->GetPrefs();
    _localPrefs = GetApplicationContext()->GetLocalState();
  }
  return self;
}

- (BOOL)isStatsReportingManaged {
  return _localPrefs->IsManagedPreference(kStatsReportingEnabled);
}

- (BOOL)isStatsReportingEnabled {
  return _localPrefs->GetBoolean(kStatsReportingEnabled);
}

- (void)setStatsReportingEnabled:(BOOL)statsReportingEnabled {
  _localPrefs->SetBoolean(kStatsReportingEnabled, statsReportingEnabled);
}

- (NSDictionary<NSString*, NSString*>*)walletParams {
  auto wallet_last_unlocked = _localPrefs->GetTime(kQoraiWalletLastUnlockTime);
  auto last_reported_wallet_unlock =
      _localPrefs->GetTime(kQoraiWalletPingReportedUnlockTime);
  uint8_t usage_bitset = 0;
  if (wallet_last_unlocked > last_reported_wallet_unlock) {
    usage_bitset = qorai_stats::UsageBitfieldFromTimestamp(
        wallet_last_unlocked, last_reported_wallet_unlock);
  }
  return @{
    @"wallet2" : base::SysUTF8ToNSString(base::NumberToString(usage_bitset))
  };
}

- (BOOL)isNotificationAdsEnabled {
  return _profilePrefs->GetBoolean(qorai_ads::prefs::kOptedInToNotificationAds);
}

- (void)notifyStatsPingSent {
  auto wallet_last_unlocked = _localPrefs->GetTime(kQoraiWalletLastUnlockTime);
  _localPrefs->SetTime(kQoraiWalletPingReportedUnlockTime,
                       wallet_last_unlocked);
}

@end
