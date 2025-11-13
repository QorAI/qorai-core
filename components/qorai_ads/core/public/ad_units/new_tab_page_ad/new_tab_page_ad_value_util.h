/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_VALUE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_VALUE_UTIL_H_

#include "base/values.h"

namespace qorai_ads {

struct NewTabPageAdInfo;

base::Value::Dict NewTabPageAdToValue(const NewTabPageAdInfo& ad);
NewTabPageAdInfo NewTabPageAdFromValue(const base::Value::Dict& dict);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_VALUE_UTIL_H_
