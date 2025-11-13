/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"

#include <utility>

#include "base/test/scoped_feature_list.h"
#include "base/test/values_test_util.h"
#include "qorai/components/qorai_vpn/common/features.h"
#include "qorai/components/qorai_vpn/common/pref_names.h"
#include "qorai/components/skus/browser/skus_utils.h"
#include "qorai/components/skus/common/features.h"
#include "components/prefs/pref_service.h"
#include "components/prefs/testing_pref_service.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

TEST(QoraiVPNUtilsUnitTest, MigrateAndMerge) {
  sync_preferences::TestingPrefServiceSyncable profile_pref_service;
  qorai_vpn::RegisterProfilePrefs(profile_pref_service.registry());
  TestingPrefServiceSimple local_state_pref_service;
  qorai_vpn::RegisterLocalStatePrefs(local_state_pref_service.registry());
  EXPECT_FALSE(local_state_pref_service.HasPrefPath(
      qorai_vpn::prefs::kQoraiVPNLocalStateMigrated));
  auto vpn_settings = base::test::ParseJsonDict(R"(
        {
            "device_region_name": "eu-de",
            "env": "development",
            "region_list":
            [
                {
                    "continent": "oceania",
                    "country-iso-code": "AU",
                    "name": "au-au",
                    "name-pretty": "Australia"
                }
            ]
        })");
  profile_pref_service.SetDict(qorai_vpn::prefs::kQoraiVPNRootPref,
                               vpn_settings.Clone());
  auto p3a_settings = base::test::ParseJsonDict(R"(
          {
            "days_in_month_used":
            [
                {
                    "day": 1663448400.0,
                    "value": 1.0
                }
            ],
            "first_use_time": "13307922000000000",
            "last_use_time": "13307922000000000"
          })");
  local_state_pref_service.SetDict(qorai_vpn::prefs::kQoraiVPNRootPref,
                                   p3a_settings.Clone());
  qorai_vpn::MigrateVPNSettings(&profile_pref_service,
                                &local_state_pref_service);

  EXPECT_FALSE(
      profile_pref_service.HasPrefPath(qorai_vpn::prefs::kQoraiVPNRootPref));
  EXPECT_TRUE(local_state_pref_service.HasPrefPath(
      qorai_vpn::prefs::kQoraiVPNRootPref));
  base::Value::Dict result = std::move(vpn_settings);
  result.Merge(std::move(p3a_settings));
  EXPECT_EQ(
      local_state_pref_service.GetDict(qorai_vpn::prefs::kQoraiVPNRootPref),
      result);
  EXPECT_TRUE(local_state_pref_service.HasPrefPath(
      qorai_vpn::prefs::kQoraiVPNLocalStateMigrated));
}

TEST(QoraiVPNUtilsUnitTest, Migrate) {
  sync_preferences::TestingPrefServiceSyncable profile_pref_service;
  qorai_vpn::RegisterProfilePrefs(profile_pref_service.registry());
  TestingPrefServiceSimple local_state_pref_service;
  qorai_vpn::RegisterLocalStatePrefs(local_state_pref_service.registry());
  EXPECT_FALSE(local_state_pref_service.HasPrefPath(
      qorai_vpn::prefs::kQoraiVPNLocalStateMigrated));

  auto vpn_settings = base::test::ParseJsonDict(R"(
        {
            "show_button": true,
            "device_region_name": "eu-de",
            "env": "development",
            "region_list":
            [
                {
                    "continent": "oceania",
                    "country-iso-code": "AU",
                    "name": "au-au",
                    "name-pretty": "Australia"
                }
            ]
        })");
  profile_pref_service.SetDict(qorai_vpn::prefs::kQoraiVPNRootPref,
                               vpn_settings.Clone());
  qorai_vpn::MigrateVPNSettings(&profile_pref_service,
                                &local_state_pref_service);
  EXPECT_TRUE(local_state_pref_service.HasPrefPath(
      qorai_vpn::prefs::kQoraiVPNRootPref));
  vpn_settings.Remove("show_button");
  EXPECT_EQ(
      local_state_pref_service.GetDict(qorai_vpn::prefs::kQoraiVPNRootPref),
      vpn_settings);
  EXPECT_TRUE(local_state_pref_service.HasPrefPath(
      qorai_vpn::prefs::kQoraiVPNLocalStateMigrated));
}

