/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/prefs/obsolete_pref_util.h"

#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace qorai_ads {

namespace {

constexpr char kObsoleteShouldShowSearchResultAdClickedInfoBar[] =
    "qorai.qorai_ads.should_show_search_result_ad_clicked_infobar";

constexpr const char* kObsoleteP2APrefPaths[] = {
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.architecture)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.artsentertainment)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.automotive)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.business)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.careers)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.cellphones)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.crypto)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.education)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.familyparenting)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.fashion)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.folklore)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.fooddrink)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.gaming)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.healthfitness)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.history)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.hobbiesinterests)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.home)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.law)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.military)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.other)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.personalfinance)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.pets)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.realestate)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.science)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.sports)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.technologycomputing)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.travel)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.untargeted)",
    R"(qorai.weekly_storage.Qorai.P2A.ad_notification.opportunities_per_segment.weather)",
    R"(qorai.weekly_storage.Qorai.P2A.inline_content_ad.opportunities)",
    R"(qorai.weekly_storage.Qorai.P2A.new_tab_page_ad.opportunities)"};

constexpr std::string_view kNewTabPageEventCountDictPref =
    "qorai.qorai_ads.p3a.ntp_event_count";
constexpr std::string_view kNewTabPageEventCountConstellationDictPref =
    "qorai.qorai_ads.p3a.ntp_event_count_constellation";
constexpr std::string_view kNewTabPageKnownCampaignsDictPref =
    "qorai.qorai_ads.p3a.ntp_known_campaigns";

void MaybeMigrateShouldShowSearchResultAdClickedInfoBarProfilePref(
    PrefService* const prefs) {
  if (!prefs->HasPrefPath(kObsoleteShouldShowSearchResultAdClickedInfoBar)) {
    return;
  }

  prefs->SetBoolean(
      prefs::kShouldShowSearchResultAdClickedInfoBar,
      prefs->GetBoolean(kObsoleteShouldShowSearchResultAdClickedInfoBar));
  prefs->ClearPref(kObsoleteShouldShowSearchResultAdClickedInfoBar);
}

}  // namespace

void RegisterProfilePrefsForMigration(PrefRegistrySimple* const registry) {
  // Added 05/2025.
  registry->RegisterBooleanPref(kObsoleteShouldShowSearchResultAdClickedInfoBar,
                                false);

  // Added 06/2025.
  for (const auto* path : kObsoleteP2APrefPaths) {
    registry->RegisterListPref(path);
  }
}

void MigrateObsoleteProfilePrefs(PrefService* const prefs) {
  // Added 05/2025.
  MaybeMigrateShouldShowSearchResultAdClickedInfoBarProfilePref(prefs);

  // Added 06/2025.
  for (const auto* path : kObsoleteP2APrefPaths) {
    prefs->ClearPref(path);
  }
}

void RegisterLocalStatePrefsForMigration(PrefRegistrySimple* registry) {
  // Added 06/2025
  registry->RegisterDictionaryPref(kNewTabPageEventCountDictPref);

  // Added 10/2025
  registry->RegisterDictionaryPref(kNewTabPageEventCountConstellationDictPref);
  registry->RegisterDictionaryPref(kNewTabPageKnownCampaignsDictPref);
}

void MigrateObsoleteLocalStatePrefs(PrefService* local_state) {
  // Added 06/2025
  local_state->ClearPref(kNewTabPageEventCountDictPref);

  // Added 10/2025
  local_state->ClearPref(kNewTabPageEventCountConstellationDictPref);
  local_state->ClearPref(kNewTabPageKnownCampaignsDictPref);
}

}  // namespace qorai_ads
