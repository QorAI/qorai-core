/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/test/internal/pref_value_test_info.h"

namespace qorai_ads::test {

PrefValueInfo::PrefValueInfo() = default;

PrefValueInfo::PrefValueInfo(const PrefValueInfo& other) {
  *this = other;
}

PrefValueInfo& PrefValueInfo::operator=(const PrefValueInfo& other) {
  if (this != &other) {
    default_value = other.default_value.Clone();
    if (other.value) {
      value = other.value->Clone();
    }
  }

  return *this;
}

PrefValueInfo::PrefValueInfo(PrefValueInfo&& other) noexcept = default;

PrefValueInfo& PrefValueInfo::operator=(PrefValueInfo&& other) noexcept =
    default;

PrefValueInfo::~PrefValueInfo() = default;

}  // namespace qorai_ads::test
