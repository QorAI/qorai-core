/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/qorai_pages.h"

#include <string_view>

#include "base/strings/strcat.h"
#include "qorai/browser/ui/webui/webcompat_reporter/webcompat_reporter_dialog.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/sidebar/browser/constants.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_navigator_params.h"
#include "chrome/browser/ui/chrome_pages.h"
#include "chrome/browser/ui/singleton_tabs.h"
#include "chrome/common/webui_url_constants.h"
#include "url/gurl.h"

namespace qorai {

void ShowQoraiRewards(Browser* browser) {
  ShowSingletonTabOverwritingNTP(browser, GURL(kRewardsPageURL));
}

void ShowQoraiAdblock(Browser* browser) {
  ShowSingletonTabOverwritingNTP(browser, GURL(kQoraiUIAdblockURL));
}

void ShowSync(Browser* browser) {
  ShowSingletonTabOverwritingNTP(
      browser, chrome::GetSettingsUrl(chrome::kSyncSetupSubPage));
}

void ShowQoraiNewsConfigure(Browser* browser) {
  ShowSingletonTabOverwritingNTP(
      browser, GURL("qorai://newtab/?openSettings=QoraiNews"));
}

void ShowShortcutsPage(Browser* browser) {
  ShowSingletonTabOverwritingNTP(browser, GURL(kShortcutsURL));
}

void ShowQoraiTalk(Browser* browser) {
  ShowSingletonTabOverwritingNTP(browser, GURL(sidebar::kQoraiTalkURL));
}

void ShowFullpageChat(Browser* browser) {
  if (!ai_chat::features::IsAIChatHistoryEnabled()) {
    return;
  }
  ShowSingletonTabOverwritingNTP(browser, GURL(kAIChatUIURL));
}

void ShowWebcompatReporter(Browser* browser) {
  content::WebContents* web_contents =
      browser->tab_strip_model()->GetActiveWebContents();
  if (!web_contents) {
    return;
  }

  webcompat_reporter::OpenReporterDialog(
      web_contents, webcompat_reporter::UISource::kAppMenu);
}

void ShowQoraiWallet(Browser* browser) {
  ShowSingletonTabOverwritingNTP(browser, GURL(kQoraiUIWalletURL));
}

void ShowQoraiWalletOnboarding(Browser* browser) {
  ShowSingletonTabOverwritingNTP(browser, GURL(kQoraiUIWalletOnboardingURL));
}

void ShowQoraiWalletAccountCreation(Browser* browser,
                                    std::string_view coin_name) {
  ShowSingletonTabOverwritingNTP(
      browser,
      GURL(base::StrCat({kQoraiUIWalletAccountCreationURL, coin_name})));
}

void ShowExtensionSettings(Browser* browser) {
  ShowSingletonTabOverwritingNTP(browser, GURL(kExtensionSettingsURL));
}

void ShowWalletSettings(Browser* browser) {
  ShowSingletonTabOverwritingNTP(browser, GURL(kWalletSettingsURL));
}

void ShowAppsPage(Browser* browser) {
  ShowSingletonTabOverwritingNTP(browser, GURL(chrome::kChromeUIAppsURL));
}

}  // namespace qorai
