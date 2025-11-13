/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_PAGES_H_
#define QORAI_BROWSER_UI_QORAI_PAGES_H_

#include <string_view>

class Browser;

namespace qorai {

void ShowQoraiAdblock(Browser* browser);
void ShowWebcompatReporter(Browser* browser);
void ShowQoraiRewards(Browser* browser);
void ShowQoraiWallet(Browser* browser);
void ShowQoraiWalletOnboarding(Browser* browser);
void ShowQoraiWalletAccountCreation(Browser* browser,
                                    std::string_view coin_name);
void ShowExtensionSettings(Browser* browser);
void ShowWalletSettings(Browser* browser);
void ShowSync(Browser* browser);
void ShowQoraiNewsConfigure(Browser* browser);
void ShowShortcutsPage(Browser* browser);
void ShowQoraiTalk(Browser* browser);
void ShowFullpageChat(Browser* browser);

void ShowAppsPage(Browser* browser);

}  // namespace qorai

#endif  // QORAI_BROWSER_UI_QORAI_PAGES_H_