TEST(QoraiVPNUtilsUnitTest, NoMigration) {
  sync_preferences::TestingPrefServiceSyncable profile_pref_service;
  qorai_vpn::RegisterProfilePrefs(profile_pref_service.registry());
  TestingPrefServiceSimple local_state_pref_service;
  qorai_vpn::RegisterLocalStatePrefs(local_state_pref_service.registry());
  EXPECT_FALSE(
      profile_pref_service.HasPrefPath(qorai_vpn::prefs::kQoraiVPNRootPref));

  auto p3a_settings = base::test::ParseJsonDict(R"(
          {
            "days_in_month_used":
            [
                {
                    "day": 1663448400.0,
                    "value": 1.0
                }
            ],
            "first_use_time": "13307922000000000",
            "last_use_time": "13307922000000000"
          })");
  local_state_pref_service.SetDict(qorai_vpn::prefs::kQoraiVPNRootPref,
                                   p3a_settings.Clone());
  qorai_vpn::MigrateVPNSettings(&profile_pref_service,
                                &local_state_pref_service);

  EXPECT_FALSE(
      profile_pref_service.HasPrefPath(qorai_vpn::prefs::kQoraiVPNRootPref));
  EXPECT_TRUE(local_state_pref_service.HasPrefPath(
      qorai_vpn::prefs::kQoraiVPNRootPref));
  EXPECT_EQ(
      local_state_pref_service.GetDict(qorai_vpn::prefs::kQoraiVPNRootPref),
      p3a_settings);
  EXPECT_TRUE(local_state_pref_service.HasPrefPath(
      qorai_vpn::prefs::kQoraiVPNLocalStateMigrated));
}

TEST(QoraiVPNUtilsUnitTest, AlreadyMigrated) {
  sync_preferences::TestingPrefServiceSyncable profile_pref_service;
  qorai_vpn::RegisterProfilePrefs(profile_pref_service.registry());
  TestingPrefServiceSimple local_state_pref_service;
  qorai_vpn::RegisterLocalStatePrefs(local_state_pref_service.registry());
  local_state_pref_service.SetBoolean(
      qorai_vpn::prefs::kQoraiVPNLocalStateMigrated, true);

  auto vpn_settings = base::test::ParseJsonDict(R"(
        {
            "show_button": true,
            "device_region_name": "eu-de",
            "env": "development",
            "region_list":
            [
                {
                    "continent": "oceania",
                    "country-iso-code": "AU",
                    "name": "au-au",
                    "name-pretty": "Australia"
                }
            ]
        })");
  profile_pref_service.SetDict(qorai_vpn::prefs::kQoraiVPNRootPref,
                               std::move(vpn_settings));
  auto p3a_settings = base::test::ParseJsonDict(R"(
          {
            "days_in_month_used":
            [
                {
                    "day": 1663448400.0,
                    "value": 1.0
                }
            ],
            "first_use_time": "13307922000000000",
            "last_use_time": "13307922000000000"
          })");
  local_state_pref_service.SetDict(qorai_vpn::prefs::kQoraiVPNRootPref,
                                   p3a_settings.Clone());
  qorai_vpn::MigrateVPNSettings(&profile_pref_service,
                                &local_state_pref_service);
  EXPECT_TRUE(local_state_pref_service.HasPrefPath(
      qorai_vpn::prefs::kQoraiVPNRootPref));
  EXPECT_EQ(
      local_state_pref_service.GetDict(qorai_vpn::prefs::kQoraiVPNRootPref),
      p3a_settings);
  EXPECT_TRUE(local_state_pref_service.HasPrefPath(
      qorai_vpn::prefs::kQoraiVPNLocalStateMigrated));
}

#if !BUILDFLAG(IS_ANDROID)
TEST(QoraiVPNUtilsUnitTest, SelectedRegionNameMigration) {
  TestingPrefServiceSimple local_state_pref_service;
  qorai_vpn::RegisterLocalStatePrefs(local_state_pref_service.registry());
  EXPECT_EQ(1, local_state_pref_service.GetInteger(
                   qorai_vpn::prefs::kQoraiVPNRegionListVersion));

  local_state_pref_service.SetString(qorai_vpn::prefs::kQoraiVPNSelectedRegion,
                                     "au-au");
  qorai_vpn::MigrateLocalStatePrefs(&local_state_pref_service);
  EXPECT_EQ("ocn-aus", local_state_pref_service.GetString(
                           qorai_vpn::prefs::kQoraiVPNSelectedRegionV2));
  EXPECT_EQ(2, local_state_pref_service.GetInteger(
                   qorai_vpn::prefs::kQoraiVPNRegionListVersion));

  // Check v1's selected region is preserved.
  EXPECT_EQ("au-au", local_state_pref_service.GetString(
                         qorai_vpn::prefs::kQoraiVPNSelectedRegion));
}

TEST(QoraiVPNUtilsUnitTest, InvalidSelectedRegionNameMigration) {
  TestingPrefServiceSimple local_state_pref_service;
  qorai_vpn::RegisterLocalStatePrefs(local_state_pref_service.registry());
  EXPECT_EQ(1, local_state_pref_service.GetInteger(
                   qorai_vpn::prefs::kQoraiVPNRegionListVersion));

  local_state_pref_service.SetString(qorai_vpn::prefs::kQoraiVPNSelectedRegion,
                                     "invalid");
  qorai_vpn::MigrateLocalStatePrefs(&local_state_pref_service);
  EXPECT_EQ("", local_state_pref_service.GetString(
                    qorai_vpn::prefs::kQoraiVPNSelectedRegionV2));
  EXPECT_EQ(2, local_state_pref_service.GetInteger(
                   qorai_vpn::prefs::kQoraiVPNRegionListVersion));
}
#endif

