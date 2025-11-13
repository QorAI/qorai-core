/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_PROMOTED_CONTENT_ADS_PROMOTED_CONTENT_AD_EVENT_HANDLER_DELEGATE_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_PROMOTED_CONTENT_ADS_PROMOTED_CONTENT_AD_EVENT_HANDLER_DELEGATE_MOCK_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/promoted_content_ads/promoted_content_ad_event_handler_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class PromotedContentAdEventHandlerDelegateMock
    : public PromotedContentAdEventHandlerDelegate {
 public:
  PromotedContentAdEventHandlerDelegateMock();

  PromotedContentAdEventHandlerDelegateMock(
      const PromotedContentAdEventHandlerDelegateMock&) = delete;
  PromotedContentAdEventHandlerDelegateMock& operator=(
      const PromotedContentAdEventHandlerDelegateMock&) = delete;

  ~PromotedContentAdEventHandlerDelegateMock() override;

  MOCK_METHOD(void,
              OnDidFirePromotedContentAdServedEvent,
              (const PromotedContentAdInfo&));
  MOCK_METHOD(void,
              OnDidFirePromotedContentAdViewedEvent,
              (const PromotedContentAdInfo&));
  MOCK_METHOD(void,
              OnDidFirePromotedContentAdClickedEvent,
              (const PromotedContentAdInfo&));
  MOCK_METHOD(void,
              OnFailedToFirePromotedContentAdEvent,
              (const std::string&,
               const std::string&,
               mojom::PromotedContentAdEventType));
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_PROMOTED_CONTENT_ADS_PROMOTED_CONTENT_AD_EVENT_HANDLER_DELEGATE_MOCK_H_
