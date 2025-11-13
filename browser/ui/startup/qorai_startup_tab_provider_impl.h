/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_STARTUP_QORAI_STARTUP_TAB_PROVIDER_IMPL_H_
#define QORAI_BROWSER_UI_STARTUP_QORAI_STARTUP_TAB_PROVIDER_IMPL_H_

#include "chrome/browser/ui/startup/startup_tab_provider.h"

class StartupBrowserCreator;

class QoraiStartupTabProviderImpl : public StartupTabProviderImpl {
 public:
  QoraiStartupTabProviderImpl() = default;
  QoraiStartupTabProviderImpl(const QoraiStartupTabProviderImpl&) = delete;
  QoraiStartupTabProviderImpl& operator=(const QoraiStartupTabProviderImpl&) =
      delete;

  // StartupTabProvider:
  StartupTabs GetDistributionFirstRunTabs(
      StartupBrowserCreator* browser_creator) const override;
};

#endif  // QORAI_BROWSER_UI_STARTUP_QORAI_STARTUP_TAB_PROVIDER_IMPL_H_
