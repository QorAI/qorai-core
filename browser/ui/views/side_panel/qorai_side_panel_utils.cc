/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ai_chat/ai_chat_service_factory.h"
#include "qorai/browser/ui/side_panel/ai_chat/ai_chat_side_panel_utils.h"
#include "qorai/browser/ui/views/side_panel/ai_chat/ai_chat_side_panel_web_view.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/views/side_panel/side_panel_registry.h"

namespace qorai {

// Register here for an entry that is used for all tabs and its life time is
// tied with tab. If it has specific life time, use separated manager for
// registering it.
void RegisterContextualSidePanel(SidePanelRegistry* registry,
                                 content::WebContents* web_contents) {
  content::BrowserContext* context = web_contents->GetBrowserContext();
  // Disable tab-scoped panel for content agent profiles.
  // TODO(https://github.com/qorai/qorai-browser/issues/48526): Remove
  // this when the feature flag is removed.
  if (ai_chat::AIChatServiceFactory::GetForBrowserContext(context) &&
      !ai_chat::ShouldSidePanelBeGlobal(Profile::FromBrowserContext(context))) {
    // If |registry| already has it, it's no-op.
    registry->Register(std::make_unique<SidePanelEntry>(
        SidePanelEntry::Key(SidePanelEntry::Id::kChatUI),
        base::BindRepeating(&AIChatSidePanelWebView::CreateView,
                            Profile::FromBrowserContext(context),
                            /*is_tab_associated=*/true),
        /*default_content_width_callback=*/base::NullCallback()));
  }
}

}  // namespace qorai
