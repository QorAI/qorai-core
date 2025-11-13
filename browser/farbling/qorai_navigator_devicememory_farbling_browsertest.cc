/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "base/path_service.h"
#include "base/test/thread_test_helper.h"
#include "qorai/browser/extensions/qorai_base_local_data_files_browsertest.h"
#include "qorai/components/qorai_component_updater/browser/local_data_files_service.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/constants/qorai_paths.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/webcompat/core/common/features.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/extensions/extension_browsertest.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/network_session_configurator/common/network_switches.h"
#include "components/permissions/permission_request.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "net/dns/mock_host_resolver.h"
#include "third_party/blink/public/common/device_memory/approximated_device_memory.h"

using qorai_shields::ControlType;

constexpr char kDeviceMemoryScript[] = "navigator.deviceMemory * 1024";

class QoraiDeviceMemoryFarblingBrowserTest : public InProcessBrowserTest {
 public:
  QoraiDeviceMemoryFarblingBrowserTest()
      : https_server_(net::EmbeddedTestServer::TYPE_HTTPS) {
    scoped_feature_list_.InitWithFeatures(
        {
            qorai_shields::features::kQoraiShowStrictFingerprintingMode,
            webcompat::features::kQoraiWebcompatExceptionsService,
        },
        {});
  }

  QoraiDeviceMemoryFarblingBrowserTest(
      const QoraiDeviceMemoryFarblingBrowserTest&) = delete;
  QoraiDeviceMemoryFarblingBrowserTest& operator=(
      const QoraiDeviceMemoryFarblingBrowserTest&) = delete;

  ~QoraiDeviceMemoryFarblingBrowserTest() override = default;

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    base::FilePath test_data_dir;
    base::PathService::Get(qorai::DIR_TEST_DATA, &test_data_dir);
    https_server_.SetSSLConfig(net::EmbeddedTestServer::CERT_TEST_NAMES);
    https_server_.ServeFilesFromDirectory(test_data_dir);
    EXPECT_TRUE(https_server_.Start());
    host_resolver()->AddRule("*", "127.0.0.1");
  }

 protected:
  base::test::ScopedFeatureList feature_list_;
  net::EmbeddedTestServer https_server_;

  HostContentSettingsMap* content_settings() {
    return HostContentSettingsMapFactory::GetForProfile(browser()->profile());
  }

  void AllowFingerprinting(std::string domain) {
    qorai_shields::SetFingerprintingControlType(
        content_settings(), ControlType::ALLOW,
        https_server_.GetURL(domain, "/"));
  }

  void BlockFingerprinting(std::string domain) {
    qorai_shields::SetFingerprintingControlType(
        content_settings(), ControlType::BLOCK,
        https_server_.GetURL(domain, "/"));
  }

  void SetFingerprintingDefault(std::string domain) {
    qorai_shields::SetFingerprintingControlType(
        content_settings(), ControlType::DEFAULT,
        https_server_.GetURL(domain, "/"));
  }

  content::WebContents* contents() {
    return browser()->tab_strip_model()->GetActiveWebContents();
  }

 private:
  base::test::ScopedFeatureList scoped_feature_list_;
};

// Tests results of farbling known values
IN_PROC_BROWSER_TEST_F(QoraiDeviceMemoryFarblingBrowserTest,
                       FarbleDeviceMemory) {
  std::string domain1 = "b.test";
  std::string domain2 = "d.test";
  GURL url1 = https_server_.GetURL(domain1, "/simple.html");
  GURL url2 = https_server_.GetURL(domain2, "/simple.html");
  // set memory to 10GB
  blink::ApproximatedDeviceMemory::SetPhysicalMemoryMBForTesting(1024 * 10);
  int true_value =
      blink::ApproximatedDeviceMemory::GetApproximatedDeviceMemory() * 1024;
  EXPECT_EQ(true_value, 8192);
  // Farbling level: off
  AllowFingerprinting(domain1);
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url1));
  EXPECT_EQ(true_value, EvalJs(contents(), kDeviceMemoryScript));
  AllowFingerprinting(domain2);
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url2));
  EXPECT_EQ(true_value, EvalJs(contents(), kDeviceMemoryScript));

  // Farbling level: default
  SetFingerprintingDefault(domain1);
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url1));
  EXPECT_EQ(4096, EvalJs(contents(), kDeviceMemoryScript));
  SetFingerprintingDefault(domain2);
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url2));
  EXPECT_EQ(512, EvalJs(contents(), kDeviceMemoryScript));

  // Farbling level: maximum
  BlockFingerprinting(domain1);
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url1));
  EXPECT_EQ(512, EvalJs(contents(), kDeviceMemoryScript));
  AllowFingerprinting(domain2);
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url2));
  EXPECT_EQ(8192, EvalJs(contents(), kDeviceMemoryScript));

  // Farbling level: default, but webcompat exception enabled
  SetFingerprintingDefault(domain1);
  qorai_shields::SetWebcompatEnabled(
      content_settings(), ContentSettingsType::QORAI_WEBCOMPAT_DEVICE_MEMORY,
      true, url1, nullptr);
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url1));
  EXPECT_EQ(true_value, EvalJs(contents(), kDeviceMemoryScript));
  SetFingerprintingDefault(domain2);
  qorai_shields::SetWebcompatEnabled(
      content_settings(), ContentSettingsType::QORAI_WEBCOMPAT_DEVICE_MEMORY,
      true, url2, nullptr);
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url2));
  EXPECT_EQ(true_value, EvalJs(contents(), kDeviceMemoryScript));
}
