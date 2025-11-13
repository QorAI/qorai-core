/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_origin/qorai_origin_policy_manager.h"

#include "base/memory/raw_ptr.h"
#include "base/strings/strcat.h"
#include "base/test/task_environment.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_info.h"
#include "qorai/components/qorai_origin/qorai_origin_utils.h"
#include "qorai/components/qorai_origin/pref_names.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/testing_pref_service.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai_origin {

// Test constants
constexpr char kTestGlobalPref[] = "test.global.pref";
constexpr char kTestProfilePref[] = "test.profile.pref";
// Policy keys (generated from pref names)
constexpr char kTestGlobalPolicyKey[] = "Testtest.global.prefPolicy";
constexpr char kTestProfilePolicyKey[] = "Testtest.profile.prefPolicy";
constexpr char kUnknownPolicyKey[] = "Testunknown.prefPolicy";
// Aliases for compatibility with existing tests
constexpr char kBrowserPolicyKey[] = "Testtest.global.prefPolicy";
constexpr char kProfilePolicyKey[] = "Testtest.profile.prefPolicy";

class QorAIOriginPolicyManagerTest : public testing::Test {
 public:
  QorAIOriginPolicyManagerTest() = default;
  ~QorAIOriginPolicyManagerTest() override = default;

  void SetUp() override {
    pref_service_.registry()->RegisterDictionaryPref(kQorAIOriginPolicies);
  }

  void TearDown() override {
    auto* manager = QorAIOriginPolicyManager::GetInstance();
    manager->Shutdown();
  }

 protected:
  void CreateTestPolicy(QorAIOriginPolicyMap& policies,
                        const std::string& pref_name,
                        bool default_value) {
    std::string policy_key = base::StrCat({"Test", pref_name, "Policy"});
    policies.emplace(
        policy_key,
        QorAIOriginPolicyInfo(pref_name, default_value, true,
                              GetQorAIOriginPrefKey(policy_key, std::nullopt)));
  }

  QorAIOriginPolicyMap CreateBrowserTestPolicies() {
    QorAIOriginPolicyMap test_policies;
    CreateTestPolicy(test_policies, kTestGlobalPref, false);
    return test_policies;
  }

  QorAIOriginPolicyMap CreateProfileTestPolicies() {
    QorAIOriginPolicyMap test_policies;
    CreateTestPolicy(test_policies, kTestProfilePref, true);
    return test_policies;
  }

  void InitializeManager() {
    auto* manager = QorAIOriginPolicyManager::GetInstance();
    manager->Init(CreateBrowserTestPolicies(), CreateProfileTestPolicies(),
                  &pref_service_);
  }

  void SetPolicyInLocalState(const std::string& key, bool value) {
    base::Value::Dict policies_dict =
        pref_service_.GetDict(kQorAIOriginPolicies).Clone();
    policies_dict.Set(key, value);
    pref_service_.SetDict(kQorAIOriginPolicies, std::move(policies_dict));
  }

  base::test::TaskEnvironment task_environment_;
  TestingPrefServiceSimple pref_service_;
};

class TestObserver : public qorai_policy::QorAIPolicyObserver {
 public:
  void OnQorAIPoliciesReady() override { ready_called_ = true; }

  void OnBrowserPolicyChanged(std::string_view pref_name) override {
    browser_policy_changed_called_ = true;
    last_browser_pref_ = pref_name;
  }

  void OnProfilePolicyChanged(std::string_view pref_name,
                              std::string_view profile_id) override {
    profile_policy_changed_called_ = true;
    last_profile_pref_ = pref_name;
    last_profile_id_ = profile_id;
  }

  bool ready_called() const { return ready_called_; }
  bool browser_policy_changed_called() const {
    return browser_policy_changed_called_;
  }
  bool profile_policy_changed_called() const {
    return profile_policy_changed_called_;
  }
  const std::string& last_browser_pref() const { return last_browser_pref_; }
  const std::string& last_profile_pref() const { return last_profile_pref_; }
  const std::string& last_profile_id() const { return last_profile_id_; }

 private:
  bool ready_called_ = false;
  bool browser_policy_changed_called_ = false;
  bool profile_policy_changed_called_ = false;
  std::string last_browser_pref_;
  std::string last_profile_pref_;
  std::string last_profile_id_;
};

TEST_F(QorAIOriginPolicyManagerTest, GetInstance_ReturnsSingleton) {
  auto* instance1 = QorAIOriginPolicyManager::GetInstance();
  auto* instance2 = QorAIOriginPolicyManager::GetInstance();

  EXPECT_EQ(instance1, instance2);
  EXPECT_NE(instance1, nullptr);
}

TEST_F(QorAIOriginPolicyManagerTest, IsInitialized_InitiallyFalse) {
  auto* manager = QorAIOriginPolicyManager::GetInstance();
  EXPECT_FALSE(manager->IsInitialized());
}

