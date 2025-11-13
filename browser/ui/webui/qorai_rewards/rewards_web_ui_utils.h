/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_REWARDS_REWARDS_WEB_UI_UTILS_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_REWARDS_REWARDS_WEB_UI_UTILS_H_

namespace content {
class BrowserContext;
}

class GURL;

namespace qorai_rewards {

bool ShouldBlockRewardsWebUI(content::BrowserContext* browser_context,
                             const GURL& url);

}  // namespace qorai_rewards

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_REWARDS_REWARDS_WEB_UI_UTILS_H_
