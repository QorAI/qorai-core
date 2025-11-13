/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/profiles/profile_util.h"

#include "qorai/components/qorai_shields/core/browser/qorai_shields_p3a.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/search_engines/qorai_prepopulated_engines.h"
#include "chrome/browser/profiles/profile.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/common/pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/search_engines/search_engines_pref_names.h"

namespace qorai {

void SetDefaultSearchVersion(Profile* profile, bool is_new_profile) {
  const PrefService::Preference* pref_default_search_version =
      profile->GetPrefs()->FindPreference(prefs::kQoraiDefaultSearchVersion);
  if (!pref_default_search_version->HasUserSetting()) {
    profile->GetPrefs()->SetInteger(
        prefs::kQoraiDefaultSearchVersion,
        is_new_profile
            ? TemplateURLPrepopulateData::kQoraiCurrentDataVersion
            : TemplateURLPrepopulateData::kQoraiFirstTrackedDataVersion);
  }
}

void SetDefaultThirdPartyCookieBlockValue(Profile* profile) {
  profile->GetPrefs()->SetDefaultPrefValue(
      prefs::kCookieControlsMode,
      base::Value(static_cast<int>(
          content_settings::CookieControlsMode::kBlockThirdParty)));
}

}  // namespace qorai
