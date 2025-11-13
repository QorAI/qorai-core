/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_EVENT_TYPE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_EVENT_TYPE_UTIL_H_

#include <optional>
#include <string_view>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

std::optional<mojom::NewTabPageAdEventType> ToMojomNewTabPageAdEventType(
    std::string_view value);

std::string_view ToString(mojom::NewTabPageAdEventType value);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_EVENT_TYPE_UTIL_H_
