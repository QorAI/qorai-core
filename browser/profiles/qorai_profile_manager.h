/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_PROFILES_QORAI_PROFILE_MANAGER_H_
#define QORAI_BROWSER_PROFILES_QORAI_PROFILE_MANAGER_H_

#include "chrome/browser/profiles/profile_manager.h"

class QoraiProfileManager : public ProfileManager {
 public:
  explicit QoraiProfileManager(const base::FilePath& user_data_dir);
  QoraiProfileManager(const QoraiProfileManager&) = delete;
  QoraiProfileManager& operator=(const QoraiProfileManager&) = delete;

  size_t GetNumberOfProfiles() override;
  void InitProfileUserPrefs(Profile* profile) override;
  void SetNonPersonalProfilePrefs(Profile* profile) override;
  bool IsAllowedProfilePath(const base::FilePath& path) const override;
  bool LoadProfileByPath(const base::FilePath& profile_path,
                         bool incognito,
                         ProfileLoadedCallback callback) override;
  void SetProfileAsLastUsed(Profile* last_active) override;

 protected:
  void DoFinalInitForServices(Profile* profile,
                              bool go_off_the_record) override;

};

class QoraiProfileManagerWithoutInit : public QoraiProfileManager {
 public:
  QoraiProfileManagerWithoutInit(const QoraiProfileManagerWithoutInit&) =
      delete;
  QoraiProfileManagerWithoutInit& operator=(
      const QoraiProfileManagerWithoutInit&) = delete;
  explicit QoraiProfileManagerWithoutInit(const base::FilePath& user_data_dir);
};

#endif  // QORAI_BROWSER_PROFILES_QORAI_PROFILE_MANAGER_H_
