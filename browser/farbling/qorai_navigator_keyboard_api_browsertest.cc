/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "base/path_service.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/constants/qorai_paths.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "net/dns/mock_host_resolver.h"
#include "url/gurl.h"

using qorai_shields::ControlType;

namespace {

constexpr char kGetLayoutMapScript[] =
    R"(navigator.keyboard.getLayoutMap instanceof Function)";

}  // namespace

class QoraiNavigatorKeyboardAPIBrowserTest : public InProcessBrowserTest {
 public:
  QoraiNavigatorKeyboardAPIBrowserTest()
      : https_server_(net::EmbeddedTestServer::TYPE_HTTPS) {}

  QoraiNavigatorKeyboardAPIBrowserTest(
      const QoraiNavigatorKeyboardAPIBrowserTest&) = delete;
  QoraiNavigatorKeyboardAPIBrowserTest& operator=(
      const QoraiNavigatorKeyboardAPIBrowserTest&) = delete;

  ~QoraiNavigatorKeyboardAPIBrowserTest() override = default;

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    base::FilePath test_data_dir;
    base::PathService::Get(qorai::DIR_TEST_DATA, &test_data_dir);
    https_server_.SetSSLConfig(net::EmbeddedTestServer::CERT_TEST_NAMES);
    https_server_.ServeFilesFromDirectory(test_data_dir);
    EXPECT_TRUE(https_server_.Start());
    top_level_page_url_ = https_server_.GetURL("a.test", "/");
    test_url_ = https_server_.GetURL("a.test", "/simple.html");
    host_resolver()->AddRule("*", "127.0.0.1");
  }

 protected:
  net::EmbeddedTestServer https_server_;

  const GURL& test_url() { return test_url_; }

  HostContentSettingsMap* content_settings() {
    return HostContentSettingsMapFactory::GetForProfile(browser()->profile());
  }

  void AllowFingerprinting() {
    qorai_shields::SetFingerprintingControlType(
        content_settings(), ControlType::ALLOW, top_level_page_url_);
  }

  void BlockFingerprinting() {
    qorai_shields::SetFingerprintingControlType(
        content_settings(), ControlType::BLOCK, top_level_page_url_);
  }

  void SetFingerprintingDefault() {
    qorai_shields::SetFingerprintingControlType(
        content_settings(), ControlType::DEFAULT, top_level_page_url_);
  }

  content::WebContents* contents() {
    return browser()->tab_strip_model()->GetActiveWebContents();
  }

  void EnableWebcompatException() {
    qorai_shields::SetWebcompatEnabled(
        content_settings(),
        ContentSettingsType::QORAI_WEBCOMPAT_HARDWARE_CONCURRENCY, true,
        top_level_page_url_, nullptr);
  }

 private:
  GURL top_level_page_url_;
  GURL test_url_;
};

IN_PROC_BROWSER_TEST_F(QoraiNavigatorKeyboardAPIBrowserTest,
                       TestKeyboardAPIAvilability) {
  // Fingerprinting level: off
  // get real navigator.keyboard.getLayoutMap key
  AllowFingerprinting();
  EXPECT_TRUE(ui_test_utils::NavigateToURL(browser(), test_url()));
  EXPECT_EQ(true, EvalJs(contents(), kGetLayoutMapScript));

  // Fingerprinting level: standard (default)
  // navigator.keyboard will be null
  SetFingerprintingDefault();
  EXPECT_TRUE(ui_test_utils::NavigateToURL(browser(), test_url()));
  auto result_standard = EvalJs(contents(), kGetLayoutMapScript);
  EXPECT_THAT(result_standard,
              content::EvalJsResult::ErrorIs(testing::HasSubstr(
                  "Cannot read properties of null (reading 'getLayoutMap')")));

  // Fingerprinting level: blocked (same as standard for this test)
  BlockFingerprinting();
  EXPECT_TRUE(ui_test_utils::NavigateToURL(browser(), test_url()));
  auto result_blocked = EvalJs(contents(), kGetLayoutMapScript);
  EXPECT_THAT(result_blocked,
              content::EvalJsResult::ErrorIs(testing::HasSubstr(
                  "Cannot read properties of null (reading 'getLayoutMap')")));

  // Fingerprinting level: default, but with webcompat exception enabled
  // get real navigator.keyboard.getLayoutMap key
  AllowFingerprinting();
  EnableWebcompatException();
  EXPECT_TRUE(ui_test_utils::NavigateToURL(browser(), test_url()));
  EXPECT_EQ(true, EvalJs(contents(), kGetLayoutMapScript));
}
