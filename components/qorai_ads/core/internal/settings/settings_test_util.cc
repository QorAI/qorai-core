/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/ntp_background_images/common/pref_names.h"

namespace qorai_ads::test {

void DisableQoraiRewards() {
  SetProfileBooleanPrefValue(qorai_rewards::prefs::kEnabled, false);
  DisconnectExternalQoraiRewardsWallet();
}

void DisconnectExternalQoraiRewardsWallet() {
  SetProfileStringPrefValue(qorai_rewards::prefs::kExternalWalletType, "");
}

void OptOutOfQoraiNewsAds() {
  SetProfileBooleanPrefValue(qorai_news::prefs::kQoraiNewsOptedIn, false);
  SetProfileBooleanPrefValue(qorai_news::prefs::kNewTabPageShowToday, false);
}

void OptOutOfNewTabPageAds() {
  SetProfileBooleanPrefValue(
      ntp_background_images::prefs::kNewTabPageShowBackgroundImage, false);
  SetProfileBooleanPrefValue(ntp_background_images::prefs::
                                 kNewTabPageShowSponsoredImagesBackgroundImage,
                             false);
}

void OptOutOfNotificationAds() {
  SetProfileBooleanPrefValue(prefs::kOptedInToNotificationAds, false);
}

void SetMaximumNotificationAdsPerHour(int max_ads_per_hour) {
  SetProfileInt64PrefValue(prefs::kMaximumNotificationAdsPerHour,
                           max_ads_per_hour);
}

void OptOutOfSearchResultAds() {
  SetProfileBooleanPrefValue(prefs::kOptedInToSearchResultAds, false);
}

void OptOutOfAllAds() {
  OptOutOfQoraiNewsAds();
  OptOutOfNewTabPageAds();
  OptOutOfNotificationAds();
  OptOutOfSearchResultAds();
}

void OptOutOfSurveyPanelist() {
  SetProfileBooleanPrefValue(
      ntp_background_images::prefs::kNewTabPageSponsoredImagesSurveyPanelist,
      false);
}

}  // namespace qorai_ads::test
