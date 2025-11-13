/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_WALLET_COMMON_UI_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_WALLET_COMMON_UI_H_

#include <stdint.h>

class Profile;
class Browser;

namespace content {
class WebContents;
}  // namespace content

namespace qorai_wallet {

void AddBlockchainTokenImageSource(Profile* profile);

content::WebContents* GetWebContentsFromTabId(Browser** browser,
                                              int32_t tab_id);
content::WebContents* GetActiveWebContents();

}  // namespace qorai_wallet

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_WALLET_COMMON_UI_H_
