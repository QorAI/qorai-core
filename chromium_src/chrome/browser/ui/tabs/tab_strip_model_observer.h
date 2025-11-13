// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_TABS_TAB_STRIP_MODEL_OBSERVER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_TABS_TAB_STRIP_MODEL_OBSERVER_H_

// Add TabCustomTitleChanged() callback to TabStripModelObserver.
// QoraiBrowser will make sure that the custom title is stored in the session
// service so that it can be restored even after browser restarts.
#define TabPinnedStateChanged                                              \
  TabCustomTitleChanged(content::WebContents* contents,                    \
                        const std::optional<std::string>& custom_title) {} \
  virtual void TabPinnedStateChanged

#include <chrome/browser/ui/tabs/tab_strip_model_observer.h>  // IWYU pragma: export

#undef TabPinnedStateChanged

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_TABS_TAB_STRIP_MODEL_OBSERVER_H_
