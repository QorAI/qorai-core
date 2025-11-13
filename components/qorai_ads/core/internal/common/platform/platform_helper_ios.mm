/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/platform/platform_helper_ios.h"

namespace qorai_ads {

namespace {
constexpr char kPlatformName[] = "ios";
}  // namespace

PlatformHelperIos::PlatformHelperIos() = default;

bool PlatformHelperIos::IsMobile() const {
  return true;
}

std::string PlatformHelperIos::GetName() const {
  return kPlatformName;
}

PlatformType PlatformHelperIos::GetType() const {
  return PlatformType::kIOS;
}

}  // namespace qorai_ads
