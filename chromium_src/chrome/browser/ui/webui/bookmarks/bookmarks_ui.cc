/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/navigation_bar_data_provider.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/buildflags.h"
#include "content/public/browser/web_ui_data_source.h"

namespace {

void QoraiAddBookmarksResources(content::WebUIDataSource* source,
                                Profile* profile) {
  NavigationBarDataProvider::Initialize(source, profile);
  source->AddLocalizedString("emptyList",
                             IDS_QORAI_BOOKMARK_MANAGER_EMPTY_LIST);
}

}  // namespace

#define QORAI_CREATE_BOOKMARKS_UI_HTML_SOURCE \
  QoraiAddBookmarksResources(source, profile);

#include <chrome/browser/ui/webui/bookmarks/bookmarks_ui.cc>

#undef QORAI_CREATE_BOOKMARKS_UI_HTML_SOURCE
