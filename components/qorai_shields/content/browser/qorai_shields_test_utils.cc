// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_shields/content/browser/qorai_shields_test_utils.h"

namespace qorai_shields {

// Declared in qorai_shields_util.cc.
extern uint32_t g_stable_farbling_tokens_seed;

ScopedStableFarblingTokensForTesting::ScopedStableFarblingTokensForTesting(
    uint32_t seed)
    : scoped_stable_farbling_token_seed_(&g_stable_farbling_tokens_seed, seed) {
}

ScopedStableFarblingTokensForTesting::~ScopedStableFarblingTokensForTesting() =
    default;

}  // namespace qorai_shields
