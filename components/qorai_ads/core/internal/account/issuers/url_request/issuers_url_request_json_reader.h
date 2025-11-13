/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_JSON_READER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_JSON_READER_H_

#include <optional>
#include <string>

namespace qorai_ads {

struct IssuersInfo;

namespace json::reader {

std::optional<IssuersInfo> ReadIssuers(const std::string& json);

}  // namespace json::reader

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_JSON_READER_H_
