/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/test/internal/local_state_pref_value_test_util_internal.h"

#include <ostream>

#include "base/check.h"
#include "qorai/components/qorai_ads/core/internal/common/test/internal/local_state_pref_storage_test_util_internal.h"
#include "qorai/components/qorai_ads/core/internal/common/test/internal/pref_value_test_info.h"

namespace qorai_ads::test {

base::Value GetLocalStatePrefValue(const std::string& path) {
  CHECK(HasLocalStatePref(path))
      << "Check failed. Trying to read an unregistered pref: " << path;

  const PrefValueInfo& pref = LocalStatePref(path);
  if (!pref.value) {
    return pref.default_value.Clone();
  }

  return pref.value->Clone();
}

base::Value GetDefaultLocalStatePrefValue(const std::string& path) {
  CHECK(HasLocalStatePref(path))
      << "Check failed. Trying to read an unregistered pref: " << path;

  return LocalStatePref(path).default_value.Clone();
}

void ClearLocalStatePrefValue(const std::string& path) {
  CHECK(HasLocalStatePref(path))
      << "Check failed. Trying to clear an unregistered pref: " << path;

  LocalStatePref(path).value.reset();
}

bool HasLocalStatePrefPathValue(const std::string& path) {
  CHECK(HasLocalStatePref(path))
      << "Check failed. Trying to read an unregistered pref: " << path;

  return !!LocalStatePref(path).value;
}

}  // namespace qorai_ads::test
