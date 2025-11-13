/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/prefs/pref_path_util.h"

#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/ntp_background_images/common/pref_names.h"

namespace qorai_ads {

bool DoesMatchUserHasJoinedQoraiRewardsPrefPath(const std::string& path) {
  return path == qorai_rewards::prefs::kEnabled;
}

bool DoesMatchUserHasOptedInToQoraiNewsAdsPrefPath(const std::string& path) {
  return path == qorai_news::prefs::kQoraiNewsOptedIn ||
         path == qorai_news::prefs::kNewTabPageShowToday;
}

bool DoesMatchUserHasOptedInToNewTabPageAdsPrefPath(const std::string& path) {
  return path == ntp_background_images::prefs::kNewTabPageShowBackgroundImage ||
         path == ntp_background_images::prefs::
                     kNewTabPageShowSponsoredImagesBackgroundImage;
}

bool DoesMatchUserHasOptedInToNotificationAdsPrefPath(const std::string& path) {
  return path == prefs::kOptedInToNotificationAds;
}

bool DoesMatchUserHasOptedInToSearchResultAdsPrefPath(const std::string& path) {
  return path == prefs::kOptedInToSearchResultAds;
}

}  // namespace qorai_ads
