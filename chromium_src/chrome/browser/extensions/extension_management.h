/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_EXTENSION_MANAGEMENT_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_EXTENSION_MANAGEMENT_H_

#define ExtensionManagementServiceTest \
  ExtensionManagementServiceTest;      \
  friend class QoraiExtensionManagement

#include <chrome/browser/extensions/extension_management.h>  // IWYU pragma: export
#undef ExtensionManagementServiceTest

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_EXTENSION_MANAGEMENT_H_
