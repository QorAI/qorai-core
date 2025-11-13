// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/ai_chat/core/browser/ai_chat_metrics.h"
#include "qorai/components/ai_chat/core/browser/model_service.h"
#include "qorai/components/ai_chat/core/common/pref_names.h"
#include "qorai/components/qorai_account/prefs.h"
#include "qorai/components/qorai_ads/core/public/prefs/obsolete_pref_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_registry.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_registry.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_p3a.h"
#include "qorai/components/qorai_shields/core/common/pref_names.h"
#include "qorai/components/qorai_sync/qorai_sync_prefs.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_prefs.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/de_amp/common/pref_names.h"
#include "qorai/components/debounce/core/browser/debounce_service.h"
#include "qorai/components/decentralized_dns/core/utils.h"
#include "qorai/components/l10n/common/prefs.h"
#include "qorai/components/ntp_background_images/browser/ntp_background_images_service.h"
#include "qorai/components/ntp_background_images/common/view_counter_pref_registry.h"
#include "qorai/components/omnibox/browser/qorai_omnibox_prefs.h"
#include "qorai/components/p3a/metric_log_store.h"
#include "qorai/components/p3a/p3a_service.h"
#include "qorai/components/p3a/rotation_scheduler.h"
#include "qorai/components/playlist/core/common/pref_names.h"
#include "qorai/components/skus/browser/skus_utils.h"
#include "qorai/ios/browser/qorai_stats/qorai_stats_prefs.h"
#include "components/pref_registry/pref_registry_syncable.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/pref_names.h"
#endif

namespace qorai {

void RegisterBrowserStatePrefs(user_prefs::PrefRegistrySyncable* registry) {
  qorai_ads::RegisterProfilePrefs(registry);
  qorai_ads::RegisterProfilePrefsForMigration(registry);
  qorai_rewards::RegisterProfilePrefs(registry);
  qorai_rewards::RegisterProfilePrefsForMigration(registry);
  qorai_sync::Prefs::RegisterProfilePrefs(registry);
  qorai_wallet::RegisterProfilePrefs(registry);
  qorai_wallet::RegisterProfilePrefsForMigration(registry);
  de_amp::RegisterProfilePrefs(registry);
  debounce::DebounceService::RegisterProfilePrefs(registry);
  ai_chat::prefs::RegisterProfilePrefs(registry);
  ai_chat::ModelService::RegisterProfilePrefs(registry);
  qorai_account::prefs::RegisterPrefs(registry);
  omnibox::RegisterQoraiProfilePrefs(registry);
  qorai_news::prefs::RegisterProfilePrefs(registry);
  ntp_background_images::RegisterProfilePrefs(registry);
  ntp_background_images::RegisterProfilePrefsForMigration(registry);
  qorai_shields::RegisterShieldsP3AProfilePrefs(registry);
  qorai_shields::RegisterShieldsP3AProfilePrefsForMigration(registry);

  registry->RegisterBooleanPref(kQoraiTalkDisabledByPolicy, false);

  // This is typically registered by the PlaylistService but iOS does not
  // use that service
  registry->RegisterBooleanPref(playlist::kPlaylistEnabledPref, true);

#if BUILDFLAG(ENABLE_QORAI_VPN)
  registry->RegisterBooleanPref(qorai_vpn::prefs::kManagedQoraiVPNDisabled,
                                false);
#endif
}

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  qorai_ads::RegisterLocalStatePrefs(registry);
  qorai_stats::RegisterLocalStatePrefs(registry);
  qorai_wallet::RegisterLocalStatePrefs(registry);
  qorai_wallet::RegisterLocalStatePrefsForMigration(registry);
  decentralized_dns::RegisterLocalStatePrefs(registry);
  skus::RegisterLocalStatePrefs(registry);
  p3a::P3AService::RegisterPrefs(registry, false);
  p3a::MetricLogStore::RegisterLocalStatePrefsForMigration(registry);
  p3a::RotationScheduler::RegisterLocalStatePrefsForMigration(registry);
  ntp_background_images::NTPBackgroundImagesService::
      RegisterLocalStatePrefsForMigration(registry);
  qorai_l10n::RegisterLocalStatePrefsForMigration(registry);
  ai_chat::prefs::RegisterLocalStatePrefs(registry);
  ai_chat::AIChatMetrics::RegisterPrefs(registry);
  ntp_background_images::RegisterLocalStatePrefs(registry);
  qorai_shields::RegisterShieldsP3ALocalPrefs(registry);

  // qorai_shields
  // Note this can be removed when we use the entire
  // `qorai_shields:AdBlockService` And we can call its
  // `RegisterPrefsForAdBlockService`
  registry->RegisterDictionaryPref(
      qorai_shields::prefs::kAdBlockRegionalFilters);
  registry->RegisterDictionaryPref(
      qorai_shields::prefs::kAdBlockListSubscriptions);
  registry->RegisterBooleanPref(
      qorai_shields::prefs::kAdBlockCheckedAllDefaultRegions, false);
  registry->RegisterBooleanPref(
      qorai_shields::prefs::kAdBlockCheckedDefaultRegion, false);
}

void MigrateObsoleteProfilePrefs(PrefService* prefs) {
  qorai_ads::MigrateObsoleteProfilePrefs(prefs);
  qorai_wallet::MigrateObsoleteProfilePrefs(prefs);
  ntp_background_images::MigrateObsoleteProfilePrefs(prefs);
}

void MigrateObsoleteLocalStatePrefs(PrefService* prefs) {
  p3a::MetricLogStore::MigrateObsoleteLocalStatePrefs(prefs);
  p3a::RotationScheduler::MigrateObsoleteLocalStatePrefs(prefs);
  ntp_background_images::NTPBackgroundImagesService::
      MigrateObsoleteLocalStatePrefs(prefs);
}

}  // namespace qorai
