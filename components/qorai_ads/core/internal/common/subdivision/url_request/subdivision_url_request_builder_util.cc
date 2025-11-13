/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/subdivision/url_request/subdivision_url_request_builder_util.h"

#include "qorai/components/qorai_ads/core/internal/common/subdivision/url_request/subdivision_url_request_constants.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace qorai_ads {

std::string BuildSubdivisionUrlPath() {
  return absl::StrFormat("/v%d/getstate", kSubdivisionServerVersion);
}

}  // namespace qorai_ads
