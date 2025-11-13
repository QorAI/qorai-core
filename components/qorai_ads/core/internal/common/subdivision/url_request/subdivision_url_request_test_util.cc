/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/strings/string_util.h"
#include "qorai/components/qorai_ads/core/internal/common/subdivision/url_request/subdivision_url_request_test_util.h"

namespace qorai_ads::test {

std::string BuildSubdivisionUrlResponseBody(
    const std::string& country_code,
    const std::string& subdivision_code) {
  return base::ReplaceStringPlaceholders(
      R"(
          {
            "country": "$1",
            "region": "$2"
          })",
      {country_code, subdivision_code}, nullptr);
}

}  // namespace qorai_ads::test
