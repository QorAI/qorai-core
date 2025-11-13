// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/navigation_bar_data_provider.h"

#include "qorai/browser/qorai_rewards/rewards_util.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_context_utils.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/grit/generated_resources.h"
#include "components/grit/qorai_components_strings.h"
#include "components/strings/grit/components_strings.h"
#include "content/public/browser/web_ui_data_source.h"

// static
void NavigationBarDataProvider::Initialize(content::WebUIDataSource* source,
                                           Profile* profile) {
  source->AddLocalizedString("brToolbarSettingsTitle", IDS_SETTINGS_SETTINGS);
  source->AddLocalizedString("brToolbarBookmarksTitle",
                             IDS_BOOKMARK_MANAGER_TITLE);
  source->AddLocalizedString("brToolbarDownloadsTitle", IDS_DOWNLOADS_TITLE);
  source->AddLocalizedString("brToolbarHistoryTitle", IDS_HISTORY_TITLE);
  source->AddLocalizedString("brToolbarRewardsTitle",
                             IDS_QORAI_UI_QORAI_REWARDS_TOOLBAR);
  source->AddLocalizedString("brToolbarWalletsTitle", IDS_WALLETS_TITLE);

  source->AddBoolean(
      "brToolbarShowRewardsButton",
      qorai_rewards::IsSupportedForProfile(
          profile, qorai_rewards::IsSupportedOptions::kSkipRegionCheck));
  source->AddBoolean("isQoraiWalletAllowed",
                     qorai_wallet::IsAllowedForContext(profile));
}
