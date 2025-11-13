/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/issuers/url_request/issuers_url_request_json_reader_util.h"

#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_value_util.h"

namespace qorai_ads::json::reader {

namespace {

constexpr char kPingKey[] = "ping";
constexpr char kIssuersKey[] = "issuers";

}  // namespace

std::optional<int> ParsePing(const base::Value::Dict& dict) {
  return dict.FindInt(kPingKey);
}

std::optional<TokenIssuerList> ParseTokenIssuers(
    const base::Value::Dict& dict) {
  if (const auto* const list = dict.FindList(kIssuersKey)) {
    return TokenIssuersFromValue(*list);
  }

  return std::nullopt;
}

}  // namespace qorai_ads::json::reader
