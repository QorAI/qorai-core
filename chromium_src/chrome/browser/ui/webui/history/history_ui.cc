/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/navigation_bar_data_provider.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/buildflags.h"
#include "content/public/browser/web_ui_data_source.h"

namespace {

void QoraiCustomizeHistoryDataSource(content::WebUIDataSource* source,
                                     Profile* profile) {
  NavigationBarDataProvider::Initialize(source, profile);
}

}  // namespace

#define QORAI_CREATE_HISTORY_UI_HTML_SOURCE \
  QoraiCustomizeHistoryDataSource(source, profile);

#include <chrome/browser/ui/webui/history/history_ui.cc>
#undef QORAI_CREATE_HISTORY_UI_HTML_SOURCE