TEST_F(QorAIOriginPolicyManagerTest, Init_SetsInitializedState) {
  auto* manager = QorAIOriginPolicyManager::GetInstance();
  manager->Init(CreateBrowserTestPolicies(), CreateProfileTestPolicies(),
                &pref_service_);

  EXPECT_TRUE(manager->IsInitialized());
}

TEST_F(QorAIOriginPolicyManagerTest, Init_NotifiesObservers) {
  TestObserver observer;
  auto* manager = QorAIOriginPolicyManager::GetInstance();

  manager->AddObserver(&observer);
  EXPECT_FALSE(observer.ready_called());

  manager->Init(CreateBrowserTestPolicies(), CreateProfileTestPolicies(),
                &pref_service_);
  EXPECT_TRUE(observer.ready_called());

  manager->RemoveObserver(&observer);
}

TEST_F(QorAIOriginPolicyManagerTest,
       AddObserver_NotifiesImmediatelyIfInitialized) {
  InitializeManager();

  TestObserver observer;
  auto* manager = QorAIOriginPolicyManager::GetInstance();
  manager->AddObserver(&observer);

  // Should be called immediately since manager is already initialized
  EXPECT_TRUE(observer.ready_called());

  manager->RemoveObserver(&observer);
}

TEST_F(QorAIOriginPolicyManagerTest,
       GetPolicyValue_ReturnsDefaultForUnknownPref) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();
  auto result = manager->GetPolicyValue(kUnknownPolicyKey);
  EXPECT_FALSE(result.has_value());
}

TEST_F(QorAIOriginPolicyManagerTest, GetPolicyValue_ReturnsDefaultValue) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();
  // Test global pref default
  auto result = manager->GetPolicyValue(kTestGlobalPolicyKey);
  ASSERT_TRUE(result.has_value());
  EXPECT_FALSE(result.value());

  // Test profile pref default
  result = manager->GetPolicyValue(kTestProfilePolicyKey, "profile123");
  ASSERT_TRUE(result.has_value());
  EXPECT_TRUE(result.value());
}

TEST_F(QorAIOriginPolicyManagerTest, GetPolicyValue_ReturnsLocalStateValue) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();
  // Set policy value in local state
  const auto* policy_info = manager->GetPolicyInfo(kTestGlobalPolicyKey);
  ASSERT_NE(policy_info, nullptr);
  std::string policy_key =
      GetQorAIOriginPrefKey(kTestGlobalPolicyKey, std::nullopt);
  SetPolicyInLocalState(policy_key, true);

  auto result = manager->GetPolicyValue(kTestGlobalPolicyKey);
  ASSERT_TRUE(result.has_value());
  EXPECT_TRUE(result.value());  // Should return local state value, not default
}

TEST_F(QorAIOriginPolicyManagerTest, GetPolicyValue_ProfileScopedPolicy) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();
  const std::string profile_id = "profile123";
  const auto* policy_info = manager->GetPolicyInfo(kTestProfilePolicyKey);
  ASSERT_NE(policy_info, nullptr);
  std::string policy_key =
      GetQorAIOriginPrefKey(kTestProfilePolicyKey, profile_id);
  SetPolicyInLocalState(policy_key, false);

  auto result = manager->GetPolicyValue(kTestProfilePolicyKey, profile_id);
  ASSERT_TRUE(result.has_value());
  EXPECT_FALSE(result.value());  // Should return local state value, not default
}

TEST_F(QorAIOriginPolicyManagerTest, GetPolicyValue_RequiresInitialization) {
  auto* manager = QorAIOriginPolicyManager::GetInstance();
  // Should crash/check fail when not initialized
  EXPECT_DEATH_IF_SUPPORTED(manager->GetPolicyValue(kTestGlobalPolicyKey), "");
}

TEST_F(QorAIOriginPolicyManagerTest,
       GetAllBrowserPolicies_ReturnsOnlyBrowserPolicies) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();
  const auto browser_policies = manager->GetAllBrowserPolicies();
  EXPECT_EQ(browser_policies.size(), 1u);
  EXPECT_TRUE(browser_policies.contains(kBrowserPolicyKey));
  EXPECT_FALSE(browser_policies.contains(kProfilePolicyKey));
  // Test that we get the actual policy value (default false)
  EXPECT_FALSE(browser_policies.at(kBrowserPolicyKey));
}

TEST_F(QorAIOriginPolicyManagerTest,
       GetAllProfilePolicies_ReturnsOnlyProfilePolicies) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();
  const auto profile_policies = manager->GetAllProfilePolicies("test_profile");
  EXPECT_EQ(profile_policies.size(), 1u);
  EXPECT_TRUE(profile_policies.contains(kProfilePolicyKey));
  EXPECT_FALSE(profile_policies.contains(kBrowserPolicyKey));
  // Test that we get the actual policy value (default true)
  EXPECT_TRUE(profile_policies.at(kProfilePolicyKey));
}

