/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/themes/qorai_dark_mode_utils.h"

namespace dark_mode {

void RegisterQoraiDarkModeLocalStatePrefs(PrefRegistrySimple* registry) {
}

bool SystemDarkModeEnabled() {
  return false;
}

void SetUseSystemDarkModeEnabledForTest(bool enabled) {
}

std::string GetStringFromQoraiDarkModeType(QoraiDarkModeType type) {
  return "Default";
}

void SetQoraiDarkModeType(const std::string& type) {
}

void SetQoraiDarkModeType(QoraiDarkModeType type) {
}

QoraiDarkModeType GetActiveQoraiDarkModeType() {
  return QoraiDarkModeType::QORAI_DARK_MODE_TYPE_DEFAULT;
}

QoraiDarkModeType GetQoraiDarkModeType() {
  return QoraiDarkModeType::QORAI_DARK_MODE_TYPE_DEFAULT;
}

base::Value::List GetQoraiDarkModeTypeList() {
  return base::Value::List();
}

void SetSystemDarkMode(QoraiDarkModeType type) {
}

}  // namespace dark_mode
