/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SIDEBAR_BROWSER_SIDEBAR_P3A_H_
#define QORAI_COMPONENTS_SIDEBAR_BROWSER_SIDEBAR_P3A_H_

#include "components/prefs/pref_change_registrar.h"

class PrefService;

namespace sidebar {
namespace p3a {

inline constexpr char kSidebarEnabledHistogramName[] = "Qorai.Sidebar.Enabled";
inline constexpr char kSettingChangeSidebarEnabledAHistogramName[] = "Qorai.Sidebar.SettingChange.SidebarEnabledA";
inline constexpr char kSettingChangeSidebarEnabledBHistogramName[] = "Qorai.Sidebar.SettingChange.SidebarEnabledB";

class SidebarP3A {
 public:
  explicit SidebarP3A(PrefService* profile_prefs);
  ~SidebarP3A();

  SidebarP3A(const SidebarP3A&) = delete;
  SidebarP3A& operator=(const SidebarP3A&) = delete;

  void RecordEnabledSetting(bool setting_changed);

 private:
  raw_ptr<PrefService> profile_prefs_;
  PrefChangeRegistrar profile_pref_change_registrar_;
};

}  // namespace p3a
}  // namespace sidebar

#endif  // QORAI_COMPONENTS_SIDEBAR_BROWSER_SIDEBAR_P3A_H_
