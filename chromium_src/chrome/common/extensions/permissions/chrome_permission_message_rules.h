/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_COMMON_EXTENSIONS_PERMISSIONS_CHROME_PERMISSION_MESSAGE_RULES_H_
#define QORAI_CHROMIUM_SRC_CHROME_COMMON_EXTENSIONS_PERMISSIONS_CHROME_PERMISSION_MESSAGE_RULES_H_

#define GetAllRules           \
  GetAllRules_ChromiumImpl(); \
  static std::vector<ChromePermissionMessageRule> GetAllRules
#include <chrome/common/extensions/permissions/chrome_permission_message_rules.h>  // IWYU pragma: export
#undef GetAllRules

#endif  // QORAI_CHROMIUM_SRC_CHROME_COMMON_EXTENSIONS_PERMISSIONS_CHROME_PERMISSION_MESSAGE_RULES_H_
