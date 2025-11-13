/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_THEMES_QORAI_THEME_SERVICE_H_
#define QORAI_BROWSER_THEMES_QORAI_THEME_SERVICE_H_

#include "chrome/browser/themes/theme_service.h"
#include "components/prefs/pref_member.h"

class Profile;

class QoraiThemeService : public ThemeService {
 public:
  explicit QoraiThemeService(Profile* profile, const ThemeHelper& theme_helper);
  ~QoraiThemeService() override;

  // ThemeService:
  bool GetIsGrayscale() const override;

 private:
#if defined(TOOLKIT_VIEWS)
  // Called when the darker theme pref is changed to notify that theme has
  // changed.
  void OnDarkerThemePrefChanged();
#endif  // defined(TOOLKIT_VIEWS)

  BooleanPrefMember darker_theme_enabled_;
};

#endif  // QORAI_BROWSER_THEMES_QORAI_THEME_SERVICE_H_
