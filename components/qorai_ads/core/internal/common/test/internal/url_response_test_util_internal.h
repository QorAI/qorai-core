/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_URL_RESPONSE_TEST_UTIL_INTERNAL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_URL_RESPONSE_TEST_UTIL_INTERNAL_H_

#include <optional>

#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads::test {

std::optional<mojom::UrlResponseInfo> GetNextUrlResponseForRequest(
    const mojom::UrlRequestInfoPtr& mojom_url_request,
    const URLResponseMap& url_responses);

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_URL_RESPONSE_TEST_UTIL_INTERNAL_H_
