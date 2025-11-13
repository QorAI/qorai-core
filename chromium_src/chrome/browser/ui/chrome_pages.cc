/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// It has caller in the same file
#define QORAI_GET_SETTINGS_URL \
  GURL GetSettingsUrl_ChromiumImpl(std::string_view sub_page) {
// QORAI_GET_SETTINGS_URL

#include <chrome/browser/ui/chrome_pages.cc>

#undef QORAI_GET_SETTINGS_URL

#include "qorai/components/constants/webui_url_constants.h"

namespace chrome {

GURL GetSettingsUrl(std::string_view sub_page) {
  if (sub_page == chrome::kSyncSetupSubPage)
    return chrome::GetSettingsUrl(kQoraiSyncSetupPath);
  return GetSettingsUrl_ChromiumImpl(sub_page);
}

}  // namespace chrome
