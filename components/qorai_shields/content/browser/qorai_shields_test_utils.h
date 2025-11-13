// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_QORAI_SHIELDS_TEST_UTILS_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_QORAI_SHIELDS_TEST_UTILS_H_

#include <stdint.h>

#include "base/auto_reset.h"

namespace qorai_shields {

class ScopedStableFarblingTokensForTesting {
 public:
  // The seed value determines whether the farbling is random or deterministic.
  // If the seed is 0, the farbling is random (production mode). If the seed is
  // non-zero, the farbling is deterministic.
  explicit ScopedStableFarblingTokensForTesting(uint32_t seed);
  ~ScopedStableFarblingTokensForTesting();

 private:
  base::AutoReset<uint32_t> scoped_stable_farbling_token_seed_;
};

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_QORAI_SHIELDS_TEST_UTILS_H_
