// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "chrome/browser/banners/app_banner_manager_desktop.h"

#include "qorai/components/constants/webui_url_constants.h"
#include "chrome/browser/banners/test_app_banner_manager_desktop.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "content/public/common/url_constants.h"
#include "content/public/test/browser_test.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace webapps {

class AppBannerManagerDesktopBrowserTest_Qorai : public InProcessBrowserTest {
 public:
  AppBannerManagerDesktopBrowserTest_Qorai() = default;
  ~AppBannerManagerDesktopBrowserTest_Qorai() override = default;

  AppBannerManagerDesktopBrowserTest_Qorai(
      const AppBannerManagerDesktopBrowserTest_Qorai&) = delete;
  AppBannerManagerDesktopBrowserTest_Qorai& operator=(
      const AppBannerManagerDesktopBrowserTest_Qorai&) = delete;

  void SetUp() override {
    TestAppBannerManagerDesktop::SetUp();
    InProcessBrowserTest::SetUp();
  }
};

IN_PROC_BROWSER_TEST_F(AppBannerManagerDesktopBrowserTest_Qorai,
                       InstallableWebUI) {
  TestAppBannerManagerDesktop* manager =
      TestAppBannerManagerDesktop::FromWebContents(
          browser()->tab_strip_model()->GetActiveWebContents());

  // Iterate through kInstallablePWAWebUIHosts and navigate to each one,
  // checking that it's installable and promotable. If they have a bad
  // webmanifest or aren't on the ChromeUI scheme, the test should fail.
  for (const auto& host : kInstallablePWAWebUIHosts) {
    SCOPED_TRACE(testing::Message() << "Host: " << host);

    ASSERT_TRUE(ui_test_utils::NavigateToURL(
        browser(), GURL(base::StrCat({"chrome://", host}))));

    ASSERT_TRUE(manager->WaitForInstallableCheck());

    EXPECT_EQ(InstallableWebAppCheckResult::kYes_Promotable,
              manager->GetInstallableWebAppCheckResult());
  }
}

}  // namespace webapps
