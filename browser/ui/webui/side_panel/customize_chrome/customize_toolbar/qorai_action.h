// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_SIDE_PANEL_CUSTOMIZE_CHROME_CUSTOMIZE_TOOLBAR_QORAI_ACTION_H_
#define QORAI_BROWSER_UI_WEBUI_SIDE_PANEL_CUSTOMIZE_CHROME_CUSTOMIZE_TOOLBAR_QORAI_ACTION_H_

#include "base/containers/fixed_flat_map.h"
#include "qorai/components/ai_chat/core/common/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/vector_icons/vector_icons.h"
#include "chrome/browser/ui/webui/side_panel/customize_chrome/customize_toolbar/customize_toolbar.mojom.h"
#include "components/grit/qorai_components_strings.h"
#include "ui/gfx/vector_icon_types.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/pref_names.h"
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)

namespace customize_chrome {

// This struct holds information about each Qorai specific action that will be
// added to the toolbar customization list. Not only it contains the UI data,
// but also the pref name that controls the visibility of the action.
struct QoraiAction {
  const side_panel::customize_chrome::mojom::ActionId id;
  const int display_name_resource_id;
  const side_panel::customize_chrome::mojom::ActionId anchor;
  const side_panel::customize_chrome::mojom::CategoryId category;
  const char* pref_name;
  // RAW_PTR_EXCLUSION: #global-scope
  RAW_PTR_EXCLUSION const gfx::VectorIcon& icon;
};

inline constexpr QoraiAction kShowAddBookmarkButton = {
    .id = side_panel::customize_chrome::mojom::ActionId::kShowAddBookmarkButton,
    .display_name_resource_id = IDS_CUSTOMIZE_TOOLBAR_TOGGLE_BOOKMARK,
    .anchor = side_panel::customize_chrome::mojom::ActionId::kForward,
    .category = side_panel::customize_chrome::mojom::CategoryId::kNavigation,
    .pref_name = kShowBookmarksButton,
    .icon = kQoraBrowserBookmarkNormalIcon};

inline constexpr QoraiAction kShowSidePanelAction = {
    .id = side_panel::customize_chrome::mojom::ActionId::kShowSidePanel,
    .display_name_resource_id = IDS_CUSTOMIZE_TOOLBAR_TOGGLE_SIDEBAR,
    .anchor =
        side_panel::customize_chrome::mojom::ActionId::kNewIncognitoWindow,
    .category = side_panel::customize_chrome::mojom::CategoryId::kNavigation,
    .pref_name = kShowSidePanelButton,
    .icon = kQoraBrowserSidebarRightIcon};

inline constexpr QoraiAction kShowWalletAction = {
    .id = side_panel::customize_chrome::mojom::ActionId::kShowWallet,
    .display_name_resource_id = IDS_CUSTOMIZE_TOOLBAR_TOGGLE_WALLET,
    .anchor = side_panel::customize_chrome::mojom::ActionId::kTabSearch,
    .category = side_panel::customize_chrome::mojom::CategoryId::kNavigation,
    .pref_name = kShowWalletIconOnToolbar,
    .icon = kQoraProductQoraiWalletIcon};

inline constexpr QoraiAction kShowAIChatAction = {
    .id = side_panel::customize_chrome::mojom::ActionId::kShowAIChat,
    .display_name_resource_id = IDS_CUSTOMIZE_TOOLBAR_TOGGLE_AI_CHAT,
    .anchor = side_panel::customize_chrome::mojom::ActionId::kTabSearch,
    .category = side_panel::customize_chrome::mojom::CategoryId::kNavigation,
    .pref_name = ai_chat::prefs::kQoraiAIChatShowToolbarButton,
    .icon = kQoraProductQoraiQoraIcon};

#if BUILDFLAG(ENABLE_QORAI_VPN)
inline constexpr QoraiAction kShowVPNAction = {
    .id = side_panel::customize_chrome::mojom::ActionId::kShowVPN,
    .display_name_resource_id = IDS_CUSTOMIZE_TOOLBAR_TOGGLE_VPN,
    .anchor = side_panel::customize_chrome::mojom::ActionId::kTabSearch,
    .category = side_panel::customize_chrome::mojom::CategoryId::kNavigation,
    .pref_name = qorai_vpn::prefs::kQoraiVPNShowButton,
    .icon = kQoraProductVpnIcon};
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)

inline constexpr QoraiAction kShowReward = {
    .id = side_panel::customize_chrome::mojom::ActionId::kShowReward,
    .display_name_resource_id = IDS_CUSTOMIZE_TOOLBAR_TOGGLE_REWARD,
    .anchor = side_panel::customize_chrome::mojom::ActionId::
        kShowReward,  // assign id of itself to append to the end of the list
    .category = side_panel::customize_chrome::mojom::CategoryId::kAddressBar,
    .pref_name = qorai_rewards::prefs::kShowLocationBarButton,
    .icon = kQoraProductBatOutlineIcon};

inline constexpr QoraiAction kShowQoraiNews = {
    .id = side_panel::customize_chrome::mojom::ActionId::kShowQoraiNews,
    .display_name_resource_id = IDS_CUSTOMIZE_TOOLBAR_TOGGLE_QORAI_NEWS,
    .anchor = side_panel::customize_chrome::mojom::ActionId::
        kShowQoraiNews,  // assign id of itself to append to the end of the list
    .category = side_panel::customize_chrome::mojom::CategoryId::kAddressBar,
    .pref_name = qorai_news::prefs::kShouldShowToolbarButton,
    .icon = kQoraRssIcon};

inline constexpr auto kQoraiActions =
    base::MakeFixedFlatMap<side_panel::customize_chrome::mojom::ActionId,
                           const QoraiAction*>({
        {kShowAddBookmarkButton.id, &kShowAddBookmarkButton},
        {kShowSidePanelAction.id, &kShowSidePanelAction},
        {kShowWalletAction.id, &kShowWalletAction},
        {kShowAIChatAction.id, &kShowAIChatAction},
#if BUILDFLAG(ENABLE_QORAI_VPN)
        {kShowVPNAction.id, &kShowVPNAction},
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)
        {kShowReward.id, &kShowReward},
        {kShowQoraiNews.id, &kShowQoraiNews},
    });

}  // namespace customize_chrome

#endif  // QORAI_BROWSER_UI_WEBUI_SIDE_PANEL_CUSTOMIZE_CHROME_CUSTOMIZE_TOOLBAR_QORAI_ACTION_H_
