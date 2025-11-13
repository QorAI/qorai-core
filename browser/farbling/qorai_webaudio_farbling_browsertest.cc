/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "base/path_service.h"
#include "base/test/scoped_feature_list.h"
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
#include "components/prefs/pref_service.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "net/dns/mock_host_resolver.h"

using qorai_shields::ControlType;

constexpr char kEmbeddedTestServerDirectory[] = "webaudio";
constexpr char kTitleScript[] = "document.title;";
constexpr char kWebAudioResultScript[] =
    "(async () => await window.webAudioAnalysisPromise)()";

class QoraiWebAudioFarblingBrowserTest : public InProcessBrowserTest {
 public:
  QoraiWebAudioFarblingBrowserTest() {
    scoped_feature_list_.InitWithFeatures(
        /*enabled_features=*/
        {webcompat::features::kQoraiWebcompatExceptionsService,
         qorai_shields::features::kQoraiShowStrictFingerprintingMode},
        /*disabled_features=*/{});
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();

    host_resolver()->AddRule("*", "127.0.0.1");
    content::SetupCrossSiteRedirector(embedded_test_server());

    base::FilePath test_data_dir;
    base::PathService::Get(qorai::DIR_TEST_DATA, &test_data_dir);
    test_data_dir = test_data_dir.AppendASCII(kEmbeddedTestServerDirectory);
    embedded_test_server()->ServeFilesFromDirectory(test_data_dir);

    ASSERT_TRUE(embedded_test_server()->Start());

    top_level_page_url_ = embedded_test_server()->GetURL("a.com", "/");
    farbling_url_ = embedded_test_server()->GetURL("a.com", "/farbling.html");
    farbling2_url_ = embedded_test_server()->GetURL("a.com", "/farbling2.html");
    copy_from_channel_url_ =
        embedded_test_server()->GetURL("a.com", "/copyFromChannel.html");
  }

  const GURL& copy_from_channel_url() { return copy_from_channel_url_; }

  const GURL& farbling_url() { return farbling_url_; }

  const GURL& farbling2_url() { return farbling2_url_; }

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

 private:
  GURL top_level_page_url_;
  GURL copy_from_channel_url_;
  GURL farbling_url_;
  GURL farbling2_url_;
  base::test::ScopedFeatureList scoped_feature_list_;
};

// Tests for crash in copyFromChannel as reported in
// https://github.com/qorai/qorai-browser/issues/9552
// No crash indicates a successful test.
IN_PROC_BROWSER_TEST_F(QoraiWebAudioFarblingBrowserTest,
                       CopyFromChannelNoCrash) {
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), copy_from_channel_url()));
}

// Tests results of farbling known values
IN_PROC_BROWSER_TEST_F(QoraiWebAudioFarblingBrowserTest, FarbleWebAudio) {
  // Farbling level: maximum
  // web audio: pseudo-random data with no relation to underlying audio channel
  BlockFingerprinting();
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), farbling_url()));
  EXPECT_EQ(content::EvalJs(contents(), kTitleScript), "356");
  // second time, same as the first (tests that the PRNG properly resets itself
  // at the beginning of each calculation)
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), farbling_url()));
  EXPECT_EQ(content::EvalJs(contents(), kTitleScript), "356");

  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), farbling2_url()));
  EXPECT_EQ(content::EvalJs(contents(), kWebAudioResultScript), -971);

  // Farbling level: balanced (default)
  // web audio: farbled audio data
  SetFingerprintingDefault();
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), farbling_url()));
  EXPECT_EQ(content::EvalJs(contents(), kTitleScript), "7920");

  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), farbling2_url()));
  EXPECT_EQ(content::EvalJs(contents(), kWebAudioResultScript), -1032);

  // Farbling level: off
  // web audio: original audio data
  AllowFingerprinting();
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), farbling_url()));
  EXPECT_EQ(content::EvalJs(contents(), kTitleScript), "8000");

  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), farbling2_url()));
  EXPECT_EQ(content::EvalJs(contents(), kWebAudioResultScript), -1031);

  // Farbling level: balanced (default), but webcompat exception enabled
  // web audio: original audio data
  SetFingerprintingDefault();
  qorai_shields::SetWebcompatEnabled(content_settings(),
                                     ContentSettingsType::QORAI_WEBCOMPAT_AUDIO,
                                     true, farbling_url(), nullptr);
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), farbling_url()));
  EXPECT_EQ(content::EvalJs(contents(), kTitleScript), "8000");

  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), farbling2_url()));
  EXPECT_EQ(content::EvalJs(contents(), kWebAudioResultScript), -1031);
}
