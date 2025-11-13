/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_THEMES_QORAI_DARK_MODE_UTILS_H_
#define QORAI_BROWSER_THEMES_QORAI_DARK_MODE_UTILS_H_

#include <string>

#include "base/values.h"
#include "build/build_config.h"

class PrefRegistrySimple;

namespace dark_mode {

enum class QoraiDarkModeType {
  // DEFAULT type acts as two ways depends on system theme mode.
  // If system dark mode is not supported, we override it with channel based
  // policy. In this case, user can see dark or light option in settings.
  // Otherwise, it acts like system dark mode mode. It respects system's dark
  // mode. In this case, user can see all three options in theme settings.
  QORAI_DARK_MODE_TYPE_DEFAULT,
  QORAI_DARK_MODE_TYPE_DARK,
  QORAI_DARK_MODE_TYPE_LIGHT,
};

// APIs for prefs.
void RegisterQoraiDarkModeLocalStatePrefs(PrefRegistrySimple* registry);

std::string GetStringFromQoraiDarkModeType(QoraiDarkModeType type);
base::Value::List GetQoraiDarkModeTypeList();
void SetQoraiDarkModeType(const std::string& type);
void SetQoraiDarkModeType(QoraiDarkModeType type);
// Returns current effective theme type. dark or light.
QoraiDarkModeType GetActiveQoraiDarkModeType();
// Returns current theme type.
// dark/light will be returned if platform doesn't support system dark mode.
// Otherwise, returns default/dark/light.
QoraiDarkModeType GetQoraiDarkModeType();
bool SystemDarkModeEnabled();
void SetUseSystemDarkModeEnabledForTest(bool enabled);

// When system supports system per-application system theme changing, set it.
// Currently, only MacOS support it.
// Otherewise, we need to overrides from native theme level and explicitly
// notifying to let observers know.
// By overriding, base ui components also use same qorai theme type.
void SetSystemDarkMode(QoraiDarkModeType type);

#if BUILDFLAG(IS_LINUX)
// Cache system preference from DarkModeManagerLinux.
// This cached value is used whenever user chooses "Same as Linux" option.
void CacheSystemDarkModePrefs(bool prefer_dark_theme);
bool HasCachedSystemDarkModeType();
#endif

}  // namespace dark_mode

#endif  // QORAI_BROWSER_THEMES_QORAI_DARK_MODE_UTILS_H_
