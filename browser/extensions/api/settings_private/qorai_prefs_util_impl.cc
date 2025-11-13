/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/extensions/api/settings_private/qorai_prefs_util.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "chrome/browser/content_settings/cookie_settings_factory.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/extensions/api/settings_private.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/common/pref_names.h"
#include "content/public/browser/browser_context.h"
#include "url/gurl.h"

namespace extensions {

std::optional<api::settings_private::PrefObject> QoraiPrefsUtil::GetPref(
    const std::string& name) {
  auto pref = PrefsUtil::GetPref(name);
  // Simulate "Enforced" mode for kCookieControlsMode pref when Cookies are
  // fully blocked via Shields. This will effectively disable the "Third-party
  // cookies" mode selector on Settings page.
  if (pref && name == prefs::kCookieControlsMode &&
      pref->enforcement == api::settings_private::Enforcement::kNone &&
      qorai_shields::GetCookieControlType(
          HostContentSettingsMapFactory::GetForProfile(profile()),
          CookieSettingsFactory::GetForProfile(profile()).get(),
          GURL()) == qorai_shields::ControlType::BLOCK) {
    pref->enforcement = api::settings_private::Enforcement::kEnforced;
  }
  return pref;
}

}  // namespace extensions
