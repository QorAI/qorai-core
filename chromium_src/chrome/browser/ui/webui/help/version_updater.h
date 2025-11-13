/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_HELP_VERSION_UPDATER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_HELP_VERSION_UPDATER_H_

#include "qorai/browser/sparkle_buildflags.h"

#if BUILDFLAG(ENABLE_SPARKLE)
#define PromoteUpdater                          \
  GetIsSparkleForTesting(bool& result) const {} \
  virtual void PromoteUpdater
#endif

#include <chrome/browser/ui/webui/help/version_updater.h>  // IWYU pragma: export

#if BUILDFLAG(ENABLE_SPARKLE)
#undef PromoteUpdater
#endif

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_HELP_VERSION_UPDATER_H_
