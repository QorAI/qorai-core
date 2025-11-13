/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/qorai_tab_strip_model_delegate.h"

#include <algorithm>

#include "qorai/browser/ui/tabs/qorai_tab_prefs.h"
#include "qorai/browser/ui/tabs/features.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "components/prefs/pref_service.h"

namespace chrome {

bool QoraiTabStripModelDelegate::CanMoveTabsToWindow(
    const std::vector<int>& indices) {
  if (!base::FeatureList::IsEnabled(tabs::features::kQoraiSharedPinnedTabs) ||
      !browser_->profile()->GetPrefs()->GetBoolean(
          qorai_tabs::kSharedPinnedTab)) {
    return BrowserTabStripModelDelegate::CanMoveTabsToWindow(indices);
  }

  // Shared pinned tabs shouldn't be moved.
  return std::ranges::none_of(indices, [this](const auto& index) {
    return browser_->tab_strip_model()->IsTabPinned(index);
  });
}

}  // namespace chrome
