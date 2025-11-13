/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/settings/settings.h"

#include "qorai/components/qorai_ads/core/internal/prefs/pref_util.h"
#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_feature.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/ntp_background_images/common/pref_names.h"

namespace qorai_ads {

bool UserHasJoinedQoraiRewards() {
  return GetProfileBooleanPref(qorai_rewards::prefs::kEnabled);
}

bool UserHasJoinedQoraiRewardsAndNotConnectedWallet() {
  return UserHasJoinedQoraiRewards() &&
         GetProfileStringPref(qorai_rewards::prefs::kExternalWalletType)
             .empty();
}

bool UserHasJoinedQoraiRewardsAndConnectedWallet() {
  return UserHasJoinedQoraiRewards() &&
         !GetProfileStringPref(qorai_rewards::prefs::kExternalWalletType)
              .empty();
}

bool UserHasOptedInToQoraiNewsAds() {
  return GetProfileBooleanPref(qorai_news::prefs::kQoraiNewsOptedIn) &&
         GetProfileBooleanPref(qorai_news::prefs::kNewTabPageShowToday);
}

bool UserHasOptedInToNewTabPageAds() {
  return GetProfileBooleanPref(
             ntp_background_images::prefs::kNewTabPageShowBackgroundImage) &&
         GetProfileBooleanPref(
             ntp_background_images::prefs::
                 kNewTabPageShowSponsoredImagesBackgroundImage);
}

bool UserHasOptedInToNotificationAds() {
  return UserHasJoinedQoraiRewards() &&
         GetProfileBooleanPref(prefs::kOptedInToNotificationAds);
}

int GetMaximumNotificationAdsPerHour() {
  const int ads_per_hour = static_cast<int>(
      GetProfileInt64Pref(prefs::kMaximumNotificationAdsPerHour));

  return ads_per_hour > 0 ? ads_per_hour : kDefaultNotificationAdsPerHour.Get();
}

bool UserHasOptedInToSearchResultAds() {
  return GetProfileBooleanPref(prefs::kOptedInToSearchResultAds);
}

bool UserHasOptedInToSurveyPanelist() {
  return GetProfileBooleanPref(
      ntp_background_images::prefs::kNewTabPageSponsoredImagesSurveyPanelist);
}

}  // namespace qorai_ads
