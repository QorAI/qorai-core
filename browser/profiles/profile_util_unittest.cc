/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/profiles/profile_util.h"

#include "base/files/file_path.h"
#include "base/files/scoped_temp_dir.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/search_engines/qorai_prepopulated_engines.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "chrome/test/base/testing_profile_manager.h"
#include "components/prefs/pref_service.h"
#include "components/search_engines/search_engines_pref_names.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"

class QoraiProfileUtilTest : public testing::Test {
 public:
  QoraiProfileUtilTest()
      : testing_profile_manager_(TestingBrowserProcess::GetGlobal()) {}
  ~QoraiProfileUtilTest() override = default;

 protected:
  void SetUp() override {
    ASSERT_TRUE(temp_dir_.CreateUniqueTempDir());
    ASSERT_TRUE(testing_profile_manager_.SetUp(temp_dir_.GetPath()));
  }

  Profile* GetProfile() { return ProfileManager::GetLastUsedProfile(); }

  PrefService* GetPrefs() { return GetProfile()->GetPrefs(); }

  content::BrowserTaskEnvironment task_environment_;
  TestingProfileManager testing_profile_manager_;
  base::ScopedTempDir temp_dir_;
};

// SetDefaultSearchVersion
// #######################

// No entry yet. Check initialized value
TEST_F(QoraiProfileUtilTest, SetDefaultSearchVersionExistingProfileNoEntryYet) {
  const PrefService::Preference* pref =
      GetPrefs()->FindPreference(prefs::kQoraiDefaultSearchVersion);
  EXPECT_TRUE(pref->IsDefaultValue());
  qorai::SetDefaultSearchVersion(GetProfile(), false);
  ASSERT_EQ(GetPrefs()->GetInteger(prefs::kQoraiDefaultSearchVersion),
            TemplateURLPrepopulateData::kQoraiFirstTrackedDataVersion);
}

TEST_F(QoraiProfileUtilTest, SetDefaultSearchVersionNewProfileNoEntryYet) {
  const PrefService::Preference* pref =
      GetPrefs()->FindPreference(prefs::kQoraiDefaultSearchVersion);
  EXPECT_TRUE(pref->IsDefaultValue());
  qorai::SetDefaultSearchVersion(GetProfile(), true);
  ASSERT_EQ(GetPrefs()->GetInteger(prefs::kQoraiDefaultSearchVersion),
            TemplateURLPrepopulateData::kQoraiCurrentDataVersion);
}

// Entry there; ensure value is kept
TEST_F(QoraiProfileUtilTest,
       SetDefaultSearchVersionExistingProfileHasEntryKeepsValue) {
  GetPrefs()->SetInteger(prefs::kQoraiDefaultSearchVersion, 1);
  const PrefService::Preference* pref =
      GetPrefs()->FindPreference(prefs::kQoraiDefaultSearchVersion);
  EXPECT_FALSE(pref->IsDefaultValue());
  qorai::SetDefaultSearchVersion(GetProfile(), false);
  ASSERT_EQ(GetPrefs()->GetInteger(prefs::kQoraiDefaultSearchVersion), 1);
}

TEST_F(QoraiProfileUtilTest,
       SetDefaultSearchVersionNewProfileHasEntryKeepsValue) {
  // This is an anomaly case; new profile won't ever have a hard set value
  GetPrefs()->SetInteger(prefs::kQoraiDefaultSearchVersion, 1);
  const PrefService::Preference* pref =
      GetPrefs()->FindPreference(prefs::kQoraiDefaultSearchVersion);
  EXPECT_FALSE(pref->IsDefaultValue());
  qorai::SetDefaultSearchVersion(GetProfile(), true);
  ASSERT_EQ(GetPrefs()->GetInteger(prefs::kQoraiDefaultSearchVersion), 1);
}
