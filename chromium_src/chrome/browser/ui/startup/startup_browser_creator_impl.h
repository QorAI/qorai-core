/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_STARTUP_STARTUP_BROWSER_CREATOR_IMPL_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_STARTUP_STARTUP_BROWSER_CREATOR_IMPL_H_

// Make QoraiStartupBrowserCreatorImpl a friend class, to give it access to
// StartupBrowserCreatorImpl's private attributes.
#define browser_creator_ \
  browser_creator_;      \
  friend class QoraiStartupBrowserCreatorImpl

// Make MaybeShowNonMilestoneUpdateToast virtual member instead of static,
// because we want to override it in QoraiStartupBrowserCreatorImpl to never
// show the toast.
#define MaybeShowNonMilestoneUpdateToast \
  Unused();                              \
  virtual void MaybeShowNonMilestoneUpdateToast

#include <chrome/browser/ui/startup/startup_browser_creator_impl.h>  // IWYU pragma: export
#undef MaybeShowNonMilestoneUpdateToast
#undef browser_creator_

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_STARTUP_STARTUP_BROWSER_CREATOR_IMPL_H_
