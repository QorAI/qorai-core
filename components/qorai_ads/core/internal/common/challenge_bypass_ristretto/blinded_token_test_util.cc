/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token_test_util.h"

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"

namespace qorai_ads::cbr::test {

BlindedToken GetBlindedToken() {
  return BlindedToken(kBlindedTokenBase64);
}

BlindedToken GetInvalidBlindedToken() {
  return BlindedToken(kInvalidBase64);
}

BlindedTokenList GetBlindedTokens() {
  return {GetBlindedToken()};
}

BlindedTokenList GetInvalidBlindedTokens() {
  return {GetInvalidBlindedToken()};
}

}  // namespace qorai_ads::cbr::test
