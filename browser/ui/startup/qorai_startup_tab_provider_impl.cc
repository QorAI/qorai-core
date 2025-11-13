/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/startup/qorai_startup_tab_provider_impl.h"

#include "qorai/components/constants/webui_url_constants.h"
#include "chrome/browser/first_run/first_run.h"
#include "chrome/browser/ui/startup/startup_tab.h"

StartupTabs QoraiStartupTabProviderImpl::GetDistributionFirstRunTabs(
    StartupBrowserCreator* browser_creator) const {
  StartupTabs tabs =
      StartupTabProviderImpl::GetDistributionFirstRunTabs(browser_creator);
  if (first_run::IsChromeFirstRun()) {
    tabs.emplace_back(GURL(kWelcomeURL));
  }
  return tabs;
}
