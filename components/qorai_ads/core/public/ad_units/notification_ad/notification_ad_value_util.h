/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_VALUE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_VALUE_UTIL_H_

#include "base/containers/circular_deque.h"
#include "base/values.h"

namespace qorai_ads {

struct NotificationAdInfo;

base::Value::Dict NotificationAdToValue(const NotificationAdInfo& ad);
base::Value::List NotificationAdsToValue(
    const base::circular_deque<NotificationAdInfo>& ads);

NotificationAdInfo NotificationAdFromValue(const base::Value::Dict& dict);
base::circular_deque<NotificationAdInfo> NotificationAdsFromValue(
    const base::Value::List& list);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_VALUE_UTIL_H_