TEST(QoraiVPNUtilsUnitTest, VPNPaymentsEnv) {
  EXPECT_EQ("production",
            qorai_vpn::GetQoraiVPNPaymentsEnv(skus::kEnvProduction));
  EXPECT_EQ("staging", qorai_vpn::GetQoraiVPNPaymentsEnv(skus::kEnvStaging));
  EXPECT_EQ("development",
            qorai_vpn::GetQoraiVPNPaymentsEnv(skus::kEnvDevelopment));
}

TEST(QoraiVPNUtilsUnitTest, IsQoraiVPNEnabled) {
  sync_preferences::TestingPrefServiceSyncable profile_pref_service;
  qorai_vpn::RegisterProfilePrefs(profile_pref_service.registry());
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitWithFeatures(
      {qorai_vpn::features::kQoraiVPN, skus::features::kSkusFeature}, {});

  EXPECT_TRUE(qorai_vpn::IsQoraiVPNFeatureEnabled());
  profile_pref_service.SetManagedPref(
      qorai_vpn::prefs::kManagedQoraiVPNDisabled, base::Value(false));
  EXPECT_TRUE(qorai_vpn::IsQoraiVPNEnabled(&profile_pref_service));
  profile_pref_service.SetManagedPref(
      qorai_vpn::prefs::kManagedQoraiVPNDisabled, base::Value(true));
  EXPECT_FALSE(qorai_vpn::IsQoraiVPNEnabled(&profile_pref_service));
}

TEST(QoraiVPNUtilsUnitTest, FeatureTest) {
#if !BUILDFLAG(IS_LINUX)
  EXPECT_TRUE(qorai_vpn::IsQoraiVPNFeatureEnabled());
#else
  EXPECT_FALSE(qorai_vpn::IsQoraiVPNFeatureEnabled());
#endif
}

TEST(QoraiVPNUtilsUnitTest, DefaultPrefsTest) {
  TestingPrefServiceSimple local_state_pref_service;
  qorai_vpn::RegisterLocalStatePrefs(local_state_pref_service.registry());

#if BUILDFLAG(IS_MAC)
  // Off by default.
  EXPECT_FALSE(local_state_pref_service.GetBoolean(
      qorai_vpn::prefs::kQoraiVPNOnDemandEnabled));
#endif

  EXPECT_TRUE(local_state_pref_service.GetBoolean(
      qorai_vpn::prefs::kQoraiVPNSmartProxyRoutingEnabled));
}

#if BUILDFLAG(IS_MAC)
TEST(QoraiVPNUtilsUnitTest, IsQoraiVPNWireguardEnabledMac) {
  {
    TestingPrefServiceSimple local_state_pref_service;
    qorai_vpn::RegisterLocalStatePrefs(local_state_pref_service.registry());

    // Prefs are in default state, the wireguard feature is disabled.
    base::test::ScopedFeatureList scoped_feature_list;
    scoped_feature_list.InitWithFeatures(
        {qorai_vpn::features::kQoraiVPN, skus::features::kSkusFeature}, {});
    EXPECT_FALSE(local_state_pref_service.GetBoolean(
        qorai_vpn::prefs::kQoraiVPNWireguardEnabled));
    EXPECT_FALSE(
        qorai_vpn::IsQoraiVPNWireguardEnabled(&local_state_pref_service));

    // The pref is enabled but the feature is disabled
    local_state_pref_service.SetBoolean(
        qorai_vpn::prefs::kQoraiVPNWireguardEnabled, true);
    EXPECT_FALSE(
        qorai_vpn::IsQoraiVPNWireguardEnabled(&local_state_pref_service));
  }

  {
    TestingPrefServiceSimple local_state_pref_service;
    qorai_vpn::RegisterLocalStatePrefs(local_state_pref_service.registry());

    // // Prefs are in default state, the wireguard feature is enabled.
    base::test::ScopedFeatureList scoped_feature_list;
    scoped_feature_list.InitWithFeatures(
        {qorai_vpn::features::kQoraiVPN, skus::features::kSkusFeature,
         qorai_vpn::features::kQoraiVPNEnableWireguardForOSX},
        {});

    EXPECT_FALSE(local_state_pref_service.GetBoolean(
        qorai_vpn::prefs::kQoraiVPNWireguardEnabled));
    EXPECT_FALSE(
        qorai_vpn::IsQoraiVPNWireguardEnabled(&local_state_pref_service));

    // The pref is enabled but the feature is enabled.
    local_state_pref_service.SetBoolean(
        qorai_vpn::prefs::kQoraiVPNWireguardEnabled, true);
    EXPECT_TRUE(
        qorai_vpn::IsQoraiVPNWireguardEnabled(&local_state_pref_service));
  }
}
#endif