TEST_F(QorAIOriginPolicyManagerTest,
       GetAllBrowserPolicies_RequiresInitialization) {
  auto* manager = QorAIOriginPolicyManager::GetInstance();
  // Should crash/check fail when not initialized
  EXPECT_DEATH_IF_SUPPORTED(manager->GetAllBrowserPolicies(), "");
}

TEST_F(QorAIOriginPolicyManagerTest,
       GetAllProfilePolicies_RequiresInitialization) {
  auto* manager = QorAIOriginPolicyManager::GetInstance();
  // Should crash/check fail when not initialized
  EXPECT_DEATH_IF_SUPPORTED(manager->GetAllProfilePolicies("test"), "");
}

TEST_F(QorAIOriginPolicyManagerTest, GetPolicyInfo_ReturnsValidInfo) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();
  const auto* info = manager->GetPolicyInfo(kTestGlobalPolicyKey);
  ASSERT_NE(info, nullptr);
  EXPECT_FALSE(info->default_value);
  EXPECT_EQ(info->pref_name, kTestGlobalPref);
}

TEST_F(QorAIOriginPolicyManagerTest, GetPolicyInfo_ReturnsNullForUnknown) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();
  const auto* info = manager->GetPolicyInfo(kUnknownPolicyKey);
  EXPECT_EQ(info, nullptr);
}

TEST_F(QorAIOriginPolicyManagerTest, MultipleObservers_AllNotified) {
  TestObserver observer1, observer2, observer3;
  auto* manager = QorAIOriginPolicyManager::GetInstance();

  manager->AddObserver(&observer1);
  manager->AddObserver(&observer2);
  manager->AddObserver(&observer3);

  manager->Init(CreateBrowserTestPolicies(), CreateProfileTestPolicies(),
                &pref_service_);

  EXPECT_TRUE(observer1.ready_called());
  EXPECT_TRUE(observer2.ready_called());
  EXPECT_TRUE(observer3.ready_called());

  manager->RemoveObserver(&observer1);
  manager->RemoveObserver(&observer2);
  manager->RemoveObserver(&observer3);
}

TEST_F(QorAIOriginPolicyManagerTest, RemoveObserver_StopsNotifications) {
  TestObserver observer;
  auto* manager = QorAIOriginPolicyManager::GetInstance();

  manager->AddObserver(&observer);
  manager->RemoveObserver(&observer);

  manager->Init(CreateBrowserTestPolicies(), CreateProfileTestPolicies(),
                &pref_service_);

  // Should not be notified since observer was removed
  EXPECT_FALSE(observer.ready_called());
}

TEST_F(QorAIOriginPolicyManagerTest, SetPolicyValue_UpdatesValue) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();

  // Initially should return default value (false)
  auto result = manager->GetPolicyValue(kTestGlobalPolicyKey);
  ASSERT_TRUE(result.has_value());
  EXPECT_FALSE(result.value());

  // Set the value to true
  manager->SetPolicyValue(kTestGlobalPolicyKey, true);

  // Should now return the updated value
  result = manager->GetPolicyValue(kTestGlobalPolicyKey);
  ASSERT_TRUE(result.has_value());
  EXPECT_TRUE(result.value());

  // Set the value back to false
  manager->SetPolicyValue(kTestGlobalPolicyKey, false);

  // Should return the updated value
  result = manager->GetPolicyValue(kTestGlobalPolicyKey);
  ASSERT_TRUE(result.has_value());
  EXPECT_FALSE(result.value());
}

TEST_F(QorAIOriginPolicyManagerTest, SetPolicyValue_ProfilePref_UpdatesValue) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();
  const std::string profile_id = "test-profile";

  // Initially should return default value (true)
  auto result = manager->GetPolicyValue(kTestProfilePolicyKey, profile_id);
  ASSERT_TRUE(result.has_value());
  EXPECT_TRUE(result.value());

  // Set the value to false
  manager->SetPolicyValue(kTestProfilePolicyKey, false, profile_id);

  // Should now return the updated value
  result = manager->GetPolicyValue(kTestProfilePolicyKey, profile_id);
  ASSERT_TRUE(result.has_value());
  EXPECT_FALSE(result.value());

  // Set the value back to true
  manager->SetPolicyValue(kTestProfilePolicyKey, true, profile_id);

  // Should return the updated value
  result = manager->GetPolicyValue(kTestProfilePolicyKey, profile_id);
  ASSERT_TRUE(result.has_value());
  EXPECT_TRUE(result.value());
}

