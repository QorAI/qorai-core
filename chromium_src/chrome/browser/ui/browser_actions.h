/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_ACTIONS_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_ACTIONS_H_

#define InitializeBrowserActions    \
  UnUsed() {}                       \
  friend class QoraiBrowserActions; \
  virtual void InitializeBrowserActions

#include <chrome/browser/ui/browser_actions.h>  // IWYU pragma: export

#undef InitializeBrowserActions

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_ACTIONS_H_
