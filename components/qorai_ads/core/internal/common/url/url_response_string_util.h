/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_URL_RESPONSE_STRING_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_URL_RESPONSE_STRING_UTIL_H_

#include <string>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

std::string UrlResponseToString(
    const mojom::UrlResponseInfo& mojom_url_response);
std::string UrlResponseHeadersToString(
    const mojom::UrlResponseInfo& mojom_url_response);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_URL_RESPONSE_STRING_UTIL_H_
