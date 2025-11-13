/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/prefs/qorai_pref_service_incognito_allowlist.h"

#include <array>

#include "base/containers/span.h"
#include "base/strings/cstring_view.h"
#include "qorai/browser/ui/bookmark/qorai_bookmark_prefs.h"
#include "qorai/components/ai_chat/core/common/pref_names.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/constants/pref_names.h"
#include "build/build_config.h"
#include "chrome/common/pref_names.h"

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/tabs/qorai_tab_prefs.h"
#endif

#if defined(TOOLKIT_VIEWS)
#include "qorai/components/sidebar/browser/pref_names.h"
#endif

namespace qorai {

base::span<const base::cstring_view> GetQoraiPersistentPrefNames() {
  static constexpr auto kAllowlist = std::to_array<base::cstring_view>({
      kQoraiAutofillPrivateWindows,
#if !BUILDFLAG(IS_ANDROID)
      kShowWalletIconOnToolbar,
      prefs::kSidePanelHorizontalAlignment,
      kTabMuteIndicatorNotClickable,
      qorai_tabs::kVerticalTabsExpandedWidth,
      qorai_tabs::kVerticalTabsEnabled,
      qorai_tabs::kVerticalTabsCollapsed,
      qorai_tabs::kVerticalTabsFloatingEnabled,
      qorai_tabs::kVerticalTabsShowTitleOnWindow,
      qorai_tabs::kVerticalTabsOnRight,
      qorai_tabs::kVerticalTabsShowScrollbar,
      qorai_tabs::kSharedPinnedTab,
      qorai_tabs::kTreeTabsEnabled,
#endif
#if defined(TOOLKIT_VIEWS)
      sidebar::kSidePanelWidth,
#endif
      ai_chat::prefs::kLastAcceptedDisclaimer,
      ai_chat::prefs::kQoraiChatAutocompleteProviderEnabled,
      qorai::bookmarks::prefs::kShowAllBookmarksButton,
  });

  return kAllowlist;
}

}  // namespace qorai
