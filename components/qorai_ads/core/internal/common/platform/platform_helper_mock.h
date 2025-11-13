/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_PLATFORM_PLATFORM_HELPER_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_PLATFORM_PLATFORM_HELPER_MOCK_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/common/platform/platform_helper.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class PlatformHelperMock : public PlatformHelper {
 public:
  PlatformHelperMock();

  PlatformHelperMock(const PlatformHelperMock&) = delete;
  PlatformHelperMock& operator=(const PlatformHelperMock&) = delete;

  ~PlatformHelperMock() override;

  MOCK_METHOD(bool, IsMobile, (), (const));
  MOCK_METHOD(std::string, GetName, (), (const));
  MOCK_METHOD(PlatformType, GetType, (), (const));
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_PLATFORM_PLATFORM_HELPER_MOCK_H_
