/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/locale/language_code.h"

#import <Foundation/Foundation.h>

#include <optional>

#include "base/strings/sys_string_conversions.h"

namespace qorai_ads {

std::optional<std::string> MaybeGetLanguageCodeString() {
  return base::SysNSStringToUTF8(NSLocale.currentLocale.languageCode);
}

}  // namespace qorai_ads
