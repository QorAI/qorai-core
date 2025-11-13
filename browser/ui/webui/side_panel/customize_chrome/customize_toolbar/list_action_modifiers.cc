// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/side_panel/customize_chrome/customize_toolbar/list_action_modifiers.h"

#include <utility>
#include <vector>

#include "base/check_is_test.h"
#include "base/containers/contains.h"
#include "base/containers/fixed_flat_set.h"
#include "base/strings/utf_string_conversions.h"
#include "qorai/browser/qorai_rewards/rewards_util.h"
#include "qorai/browser/ui/webui/side_panel/customize_chrome/customize_toolbar/qorai_action.h"
#include "qorai/components/ai_chat/core/browser/utils.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/webui/util/image_util.h"
#include "components/prefs/pref_service.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/models/image_model.h"
#include "ui/color/color_provider.h"
#include "ui/display/screen.h"
#include "ui/gfx/image/image_skia.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/vpn_utils.h"
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)

namespace customize_chrome {

namespace {

void AddActionsForAddressBarCategory(Profile* profile,
                                     std::vector<QoraiAction>& qorai_actions) {
  if (qorai_rewards::IsSupportedForProfile(profile)) {
    qorai_actions.push_back(kShowReward);
  }

  if (!profile->GetPrefs()->GetBoolean(
          qorai_news::prefs::kQoraiNewsDisabledByPolicy)) {
    qorai_actions.push_back(kShowQoraiNews);
  }
}

}  // namespace

using side_panel::customize_chrome::mojom::ActionId;
using side_panel::customize_chrome::mojom::ActionPtr;
using side_panel::customize_chrome::mojom::Category;
using side_panel::customize_chrome::mojom::CategoryId;
using side_panel::customize_chrome::mojom::CategoryPtr;

std::vector<CategoryPtr> AppendQoraiSpecificCategories(
    content::WebContents& web_contents,
    std::vector<CategoryPtr> categories) {
  // Add a new "Address bar" category.
  std::vector<QoraiAction> qorai_actions;
  AddActionsForAddressBarCategory(
      Profile::FromBrowserContext(web_contents.GetBrowserContext()),
      qorai_actions);
  if (qorai_actions.empty()) {
    // In case we don't have any Qorai actions for Address bar category, we
    // don't need to add the category.
    return categories;
  }

  categories.push_back(Category::New(
      CategoryId::kAddressBar,
      l10n_util::GetStringUTF8(IDS_CUSTOMIZE_TOOLBAR_CATEGORY_ADDRESS_BAR)));
  return categories;
}

std::vector<ActionPtr> FilterUnsupportedChromiumActions(
    std::vector<ActionPtr> actions) {
  // Filter out unsupported Chromium actions.
  std::erase_if(actions, [](const ActionPtr& action) -> bool {
    static constexpr auto kUnsupportedChromiumActions =
        base::MakeFixedFlatSet<ActionId>({
            ActionId::kShowPaymentMethods,
            ActionId::kShowTranslate,
            ActionId::kShowReadAnything,
            ActionId::kShowAddresses,
        });
    return base::Contains(kUnsupportedChromiumActions, action->id);
  });
  return actions;
}

std::vector<ActionPtr> ApplyQoraiSpecificModifications(
    content::WebContents& web_contents,
    std::vector<ActionPtr> actions) {
  using side_panel::customize_chrome::mojom::Action;
  using side_panel::customize_chrome::mojom::CategoryId;

  // 1. Move an existing Chromium actions to where we want them to be.
  // Find kTabSearch action and move it to after kNewIncognitoWindow.
  auto get_action_id = [](const ActionPtr& action) { return action->id; };
  {
    auto tab_search_it =
        std::ranges::find(actions, ActionId::kTabSearch, get_action_id);
    CHECK(tab_search_it != actions.end()) << "Tab Search action not found";
    auto tab_search_action = std::move(*tab_search_it);
    tab_search_action->category = CategoryId::kNavigation;
    actions.erase(tab_search_it);
    auto incognito_action_it = std::ranges::find(
        actions, ActionId::kNewIncognitoWindow, get_action_id);
    CHECK(incognito_action_it != actions.end())
        << "New Incognito Window action not found";
    actions.insert(incognito_action_it + 1, std::move(tab_search_action));
  }

  // 2. Update icons/strings for existing actions.
  const auto& cp = web_contents.GetColorProvider();

  float scale_factor = 1.0f;
  if (auto* screen = display::Screen::Get()) {
    scale_factor =
        screen->GetDisplayNearestWindow(web_contents.GetTopLevelNativeWindow())
            .device_scale_factor();
  } else {
    CHECK_IS_TEST();
  }

  auto get_icon_url = [&cp, scale_factor](const gfx::VectorIcon& icon) {
    return GURL(webui::EncodePNGAndMakeDataURI(
        ui::ImageModel::FromVectorIcon(icon, ui::kColorSysOnSurface)
            .Rasterize(&cp),
        scale_factor));
  };

  {
    auto new_incognito_window_it = std::ranges::find(
        actions, ActionId::kNewIncognitoWindow, get_action_id);
    CHECK(new_incognito_window_it != actions.end())
        << "New Incognito Window action not found";
    (*new_incognito_window_it)->icon_url =
        get_icon_url(kQoraProductPrivateWindowIcon);
  }

  {
    auto bookmark_panel_it =
        std::ranges::find(actions, ActionId::kShowBookmarks, get_action_id);
    CHECK(bookmark_panel_it != actions.end())
        << "Bookmark panel action not found";
    (*bookmark_panel_it)->display_name =
        l10n_util::GetStringUTF8(IDS_CUSTOMIZE_TOOLBAR_TOGGLE_BOOKMARKS_PANEL);
  }

  // 3. Add Qorai specific actions.
  // Qorai specific actions
  // Navigation
  //   kShowAddBookmarkButton,
  //   kShowSidePanel,
  //   kShowWallet,
  //   kShowAIChat,
  //   kShowVPN,
  // Address bar
  //   kShowReward
  //   kShowQoraiNews
  auto* prefs = user_prefs::UserPrefs::Get(web_contents.GetBrowserContext());
  CHECK(prefs) << "Browser context does not have prefs";

  std::vector<QoraiAction> qorai_actions;
  qorai_actions.push_back(kShowAddBookmarkButton);
  qorai_actions.push_back(kShowSidePanelAction);

  // Followings are dynamic actions: anchor to TabSearchButton and append to
  // action list in reverse order.
#if BUILDFLAG(ENABLE_QORAI_VPN)
  if (qorai_vpn::IsQoraiVPNEnabled(web_contents.GetBrowserContext())) {
    qorai_actions.push_back(kShowVPNAction);
  }
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)

  if (ai_chat::IsAIChatEnabled(prefs)) {
    qorai_actions.push_back(kShowAIChatAction);
  }

  if (qorai_wallet::IsNativeWalletEnabled()) {
    qorai_actions.push_back(kShowWalletAction);
  }

  AddActionsForAddressBarCategory(
      Profile::FromBrowserContext(web_contents.GetBrowserContext()),
      qorai_actions);

  for (const auto& qorai_action : qorai_actions) {
    // Find the anchor action. If anchor action is not found, just append to the
    // end of the list.
    auto anchor_it =
        std::ranges::find(actions, qorai_action.anchor, get_action_id);

    // Create the new action.
    auto new_action = Action::New(
        qorai_action.id,
        base::UTF16ToUTF8(
            l10n_util::GetStringUTF16(qorai_action.display_name_resource_id)),
        /*pinned=*/prefs->GetBoolean(qorai_action.pref_name),
        /*has_enterprise_controlled_pinned_state=*/false, qorai_action.category,
        get_icon_url(qorai_action.icon));

    // Insert the new action after the anchor or end of the list.
    actions.insert(anchor_it == actions.end() ? actions.end() : anchor_it + 1,
                   std::move(new_action));
  }

  return actions;
}

}  // namespace customize_chrome
