/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/qorai_rewards/rewards_web_ui_utils.h"

#include "qorai/browser/qorai_rewards/rewards_util.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "build/build_config.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/browser_context.h"
#include "url/gurl.h"

namespace qorai_rewards {

bool ShouldBlockRewardsWebUI(content::BrowserContext* browser_context,
                             const GURL& url) {
  if (url.host_piece() != kRewardsPageHost &&
#if !BUILDFLAG(IS_ANDROID)
      url.host_piece() != kRewardsPageTopHost &&
#endif  // !BUILDFLAG(IS_ANDROID)
      url.host_piece() != kRewardsInternalsHost) {
    return false;
  }

  Profile* profile = Profile::FromBrowserContext(browser_context);
  if (profile) {
    if (!qorai_rewards::IsSupportedForProfile(
            profile, url.host_piece() == kRewardsPageHost
                         ? qorai_rewards::IsSupportedOptions::kSkipRegionCheck
                         : qorai_rewards::IsSupportedOptions::kNone)) {
      return true;
    }
  }
  return false;
}

}  // namespace qorai_rewards
