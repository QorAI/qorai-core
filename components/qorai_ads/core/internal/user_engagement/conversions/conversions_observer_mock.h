/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_OBSERVER_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_OBSERVER_MOCK_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class ConversionsObserverMock : public ConversionsObserver {
 public:
  ConversionsObserverMock();

  ConversionsObserverMock(const ConversionsObserverMock&) = delete;
  ConversionsObserverMock& operator=(const ConversionsObserverMock&) = delete;

  ~ConversionsObserverMock() override;

  MOCK_METHOD(void, OnDidConvertAd, (const ConversionInfo&));
  MOCK_METHOD(void, OnFailedToConvertAd, (const std::string&));
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_OBSERVER_MOCK_H_
