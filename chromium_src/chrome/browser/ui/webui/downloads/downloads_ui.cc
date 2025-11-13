/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/navigation_bar_data_provider.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/grit/generated_resources.h"

namespace {

void QoraiCustomizeDownloadsDataSource(content::WebUIDataSource* source,
                                       Profile* profile) {
  NavigationBarDataProvider::Initialize(source, profile);
}

}  // namespace

#if !defined(IDS_DOWNLOAD_HISTORY_TITLE)
#error IDS_DOWNLOAD_HISTORY_TITLE is no longer defined in Chromium
#endif
#undef IDS_DOWNLOAD_HISTORY_TITLE
#define IDS_DOWNLOAD_HISTORY_TITLE IDS_DOWNLOADS_TITLE

#define QORAI_CREATE_DOWNLOADS_UI_HTML_SOURCE \
  QoraiCustomizeDownloadsDataSource(source, profile);

#include <chrome/browser/ui/webui/downloads/downloads_ui.cc>
#undef QORAI_CREATE_DOWNLOADS_UI_HTML_SOURCE
#undef IDS_DOWNLOAD_HISTORY_TITLE
