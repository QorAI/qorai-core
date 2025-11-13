/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token_test_util.h"

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"

namespace qorai_ads::cbr::test {

Token GetToken() {
  return Token(kTokenBase64);
}

Token GetInvalidToken() {
  return Token(kInvalidBase64);
}

TokenList GetTokens() {
  return {GetToken()};
}

TokenList GetInvalidTokens() {
  return {GetInvalidToken()};
}

}  // namespace qorai_ads::cbr::test
