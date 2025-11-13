// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_news/common/p3a_pref_names.h"

#include "qorai/components/p3a_utils/feature_usage.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace qorai_news::p3a::prefs {

void RegisterProfileNewsMetricsPrefs(PrefRegistrySimple* registry) {
  registry->RegisterListPref(kQoraiNewsWeeklySessionCount);
  registry->RegisterListPref(kQoraiNewsWeeklyDisplayAdViewedCount);
  registry->RegisterListPref(kQoraiNewsWeeklyAddedDirectFeedsCount);
  registry->RegisterListPref(kQoraiNewsTotalCardViews);
  registry->RegisterListPref(kQoraiNewsTotalCardVisits);
  registry->RegisterListPref(kQoraiNewsVisitDepthSum);
  registry->RegisterListPref(kQoraiNewsTotalSidebarFilterUsages);
  p3a_utils::RegisterFeatureUsagePrefs(
      registry, prefs::kQoraiNewsFirstSessionTime,
      prefs::kQoraiNewsLastSessionTime, prefs::kQoraiNewsUsedSecondDay, nullptr,
      nullptr);
  registry->RegisterBooleanPref(kQoraiNewsWasEverEnabled, false);
}

void RegisterProfileNewsMetricsPrefsForMigration(PrefRegistrySimple* registry) {
  // Reserved for future deprecated P3A-related prefs
}

void MigrateObsoleteProfileNewsMetricsPrefs(PrefService* prefs) {
  // Reserved for future deprecated P3A-related prefs
}

}  // namespace qorai_news::p3a::prefs
