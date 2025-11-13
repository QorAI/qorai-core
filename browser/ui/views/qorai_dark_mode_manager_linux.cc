/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/qorai_dark_mode_manager_linux.h"

#include "qorai/browser/themes/qorai_dark_mode_utils.h"
#include "ui/linux/linux_ui_factory.h"

namespace ui {

QoraiDarkModeManagerLinux::QoraiDarkModeManagerLinux()
    : DarkModeManagerLinux() {
  // In base class' ctor, |prefer_dark_theme_| is set by calling
  // SetColorScheme() when ui::GetDefaultLinuxUiTheme()
  if (ui::GetDefaultLinuxUiTheme()) {
    dark_mode::CacheSystemDarkModePrefs(prefer_dark_theme_);
  }
}

QoraiDarkModeManagerLinux::~QoraiDarkModeManagerLinux() = default;

void QoraiDarkModeManagerLinux::SetColorScheme(bool prefer_dark_theme,
                                               bool from_toolkit_theme) {
  dark_mode::CacheSystemDarkModePrefs(prefer_dark_theme);
  if (dark_mode::GetQoraiDarkModeType() ==
      dark_mode::QoraiDarkModeType::QORAI_DARK_MODE_TYPE_DEFAULT) {
    DarkModeManagerLinux::SetColorScheme(prefer_dark_theme, from_toolkit_theme);
  } else {
    // Make |prefer_dark_theme_| stores latest system theme even qorai theme(
    // dark or light) is set. If not, system theme change could not be applied
    // properly later.
    prefer_dark_theme_ = prefer_dark_theme;
  }
}

}  // namespace ui
