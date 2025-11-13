/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_DELEGATE_H_

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

struct SearchResultAdInfo;

class SearchResultAdEventHandlerDelegate {
 public:
  // Invoked when the search result `ad` is served.
  virtual void OnDidFireSearchResultAdServedEvent(
      const SearchResultAdInfo& ad) {}

  // Invoked when the search result `ad` is viewed.
  virtual void OnDidFireSearchResultAdViewedEvent(
      const SearchResultAdInfo& ad) {}

  // Invoked when the search result `ad` is clicked.
  virtual void OnDidFireSearchResultAdClickedEvent(
      const SearchResultAdInfo& ad) {}

  // Invoked when the search result `ad` event fails for `mojom_ad_event_type`.
  virtual void OnFailedToFireSearchResultAdEvent(
      const SearchResultAdInfo& ad,
      mojom::SearchResultAdEventType mojom_ad_event_type) {}

 protected:
  virtual ~SearchResultAdEventHandlerDelegate() = default;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_DELEGATE_H_
