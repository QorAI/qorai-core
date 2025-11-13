/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/tabs/qorai_tab_prefs.h"

#include "qorai/browser/ui/tabs/features.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace qorai_tabs {

void RegisterQoraiProfilePrefs(PrefRegistrySimple* registry) {
  registry->RegisterIntegerPref(kTabHoverMode, TabHoverMode::CARD);
  registry->RegisterBooleanPref(kVerticalTabsEnabled, false);
  registry->RegisterBooleanPref(kVerticalTabsCollapsed, false);
  registry->RegisterBooleanPref(kVerticalTabsExpandedStatePerWindow, false);
#if BUILDFLAG(IS_WIN)
  // On Windows, we show window title by default
  // https://github.com/qorai/qorai-browser/issues/30027
  registry->RegisterBooleanPref(kVerticalTabsShowTitleOnWindow, true);
#else
  registry->RegisterBooleanPref(kVerticalTabsShowTitleOnWindow, false);
#endif

  if (base::FeatureList::IsEnabled(
          tabs::features::kQoraiVerticalTabHideCompletely)) {
    registry->RegisterBooleanPref(kVerticalTabsHideCompletelyWhenCollapsed,
                                  false);
  }

  registry->RegisterBooleanPref(kVerticalTabsFloatingEnabled, true);
  registry->RegisterIntegerPref(kVerticalTabsExpandedWidth, 220);
  registry->RegisterBooleanPref(kVerticalTabsOnRight, false);
  registry->RegisterBooleanPref(kVerticalTabsShowScrollbar, false);

  registry->RegisterBooleanPref(kSharedPinnedTab, false);

  if (base::FeatureList::IsEnabled(tabs::features::kQoraiTreeTab)) {
    registry->RegisterBooleanPref(kTreeTabsEnabled, false);
  }
}

void MigrateQoraiProfilePrefs(PrefService* prefs) {
  if (auto* pref = prefs->FindPreference(kVerticalTabsShowScrollbar);
      pref && pref->IsDefaultValue() &&
      base::FeatureList::IsEnabled(
          tabs::features::kQoraiVerticalTabScrollBar)) {
    prefs->SetBoolean(kVerticalTabsShowScrollbar, true);
  }
}

bool AreTooltipsEnabled(PrefService* prefs) {
  return prefs->GetInteger(kTabHoverMode) == TabHoverMode::TOOLTIP;
}

bool AreCardPreviewsEnabled(PrefService* prefs) {
  return prefs->GetInteger(kTabHoverMode) == TabHoverMode::CARD_WITH_PREVIEW;
}

}  // namespace qorai_tabs
