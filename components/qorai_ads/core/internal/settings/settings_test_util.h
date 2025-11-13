/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SETTINGS_SETTINGS_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SETTINGS_SETTINGS_TEST_UTIL_H_

namespace qorai_ads::test {

void DisableQoraiRewards();
void DisconnectExternalQoraiRewardsWallet();

void OptOutOfQoraiNewsAds();

void OptOutOfNewTabPageAds();

void OptOutOfNotificationAds();
void SetMaximumNotificationAdsPerHour(int max_ads_per_hour);

void OptOutOfSearchResultAds();

void OptOutOfAllAds();

void OptOutOfSurveyPanelist();

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SETTINGS_SETTINGS_TEST_UTIL_H_
