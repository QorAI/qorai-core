/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_JSON_READER_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_JSON_READER_UTIL_H_

#include <optional>
#include <string>


namespace qorai_ads::json::reader {

std::optional<std::string> ParseSubdivision(const std::string& json);

}  // namespace qorai_ads::json::reader

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_JSON_READER_UTIL_H_
