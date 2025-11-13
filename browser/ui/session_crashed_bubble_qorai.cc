/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/metrics/metrics_reporting_util.h"
#include "qorai/browser/ui/browser_dialogs.h"
#include "chrome/browser/ui/browser_window/public/browser_window_interface.h"
#include "chrome/browser/ui/session_crashed_bubble.h"

// static
void SessionCrashedBubble::ShowIfNotOffTheRecordProfileQorai(
    BrowserWindowInterface* browser,
    bool skip_tab_checking) {
  // If crash report permission ask dialog is launched, tab restore bubble will
  // be shown after closing aks dialog.
  if (ShouldShowCrashReportPermissionAskDialog()) {
    qorai::ShowCrashReportPermissionAskDialog(
        browser->GetBrowserForMigrationOnly());
    return;
  }

  ShowIfNotOffTheRecordProfile(browser, skip_tab_checking);
}