TEST_F(QorAIOriginPolicyManagerTest, SetPolicyValue_RequiresInitialization) {
  auto* manager = QorAIOriginPolicyManager::GetInstance();
  // Should crash/check fail when not initialized
  EXPECT_DEATH_IF_SUPPORTED(manager->SetPolicyValue(kTestGlobalPolicyKey, true),
                            "");
}

TEST_F(QorAIOriginPolicyManagerTest, SetPolicyValue_RejectsUnknownPref) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();

  // Setting unknown pref should not crash but should be ignored
  manager->SetPolicyValue(kUnknownPolicyKey, true);

  // Verify it's still unknown
  auto result = manager->GetPolicyValue(kUnknownPolicyKey);
  EXPECT_FALSE(result.has_value());
}

TEST_F(QorAIOriginPolicyManagerTest, SetValues_UpdatesGetAllPoliciesMethods) {
  InitializeManager();

  auto* manager = QorAIOriginPolicyManager::GetInstance();
  const std::string profile_id = "test-profile";

  // Set browser policy value
  manager->SetPolicyValue(kTestGlobalPolicyKey, true);

  // Set profile policy value
  manager->SetPolicyValue(kTestProfilePolicyKey, false, profile_id);

  // Verify GetAllBrowserPolicies reflects the change
  const auto browser_policies = manager->GetAllBrowserPolicies();
  EXPECT_EQ(browser_policies.size(), 1u);
  EXPECT_TRUE(browser_policies.contains(kBrowserPolicyKey));
  EXPECT_TRUE(browser_policies.at(kBrowserPolicyKey));

  // Verify GetAllProfilePolicies reflects the change
  const auto profile_policies = manager->GetAllProfilePolicies(profile_id);
  EXPECT_EQ(profile_policies.size(), 1u);
  EXPECT_TRUE(profile_policies.contains(kProfilePolicyKey));
  EXPECT_FALSE(profile_policies.at(kProfilePolicyKey));
}

TEST_F(QorAIOriginPolicyManagerTest,
       SetPolicyValue_BrowserPolicy_NotifiesObservers) {
  InitializeManager();

  TestObserver observer;
  auto* manager = QorAIOriginPolicyManager::GetInstance();
  manager->AddObserver(&observer);

  // Set a browser policy value
  manager->SetPolicyValue(kTestGlobalPolicyKey, true);

  // Verify browser policy observer was called
  EXPECT_TRUE(observer.browser_policy_changed_called());
  EXPECT_EQ(observer.last_browser_pref(), kTestGlobalPolicyKey);

  // Verify profile policy observer was not called
  EXPECT_FALSE(observer.profile_policy_changed_called());

  manager->RemoveObserver(&observer);
}

TEST_F(QorAIOriginPolicyManagerTest,
       SetPolicyValue_ProfilePolicy_NotifiesObservers) {
  InitializeManager();

  TestObserver observer;
  auto* manager = QorAIOriginPolicyManager::GetInstance();
  manager->AddObserver(&observer);

  const std::string profile_id = "test-profile";

  // Set a profile policy value
  manager->SetPolicyValue(kTestProfilePolicyKey, false, profile_id);

  // Verify profile policy observer was called
  EXPECT_TRUE(observer.profile_policy_changed_called());
  EXPECT_EQ(observer.last_profile_pref(), kTestProfilePolicyKey);
  EXPECT_EQ(observer.last_profile_id(), profile_id);

  // Verify browser policy observer was not called
  EXPECT_FALSE(observer.browser_policy_changed_called());

  manager->RemoveObserver(&observer);
}

TEST_F(QorAIOriginPolicyManagerTest,
       SetPolicyValue_MultipleObservers_AllNotified) {
  InitializeManager();

  TestObserver observer1, observer2, observer3;
  auto* manager = QorAIOriginPolicyManager::GetInstance();
  manager->AddObserver(&observer1);
  manager->AddObserver(&observer2);
  manager->AddObserver(&observer3);

  // Set a browser policy value
  manager->SetPolicyValue(kTestGlobalPolicyKey, true);

  // Verify all observers were called
  EXPECT_TRUE(observer1.browser_policy_changed_called());
  EXPECT_TRUE(observer2.browser_policy_changed_called());
  EXPECT_TRUE(observer3.browser_policy_changed_called());

  EXPECT_EQ(observer1.last_browser_pref(), kTestGlobalPolicyKey);
  EXPECT_EQ(observer2.last_browser_pref(), kTestGlobalPolicyKey);
  EXPECT_EQ(observer3.last_browser_pref(), kTestGlobalPolicyKey);

  manager->RemoveObserver(&observer1);
  manager->RemoveObserver(&observer2);
  manager->RemoveObserver(&observer3);
}

}  // namespace qorai_origin
