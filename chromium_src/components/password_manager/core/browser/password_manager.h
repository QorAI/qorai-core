/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_H_

#define RegisterProfilePrefs                       \
  RegisterProfilePrefs_ChromiumImpl(               \
      user_prefs::PrefRegistrySyncable* registry); \
  static void RegisterProfilePrefs

#include <components/password_manager/core/browser/password_manager.h>  // IWYU pragma: export

#undef RegisterProfilePrefs

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_H_
