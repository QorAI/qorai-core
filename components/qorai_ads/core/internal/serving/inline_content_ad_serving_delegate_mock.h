/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_INLINE_CONTENT_AD_SERVING_DELEGATE_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_INLINE_CONTENT_AD_SERVING_DELEGATE_MOCK_H_

#include <cstdint>

#include "qorai/components/qorai_ads/core/internal/serving/inline_content_ad_serving_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class InlineContentAdServingDelegateMock
    : public InlineContentAdServingDelegate {
 public:
  InlineContentAdServingDelegateMock();

  InlineContentAdServingDelegateMock(
      const InlineContentAdServingDelegateMock&) = delete;
  InlineContentAdServingDelegateMock& operator=(
      const InlineContentAdServingDelegateMock&) = delete;

  ~InlineContentAdServingDelegateMock() override;

  MOCK_METHOD(void, OnOpportunityAroseToServeInlineContentAd, ());

  MOCK_METHOD(void,
              OnDidServeInlineContentAd,
              (int32_t, const InlineContentAdInfo&));
  MOCK_METHOD(void, OnFailedToServeInlineContentAd, ());
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_INLINE_CONTENT_AD_SERVING_DELEGATE_MOCK_H_
