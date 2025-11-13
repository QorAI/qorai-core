/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/test/base/qorai_test_launcher_delegate.h"

#include "build/build_config.h"

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/app/qorai_main_delegate.h"
#include "qorai/browser/ui/qorai_browser.h"
#endif

#if BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
#include "chrome/browser/first_run/first_run_internal.h"
#endif

QoraiTestLauncherDelegate::QoraiTestLauncherDelegate(
    ChromeTestSuiteRunner* runner)
    : ChromeTestLauncherDelegate(runner) {
  // Suppress first run dialg during the test. It can cause some tests timeout.
  // It's not used on Windows.
#if BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
  first_run::internal::ForceFirstRunDialogShownForTesting(false);
#endif

#if !BUILDFLAG(IS_ANDROID)
  // Suppress browser window closing dialog during the test.
  // It can cause some tests timeout.
  QoraiBrowser::SuppressBrowserWindowClosingDialogForTesting(true);
#endif
}

QoraiTestLauncherDelegate::~QoraiTestLauncherDelegate() = default;
