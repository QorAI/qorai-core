/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_BROWSER_MAIN_PARTS_MAC_H_
#define QORAI_BROWSER_QORAI_BROWSER_MAIN_PARTS_MAC_H_

#include <memory>

#include "base/feature_list.h"
#include "qorai/browser/upgrade_when_idle/upgrade_when_idle.h"
#include "chrome/browser/chrome_browser_main_mac.h"

namespace qorai {
BASE_DECLARE_FEATURE(kUpgradeWhenIdle);
}

class QoraiBrowserMainPartsMac : public ChromeBrowserMainPartsMac {
 public:
  QoraiBrowserMainPartsMac(bool is_integration_test, StartupData* startup_data);
  ~QoraiBrowserMainPartsMac() override;

 private:
  // ChromeBrowserMainPartsMac overrides:
  void PreCreateMainMessageLoop() override;
  void PostProfileInit(Profile* profile, bool is_initial_profile) override;
  void PostMainMessageLoopRun() override;

  std::unique_ptr<qorai::UpgradeWhenIdle> upgrade_when_idle_;
};

#endif  // QORAI_BROWSER_QORAI_BROWSER_MAIN_PARTS_MAC_H_
