/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/test/internal/string_test_util_internal.h"

#include <vector>

#include "base/strings/strcat.h"
#include "base/strings/string_split.h"
#include "base/strings/string_util.h"

namespace qorai_ads::test {

std::string CapitalizeFirstCharacterOfEachWordAndTrimWhitespace(
    const std::string& value) {
  std::vector<std::string> components = base::SplitString(
      value, " ", base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);

  for (auto& component : components) {
    component[0] = base::ToUpperASCII(component[0]);
  }

  return base::StrCat(components);
}

}  // namespace qorai_ads::test
