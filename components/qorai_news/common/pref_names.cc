// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_news/common/pref_names.h"

#include "qorai/components/qorai_news/common/locales_helper.h"
#include "qorai/components/qorai_news/common/p3a_pref_names.h"
#include "qorai/components/p3a_utils/feature_usage.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace qorai_news {
namespace prefs {

void RegisterProfilePrefs(PrefRegistrySimple* registry) {
  registry->RegisterBooleanPref(kShouldShowToolbarButton, true);
  registry->RegisterBooleanPref(kNewTabPageShowToday,
                                IsUserInDefaultEnabledLocale());
  registry->RegisterBooleanPref(kQoraiNewsOptedIn, false);
  registry->RegisterDictionaryPref(kQoraiNewsSources);
  registry->RegisterDictionaryPref(kQoraiNewsChannels);
  registry->RegisterDictionaryPref(kQoraiNewsDirectFeeds);
  registry->RegisterBooleanPref(kQoraiNewsOpenArticlesInNewTab, true);
  registry->RegisterBooleanPref(kQoraiNewsDisabledByPolicy, false);

  qorai_news::p3a::prefs::RegisterProfileNewsMetricsPrefs(registry);
}

}  // namespace prefs

bool IsEnabled(PrefService* prefs) {
  if (prefs->GetBoolean(prefs::kQoraiNewsDisabledByPolicy)) {
    return false;
  }
  return prefs->GetBoolean(prefs::kNewTabPageShowToday) &&
         prefs->GetBoolean(prefs::kQoraiNewsOptedIn);
}

}  // namespace qorai_news
