/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/test/scoped_feature_list.h"
#include "qorai/app/qorai_command_ids.h"
#include "qorai/components/qorai_vpn/common/features.h"
#include "qorai/components/skus/common/features.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_command_controller.h"
#include "chrome/browser/ui/test/test_browser_dialog.h"
#include "content/public/test/browser_test.h"

class QoraiVPNPanelControllerTest : public DialogBrowserTest {
 public:
  QoraiVPNPanelControllerTest() {
    scoped_feature_list_.InitWithFeatures(
        {skus::features::kSkusFeature, qorai_vpn::features::kQoraiVPN}, {});
  }

  ~QoraiVPNPanelControllerTest() override = default;

  // TestBrowserUi:
  void ShowUi(const std::string& name) override {
    browser()->command_controller()->ExecuteCommand(IDC_SHOW_QORAI_VPN_PANEL);
  }

  base::test::ScopedFeatureList scoped_feature_list_;
};

IN_PROC_BROWSER_TEST_F(QoraiVPNPanelControllerTest, InvokeUi_Dialog) {
  ShowAndVerifyUi();
}
