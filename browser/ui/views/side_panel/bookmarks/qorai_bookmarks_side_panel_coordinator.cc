/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/side_panel/bookmarks/qorai_bookmarks_side_panel_coordinator.h"

#include "base/functional/bind.h"
#include "qorai/browser/ui/views/side_panel/qorai_bookmarks_side_panel_view.h"
#include "chrome/browser/ui/views/side_panel/side_panel_entry.h"
#include "chrome/browser/ui/views/side_panel/side_panel_registry.h"

QoraiBookmarksSidePanelCoordinator::~QoraiBookmarksSidePanelCoordinator() =
    default;

void QoraiBookmarksSidePanelCoordinator::CreateAndRegisterEntry(
    SidePanelRegistry* global_registry) {
  global_registry->Register(std::make_unique<SidePanelEntry>(
      SidePanelEntry::Key(SidePanelEntry::Id::kBookmarks),
      base::BindRepeating(
          &QoraiBookmarksSidePanelCoordinator::CreateBookmarksPanelView,
          base::Unretained(this)),
      /*default_content_width_callback=*/base::NullCallback()));
}

std::unique_ptr<views::View>
QoraiBookmarksSidePanelCoordinator::CreateBookmarksPanelView(
    SidePanelEntryScope& scope) {
  return std::make_unique<QoraiBookmarksSidePanelView>(scope);
}
