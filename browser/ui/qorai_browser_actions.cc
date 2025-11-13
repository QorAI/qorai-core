/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/qorai_browser_actions.h"

#include "base/types/to_address.h"
#include "qorai/components/ai_chat/core/browser/utils.h"
#include "qorai/components/playlist/core/common/features.h"
#include "qorai/components/vector_icons/vector_icons.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser_window/public/browser_window_interface.h"
#include "chrome/browser/ui/views/side_panel/side_panel_action_callback.h"
#include "chrome/browser/ui/views/side_panel/side_panel_entry_id.h"
#include "chrome/browser/ui/views/side_panel/side_panel_entry_key.h"
#include "components/grit/qorai_components_strings.h"
#include "ui/actions/actions.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/gfx/vector_icon_types.h"

namespace {

actions::ActionItem::ActionItemBuilder SidePanelAction(
    SidePanelEntryId id,
    int title_id,
    int tooltip_id,
    const gfx::VectorIcon& icon,
    actions::ActionId action_id,
    BrowserWindowInterface* bwi,
    bool is_pinnable) {
  return actions::ActionItem::Builder(
             CreateToggleSidePanelActionCallback(SidePanelEntryKey(id), bwi))
      .SetActionId(action_id)
      .SetText(l10n_util::GetStringUTF16(title_id))
      .SetTooltipText(l10n_util::GetStringUTF16(tooltip_id))
      .SetImage(ui::ImageModel::FromVectorIcon(icon, ui::kColorIcon))
      .SetProperty(actions::kActionItemPinnableKey, is_pinnable);
}

}  // namespace

QoraiBrowserActions::QoraiBrowserActions(BrowserWindowInterface* bwi)
    : BrowserActions(bwi) {}

QoraiBrowserActions::~QoraiBrowserActions() = default;

void QoraiBrowserActions::InitializeBrowserActions() {
  BrowserActions::InitializeBrowserActions();
  BrowserWindowInterface* const bwi = base::to_address(bwi_);

  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
    root_action_item_->AddChild(
        SidePanelAction(
            SidePanelEntryId::kPlaylist, IDS_SIDEBAR_PLAYLIST_ITEM_TITLE,
            IDS_SIDEBAR_PLAYLIST_ITEM_TITLE, kQoraProductPlaylistIcon,
            kActionSidePanelShowPlaylist, bwi, true)
            .Build());
  }

  if (ai_chat::IsAIChatEnabled(profile_->GetPrefs())) {
    root_action_item_->AddChild(
        SidePanelAction(SidePanelEntryId::kChatUI, IDS_CHAT_UI_TITLE,
                        IDS_CHAT_UI_TITLE, kQoraProductQoraiQoraIcon,
                        kActionSidePanelShowChatUI, bwi, true)
            .Build());
  }
}
