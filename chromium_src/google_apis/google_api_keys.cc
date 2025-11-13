/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <google_apis/google_api_keys.cc>

namespace google_apis {

void SetAPIKeyForTesting(const std::string& api_key) {
  GetApiKeyCacheInstance().set_api_key_for_testing(api_key);  // IN-TEST
}

bool QoraiHasAPIKeyConfigured() {
  // Google API key is not used in qorai for translation service, always return
  // true for the API key check so the flow won't be blocked because of missing
  // keys.
  return true;
}

}  // namespace google_apis
