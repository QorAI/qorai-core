/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_SERVED_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_SERVED_H_

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_interface.h"

namespace qorai_ads {

struct SearchResultAdInfo;

class SearchResultAdEventServed final
    : public AdEventInterface<SearchResultAdInfo> {
 public:
  void FireEvent(const SearchResultAdInfo& ad,
                 ResultCallback callback) override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_SERVED_H_
