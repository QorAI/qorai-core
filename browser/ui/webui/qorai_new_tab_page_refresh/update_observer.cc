// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/update_observer.h"

#include <utility>

#include "qorai/browser/ntp_background/ntp_background_prefs.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/top_sites_facade.h"
#include "qorai/components/qorai_perf_predictor/common/pref_names.h"
#include "qorai/components/qorai_search_conversion/pref_names.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/ntp_background_images/common/pref_names.h"
#include "chrome/browser/ui/webui/new_tab_page/ntp_pref_names.h"
#include "chrome/common/pref_names.h"

namespace qorai_new_tab_page_refresh {

UpdateObserver::UpdateObserver(PrefService& pref_service,
                               TopSitesFacade* top_sites_facade) {
  pref_change_registrar_.Init(&pref_service);

  AddPrefListener(ntp_background_images::prefs::kNewTabPageShowBackgroundImage,
                  Source::kBackgrounds);
  AddPrefListener(ntp_background_images::prefs::
                      kNewTabPageShowSponsoredImagesBackgroundImage,
                  Source::kBackgrounds);
  AddPrefListener(NTPBackgroundPrefs::kPrefName, Source::kBackgrounds);
  AddPrefListener(NTPBackgroundPrefs::kCustomImageListPrefName,
                  Source::kBackgrounds);

  AddPrefListener(qorai_search_conversion::prefs::kShowNTPSearchBox,
                  Source::kSearch);
  AddPrefListener(prefs::kSearchSuggestEnabled, Source::kSearch);
  AddPrefListener(qorai_search_conversion::prefs::kDismissed, Source::kSearch);

  AddPrefListener(ntp_prefs::kNtpShortcutsVisible, Source::kTopSites);
  AddPrefListener(ntp_prefs::kNtpShortcutsType, Source::kTopSites);

  AddPrefListener(kNewTabPageShowClock, Source::kClock);
  AddPrefListener(kNewTabPageClockFormat, Source::kClock);

  AddPrefListener(kNewTabPageShowStats, Source::kShieldsStats);
  AddPrefListener(kAdsBlocked, Source::kShieldsStats);
  AddPrefListener(kTrackersBlocked, Source::kShieldsStats);
  AddPrefListener(qorai_perf_predictor::prefs::kBandwidthSavedBytes,
                  Source::kShieldsStats);

  AddPrefListener(kNewTabPageShowQoraiTalk, Source::kTalk);

  AddPrefListener(kNewTabPageShowRewards, Source::kRewards);

#if BUILDFLAG(ENABLE_QORAI_VPN)
  AddPrefListener(kNewTabPageShowQoraiVPN, Source::kVPN);
#endif

  if (top_sites_facade) {
    top_sites_facade->SetSitesUpdatedCallback(
        base::BindRepeating(&UpdateObserver::OnUpdate,
                            weak_factory_.GetWeakPtr(), Source::kTopSites));
  }
}

UpdateObserver::~UpdateObserver() = default;

void UpdateObserver::SetCallback(
    base::RepeatingCallback<void(Source)> callback) {
  callback_ = std::move(callback);
}

void UpdateObserver::OnUpdate(Source update_source) {
  if (callback_) {
    callback_.Run(update_source);
  }
}

void UpdateObserver::OnPrefChanged(Source update_kind,
                                   const std::string& path) {
  OnUpdate(update_kind);
}

void UpdateObserver::AddPrefListener(const std::string& path,
                                     Source update_source) {
  pref_change_registrar_.Add(
      path, base::BindRepeating(&UpdateObserver::OnPrefChanged,
                                weak_factory_.GetWeakPtr(), update_source));
}

}  // namespace qorai_new_tab_page_refresh
