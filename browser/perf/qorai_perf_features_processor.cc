// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/perf/qorai_perf_features_processor.h"

#include "base/command_line.h"
#include "base/task/sequenced_task_runner.h"
#include "qorai/browser/qorai_browser_process.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/browser/perf/qorai_perf_switches.h"
#include "qorai/components/ai_chat/core/common/pref_names.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/content/rewards_service.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_service.h"
#include "qorai/components/qorai_shields/core/browser/ad_block_component_service_manager.h"
#include "qorai/components/qorai_shields/core/common/qorai_shield_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/chrome_switches.h"
#include "components/prefs/pref_service.h"

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/components/speedreader/speedreader_pref_names.h"
#endif

namespace {
void FakeCallback(qorai_rewards::mojom::CreateRewardsWalletResult) {}

void EnableAdblockCookieList(base::WeakPtr<Profile> profile) {
  if (!profile) {
    return;
  }

  // Obtrusive cookie notices list in cosmetic filters.
  auto* component_service_manager =
      g_qorai_browser_process->ad_block_service()->component_service_manager();
  if (!component_service_manager ||
      !component_service_manager->IsFilterListAvailable(
          qorai_shields::kCookieListUuid)) {
    base::SequencedTaskRunner::GetCurrentDefault()->PostDelayedTask(
        FROM_HERE, base::BindOnce(&EnableAdblockCookieList, profile),
        base::Seconds(1));
    return;
  }

  component_service_manager->EnableFilterList(qorai_shields::kCookieListUuid,
                                              true);
}

}  // namespace

namespace perf {

void MaybeEnableQoraiFeaturesPrefsForPerfTesting(Profile* profile) {
  auto* cmd = base::CommandLine::ForCurrentProcess();
  if (!cmd->HasSwitch(switches::kEnableQoraiFeaturesForPerfTesting) ||
      !cmd->HasSwitch(::switches::kUserDataDir)) {
    return;
  }

  // Notification Ads
  profile->GetPrefs()->SetBoolean(qorai_ads::prefs::kOptedInToNotificationAds,
                                  true);

  // Qorai news
  profile->GetPrefs()->SetBoolean(qorai_news::prefs::kNewTabPageShowToday,
                                  true);
  profile->GetPrefs()->SetBoolean(qorai_news::prefs::kQoraiNewsOptedIn, true);

#if BUILDFLAG(ENABLE_SPEEDREADER)
  // Speedreader - enable both the feature toggle and all-sites setting
  profile->GetPrefs()->SetBoolean(speedreader::kSpeedreaderEnabled, true);
  profile->GetPrefs()->SetBoolean(
      speedreader::kSpeedreaderAllowedForAllReadableSites, true);
#endif

  profile->GetPrefs()->SetTime(ai_chat::prefs::kLastAcceptedDisclaimer,
                               base::Time::Now());
  profile->GetPrefs()->SetBoolean(
      ai_chat::prefs::kQoraiChatAutocompleteProviderEnabled, true);
}

void MaybeEnableQoraiFeaturesServicesAndComponentsForPerfTesting(
    Profile* profile) {
  auto* cmd = base::CommandLine::ForCurrentProcess();
  if (!cmd->HasSwitch(switches::kEnableQoraiFeaturesForPerfTesting) ||
      !cmd->HasSwitch(::switches::kUserDataDir)) {
    return;
  }

  // Rewards
  auto* rewards_service =
      qorai_rewards::RewardsServiceFactory::GetForProfile(profile);
  rewards_service->CreateRewardsWallet("US", base::BindOnce(&FakeCallback));

  // Adblock
  EnableAdblockCookieList(profile->GetWeakPtr());
}

}  // namespace perf
