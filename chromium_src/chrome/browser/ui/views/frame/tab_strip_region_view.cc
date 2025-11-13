/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/views/frame/tab_strip_region_view.h"

#include "qorai/browser/ui/views/tabs/qorai_browser_tab_strip_controller.h"
#include "qorai/browser/ui/views/tabs/qorai_new_tab_button.h"
#include "qorai/browser/ui/views/tabs/qorai_tab_strip.h"

// Currently, `NewTabButton::kButtonSize` is used to calculate tab strip button
// borders. Since the size of buttons varies depending upon the tabs update
// feature flag, replace the `kButtonSize` identifier with a call to the static
// `QoraiNewTabButton::GetButtonSize` function.
#define kButtonSize GetButtonSize()

#define BrowserTabStripController QoraiBrowserTabStripController
#define NewTabButton QoraiNewTabButton

#define QORAI_TAB_STRIP_REGION_VIEW_CREATE_TAB_STRIP \
  auto tab_strip =                                   \
      std::make_unique<QoraiTabStrip>(std::move(tabstrip_controller));

#include <chrome/browser/ui/views/frame/tab_strip_region_view.cc>
#undef QORAI_TAB_STRIP_REGION_VIEW_CREATE_TAB_STRIP
#undef NewTabButton
#undef BrowserTabStripController
#undef kButtonSize
