/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <optional>

#include "base/check.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/verification_key.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/verification_key_test_util.h"

namespace qorai_ads::cbr::test {

VerificationKey GetVerificationKey() {
  const UnblindedToken unblinded_token = GetUnblindedToken();
  std::optional<VerificationKey> verification_key =
      unblinded_token.DeriveVerificationKey();
  CHECK(verification_key);
  return *verification_key;
}

}  // namespace qorai_ads::cbr::test
