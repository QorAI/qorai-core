/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_INFO_H_

#include <string>

#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"

namespace qorai_ads {

struct NotificationAdInfo final : AdInfo {
  [[nodiscard]] bool IsValid() const;

  std::string title;
  std::string body;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_INFO_H_
