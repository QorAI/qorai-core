/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_CHROME_BROWSER_MAIN_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_CHROME_BROWSER_MAIN_H_

#define ChromeBrowserMainParts ChromeBrowserMainParts_ChromiumImpl
#include <chrome/browser/chrome_browser_main.h>  // IWYU pragma: export
#undef ChromeBrowserMainParts

class ChromeBrowserMainParts : public ChromeBrowserMainParts_ChromiumImpl {
 public:
  ChromeBrowserMainParts(bool is_integration_test, StartupData* startup_data);

  ChromeBrowserMainParts(const ChromeBrowserMainParts&) = delete;
  ChromeBrowserMainParts& operator=(const ChromeBrowserMainParts&) = delete;
  ~ChromeBrowserMainParts() override;

  int PreMainMessageLoopRun() override;
  void PreBrowserStart() override;
  void PostBrowserStart() override;
  void PreShutdown() override;
  void PreProfileInit() override;
  void PostProfileInit(Profile* profile, bool is_initial_profile) override;

 private:
  friend class ChromeBrowserMainExtraPartsTor;
};

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_CHROME_BROWSER_MAIN_H_
