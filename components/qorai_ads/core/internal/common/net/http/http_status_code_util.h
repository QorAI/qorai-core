/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_NET_HTTP_HTTP_STATUS_CODE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_NET_HTTP_HTTP_STATUS_CODE_UTIL_H_

#include <optional>
#include <string>

namespace qorai_ads {

bool IsSuccessfulHttpStatusCode(int http_status_code);

std::optional<std::string> HttpStatusCodeToString(int http_status_code);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_NET_HTTP_HTTP_STATUS_CODE_UTIL_H_
