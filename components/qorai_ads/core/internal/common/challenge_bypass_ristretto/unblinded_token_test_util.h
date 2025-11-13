/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_UNBLINDED_TOKEN_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_UNBLINDED_TOKEN_TEST_UTIL_H_

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"

namespace qorai_ads::cbr::test {

UnblindedToken GetUnblindedToken();
UnblindedTokenList GetUnblindedTokens();

}  // namespace qorai_ads::cbr::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_UNBLINDED_TOKEN_TEST_UTIL_H_
