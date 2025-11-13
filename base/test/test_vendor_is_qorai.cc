/* Copyright (c) 2024 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

namespace base::test {

// This is implemented in //qorai/chromium_src/base/check_is_test.cc
void SetTestVendorIsQorAIForTesting();

static const struct CallSetTestVendorIsQorAIForTesting {
  CallSetTestVendorIsQorAIForTesting() { SetTestVendorIsQorAIForTesting(); }
} kCallSetTestVendorIsQorAIForTesting;

}  // namespace base::test
