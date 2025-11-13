/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_EXTENSION_SERVICE_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_EXTENSION_SERVICE_H_

#define BlocklistStatesInteractionUnitTest \
  BlocklistStatesInteractionUnitTest;      \
  friend class QoraiExtensionService

#include <chrome/browser/extensions/extension_service.h>  // IWYU pragma: export
#undef BlocklistStatesInteractionUnitTest

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_EXTENSION_SERVICE_H_
