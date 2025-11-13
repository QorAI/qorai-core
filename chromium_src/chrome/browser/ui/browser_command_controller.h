// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_COMMAND_CONTROLLER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_COMMAND_CONTROLLER_H_

#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"

#define OnTabStripModelChanged                \
  OnTabStripModelChanged_Unused();            \
  friend class QoraiBrowserCommandController; \
  void OnTabStripModelChanged

#include <chrome/browser/ui/browser_command_controller.h>  // IWYU pragma: export

#undef OnTabStripModelChanged

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_COMMAND_CONTROLLER_H_
