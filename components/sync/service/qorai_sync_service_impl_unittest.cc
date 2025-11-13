/* Copyright (c) 2020 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/sync/service/qorai_sync_service_impl.h"

#include <utility>

#include "base/base64.h"
#include "base/check.h"
#include "base/memory/raw_ptr.h"
#include "base/notreached.h"
#include "base/run_loop.h"
#include "base/test/gtest_util.h"
#include "base/test/metrics/histogram_tester.h"
#include "base/test/scoped_feature_list.h"
#include "base/test/task_environment.h"
#include "base/time/default_clock.h"
#include "base/time/default_tick_clock.h"
#include "qorai/components/qorai_sync/qorai_sync_p3a.h"
#include "qorai/components/qorai_sync/features.h"
#include "qorai/components/qorai_sync/network_time_helper.h"
#include "qorai/components/history/core/browser/sync/qorai_history_data_type_controller.h"
#include "qorai/components/history/core/browser/sync/qorai_history_delete_directives_data_type_controller.h"
#include "qorai/components/sync/service/sync_service_impl_delegate.h"
#include "qorai/components/sync/test/qorai_mock_sync_engine.h"
#include "build/build_config.h"
#include "components/network_time/network_time_tracker.h"
#include "components/os_crypt/sync/os_crypt.h"
#include "components/os_crypt/sync/os_crypt_mocker.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/signin/public/identity_manager/accounts_in_cookie_jar_info.h"
#include "components/sync/base/data_type.h"
#include "components/sync/engine/nigori/key_derivation_params.h"
#include "components/sync/engine/nigori/nigori.h"
#include "components/sync/model/type_entities_count.h"
#include "components/sync/service/data_type_manager_impl.h"
#include "components/sync/service/glue/sync_transport_data_prefs.h"
#include "components/sync/test/data_type_manager_mock.h"
#include "components/sync/test/fake_data_type_controller.h"
#include "components/sync/test/fake_sync_engine.h"
#include "components/sync/test/fake_sync_engine_factory.h"
#include "components/sync/test/fake_sync_manager.h"
#include "components/sync/test/sync_service_impl_bundle.h"
#include "components/sync/test/test_data_type_store_service.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "content/public/test/browser_task_environment.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"
#include "testing/gtest/include/gtest/gtest.h"

using testing::_;
using testing::ByMove;
using testing::NiceMock;
using testing::Return;

namespace syncer {

namespace {

constexpr char kCacheGuid[] = "cache_guid";

constexpr char kValidSyncCode[] =
    "fringe digital begin feed equal output proof cheap "
    "exotic ill sure question trial squirrel glove celery "
    "awkward push jelly logic broccoli almost grocery drift";

// Taken from anonymous namespace from sync_service_crypto_unittest.cc
sync_pb::EncryptedData MakeEncryptedData(
    const std::string& passphrase,
    const KeyDerivationParams& derivation_params) {
  std::unique_ptr<Nigori> nigori =
      Nigori::CreateByDerivation(derivation_params, passphrase);

  std::string nigori_name = nigori->GetKeyName();
  const std::string unencrypted = "test";
  sync_pb::EncryptedData encrypted;
  encrypted.set_key_name(nigori_name);
  *encrypted.mutable_blob() = nigori->Encrypt(unencrypted);
  return encrypted;
}

}  // namespace

class SyncServiceImplDelegateMock : public SyncServiceImplDelegate {
 public:
  SyncServiceImplDelegateMock() = default;
  ~SyncServiceImplDelegateMock() override = default;

  MOCK_METHOD0(SuspendDeviceObserverForOwnReset, void());
  MOCK_METHOD0(ResumeDeviceObserver, void());
  MOCK_METHOD1(SetLocalDeviceAppearedCallback,
               void(base::OnceCallback<void()>));
  MOCK_METHOD1(GetKnownToSyncHistoryCount,
               void(base::OnceCallback<void(std::pair<bool, int>)>));
};

class SyncServiceObserverMock : public SyncServiceObserver {
 public:
  SyncServiceObserverMock() {}
  ~SyncServiceObserverMock() override {}

  MOCK_METHOD(void, OnStateChanged, (SyncService * sync), (override));
  MOCK_METHOD(void, OnSyncCycleCompleted, (SyncService * sync), (override));
  MOCK_METHOD(void, OnSyncShutdown, (SyncService * sync), (override));
};

class QorAISyncServiceImplTest : public testing::Test {
 public:
  QorAISyncServiceImplTest()
      : qorai_sync_prefs_(sync_service_impl_bundle_.pref_service()),
        sync_prefs_(sync_service_impl_bundle_.pref_service()) {
    sync_service_impl_bundle_.identity_test_env()
        ->SetAutomaticIssueOfAccessTokens(true);
    qorai_sync::Prefs::RegisterProfilePrefs(
        sync_service_impl_bundle_.pref_service()->registry());
    network_time::NetworkTimeTracker::RegisterPrefs(local_state_.registry());
  }

  ~QorAISyncServiceImplTest() override { sync_service_impl_->Shutdown(); }

  void SetUp() override {
    testing::Test::SetUp();
    network_time_tracker_ = std::make_unique<network_time::NetworkTimeTracker>(
        std::unique_ptr<base::Clock>(new base::DefaultClock()),
        std::unique_ptr<base::TickClock>(new base::DefaultTickClock()),
        &local_state_, nullptr, std::nullopt);
    qorai_sync::NetworkTimeHelper::GetInstance()->SetNetworkTimeTracker(
        network_time_tracker_.get(),
        base::SingleThreadTaskRunner::GetCurrentDefault());
  }

  void TearDown() override {
    qorai_sync::NetworkTimeHelper::GetInstance()->Shutdown();
    testing::Test::TearDown();
  }

  void CreateSyncService(
      DataTypeSet registered_types = DataTypeSet({BOOKMARKS, PASSWORDS})) {
    DataTypeController::TypeVector controllers;
    for (DataType type : registered_types) {
      controllers.push_back(std::make_unique<FakeDataTypeController>(type));
    }

    std::unique_ptr<SyncClientMock> sync_client =
        sync_service_impl_bundle_.CreateSyncClientMock();

    auto sync_service_delegate(std::make_unique<SyncServiceImplDelegateMock>());
    sync_service_delegate_ = sync_service_delegate.get();

    sync_service_impl_ = std::make_unique<QorAISyncServiceImpl>(
        sync_service_impl_bundle_.CreateBasicInitParams(std::move(sync_client)),
        std::move(sync_service_delegate));
    sync_service_impl_->Initialize(std::move(controllers));
  }

  qorai_sync::Prefs* qorai_sync_prefs() { return &qorai_sync_prefs_; }

  SyncPrefs* sync_prefs() { return &sync_prefs_; }

  sync_preferences::TestingPrefServiceSyncable* pref_service() {
    return sync_service_impl_bundle_.pref_service();
  }

  QorAISyncServiceImpl* qorai_sync_service_impl() {
    return sync_service_impl_.get();
  }

  FakeSyncEngineFactory* engine_factory() {
    return sync_service_impl_bundle_.engine_factory();
  }

  FakeSyncEngine* engine() { return engine_factory()->last_created_engine(); }

  signin::IdentityManager* identity_manager() {
    return sync_service_impl_bundle_.identity_manager();
  }

  SyncServiceImplDelegateMock* sync_service_delegate() {
    return sync_service_delegate_;
  }

 protected:
  content::BrowserTaskEnvironment task_environment_;

 private:
  SyncServiceImplBundle sync_service_impl_bundle_;
  qorai_sync::Prefs qorai_sync_prefs_;
  SyncPrefs sync_prefs_;
  std::unique_ptr<network_time::NetworkTimeTracker> network_time_tracker_;
  std::unique_ptr<QorAISyncServiceImpl> sync_service_impl_;
  raw_ptr<SyncServiceImplDelegateMock> sync_service_delegate_;
  TestingPrefServiceSimple local_state_;
};

TEST_F(QorAISyncServiceImplTest, GroupPolicyOverride) {
  pref_service()->SetManagedPref(qorai_sync::kCustomSyncServiceUrl,
                                 base::Value("https://sync.example.com/v2"));

  OSCryptMocker::SetUp();

  CreateSyncService();

  EXPECT_FALSE(engine());

  GURL expected_service_url = GURL("https://sync.example.com/v2");
  GURL actual_service_url =
      qorai_sync_service_impl()->GetSyncServiceUrlForDebugging();
  EXPECT_EQ(expected_service_url, actual_service_url);

  OSCryptMocker::TearDown();

  pref_service()->SetManagedPref(qorai_sync::kCustomSyncServiceUrl,
                                 base::Value(""));
}

TEST_F(QorAISyncServiceImplTest, GroupPolicyNonHttpsOverride) {
  pref_service()->SetManagedPref(qorai_sync::kCustomSyncServiceUrl,
                                 base::Value("http://sync.example.com/v2"));

  OSCryptMocker::SetUp();

  CreateSyncService();

  EXPECT_FALSE(engine());

  GURL expected_service_url = GURL("http://sync.example.com/v2");
  GURL actual_service_url =
      qorai_sync_service_impl()->GetSyncServiceUrlForDebugging();
  EXPECT_NE(expected_service_url, actual_service_url);

  OSCryptMocker::TearDown();

  pref_service()->SetManagedPref(qorai_sync::kCustomSyncServiceUrl,
                                 base::Value(""));
}

TEST_F(QorAISyncServiceImplTest, ValidPassphrase) {
  OSCryptMocker::SetUp();

  CreateSyncService();

  EXPECT_FALSE(engine());

  bool set_code_result = qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);
  EXPECT_TRUE(set_code_result);

  bool failed_to_decrypt = false;
  EXPECT_EQ(qorai_sync_prefs()->GetSeed(&failed_to_decrypt), kValidSyncCode);
  EXPECT_FALSE(failed_to_decrypt);

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, InvalidPassphrase) {
  OSCryptMocker::SetUp();

  CreateSyncService();
  EXPECT_FALSE(engine());

  bool set_code_result =
      qorai_sync_service_impl()->SetSyncCode("word one and then two");
  EXPECT_FALSE(set_code_result);

  bool failed_to_decrypt = false;
  EXPECT_EQ(qorai_sync_prefs()->GetSeed(&failed_to_decrypt), "");
  EXPECT_FALSE(failed_to_decrypt);

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, ValidPassphraseLeadingTrailingWhitespace) {
  OSCryptMocker::SetUp();

  CreateSyncService();
  EXPECT_FALSE(engine());

  std::string sync_code_extra_whitespace =
      std::string(" \t\n") + kValidSyncCode + std::string(" \t\n");
  bool set_code_result =
      qorai_sync_service_impl()->SetSyncCode(sync_code_extra_whitespace);
  EXPECT_TRUE(set_code_result);

  bool failed_to_decrypt = false;
  EXPECT_EQ(qorai_sync_prefs()->GetSeed(&failed_to_decrypt), kValidSyncCode);
  EXPECT_FALSE(failed_to_decrypt);

  OSCryptMocker::TearDown();
}

// Google test doc strongly recommends to use `*DeathTest` naming
// for test suite
using QorAISyncServiceImplDeathTest = QorAISyncServiceImplTest;

// Some tests are failing for Windows x86 CI,
// See https://github.com/qorai/qorai-browser/issues/22767
#if BUILDFLAG(IS_WIN) && defined(ARCH_CPU_X86)
#define MAYBE_EmulateGetOrCreateSyncCodeCHECK \
  DISABLED_EmulateGetOrCreateSyncCodeCHECK
#else
#define MAYBE_EmulateGetOrCreateSyncCodeCHECK EmulateGetOrCreateSyncCodeCHECK
#endif
TEST_F(QorAISyncServiceImplDeathTest, MAYBE_EmulateGetOrCreateSyncCodeCHECK) {
  OSCryptMocker::SetUp();

  CreateSyncService();
  EXPECT_FALSE(engine());

  // Since Chromium commit 33441a0f3f9a591693157f2fd16852ce072e6f9d
  // we cannot change datatypes if we are not signed to sync, see changes
  // around SyncUserSettingsImpl::SetSelectedTypes.
  // Call pref_service()->SetString() below triggers
  // QorAISyncServiceImpl::OnQorAISyncPrefsChanged which sets kBookmarks type.
  // To workaround this, first set valid sync code to pretend we are signed in.
  bool set_code_result = qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);
  EXPECT_TRUE(set_code_result);

  std::string wrong_seed = "123";
  std::string encrypted_wrong_seed;
  EXPECT_TRUE(OSCrypt::EncryptString(wrong_seed, &encrypted_wrong_seed));

  pref_service()->SetString(qorai_sync::Prefs::GetSeedPath(),
                            base::Base64Encode(encrypted_wrong_seed));

  EXPECT_CHECK_DEATH(qorai_sync_service_impl()->GetOrCreateSyncCode());

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, StopAndClearForQorAISeed) {
  OSCryptMocker::SetUp();

  CreateSyncService();
  EXPECT_FALSE(engine());

  bool set_code_result = qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);
  EXPECT_TRUE(set_code_result);

  qorai_sync_service_impl()->StopAndClearWithResetLocalDataReason();

  bool failed_to_decrypt = false;
  EXPECT_EQ(qorai_sync_prefs()->GetSeed(&failed_to_decrypt), "");
  EXPECT_FALSE(failed_to_decrypt);

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, ForcedSetDecryptionPassphrase) {
  OSCryptMocker::SetUp();
  CreateSyncService();
  EXPECT_FALSE(engine());
  qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);

  task_environment_.RunUntilIdle();

  qorai_sync_service_impl()
      ->GetUserSettings()
      ->SetInitialSyncFeatureSetupComplete(
          syncer::SyncFirstSetupCompleteSource::ADVANCED_FLOW_CONFIRM);

  // Pretend we need the passphrase by triggering OnPassphraseRequired and
  // supplying the encrypted portion of data, as it is done in
  // sync_service_crypto_unittest.cc
  qorai_sync_service_impl()->GetCryptoForTests()->OnPassphraseRequired(
      KeyDerivationParams::CreateForPbkdf2(),
      MakeEncryptedData(kValidSyncCode,
                        KeyDerivationParams::CreateForPbkdf2()));

  EXPECT_TRUE(
      qorai_sync_service_impl()->GetUserSettings()->IsPassphraseRequired());

  // During the calls below:
  //    DataTypeManagerImpl::SetConfigurer()
  //    SyncServiceImpl::OnEngineInitialized()
  //    QorAISyncServiceImpl::OnEngineInitialized()
  // SetConfigurer method requires |DataTypeManagerImpl::state_| to be in a
  // STOPPED state.
  // Current unit test is intended to verify fix for qorai/qorai-browser#22898
  // and is about set encryption passphrase later setup after right after
  // enabling sync, for example when internet connection is unstable.
  // So we just make DataTypeManagerImpl::SetConfigurer requirements be
  // satisfied.
  // Related Chromium commit 7cdf92e9470fc73a09b871f99d14ff115edef652
  qorai_sync_service_impl()->data_type_manager_->Stop(KEEP_METADATA);

  // We have to cleanup SyncServiceCrypto.state_.engine with Reset
  // because on 2nd OnEngineInitialized call it is non-null and CHECK gets
  // invoked. Then call again OnPassphraseRequired/data_type_manager_->Stop.
  // Related Chromium change b0567d24a6da98c40363c693fccfd63688f43bb3.
  // TODO(alexeybarabash): revert PR#13397 if it is not required anymore.
  // https://github.com/qorai/qorai-browser/issues/39353

  qorai_sync_service_impl()->GetCryptoForTests()->Reset();
  qorai_sync_service_impl()->GetCryptoForTests()->OnPassphraseRequired(
      KeyDerivationParams::CreateForPbkdf2(),
      MakeEncryptedData(kValidSyncCode,
                        KeyDerivationParams::CreateForPbkdf2()));
  qorai_sync_service_impl()->data_type_manager_->Stop(KEEP_METADATA);

  qorai_sync_service_impl()->OnEngineInitialized(true, false);
  EXPECT_FALSE(
      qorai_sync_service_impl()->GetUserSettings()->IsPassphraseRequired());

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, OnSelfDeviceInfoDeleted) {
  OSCryptMocker::SetUp();
  CreateSyncService();
  EXPECT_FALSE(engine());

  qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);
  task_environment_.RunUntilIdle();

  std::unique_ptr<DataTypeManager> bak_data_type_manager =
      std::move(qorai_sync_service_impl()->data_type_manager_);
  // Replace DataTypeManager with mock who gives CONFIGURING result on state()
  // call. We need this to force SyncService::GetTransportState() give
  // TransportState::CONFIGURING status to test behavior
  // QorAISyncServiceImpl::OnSelfDeviceInfoDeleted.
  // Save original DataTypeManager to revert it before test exit.
  NiceMock<DataTypeManagerMock> data_type_manager_mock;
  std::unique_ptr<DataTypeManager> data_type_manager_mock_ptr =
      std::unique_ptr<DataTypeManager>(&data_type_manager_mock);

  qorai_sync_service_impl()->data_type_manager_ =
      std::move(data_type_manager_mock_ptr);

  ON_CALL(data_type_manager_mock, state())
      .WillByDefault(Return(DataTypeManager::CONFIGURING));

  EXPECT_EQ(qorai_sync_service_impl()->GetTransportState(),
            SyncServiceImpl::TransportState::CONFIGURING);

  NiceMock<SyncServiceObserverMock> observer_mock;
  qorai_sync_service_impl()->AddObserver(&observer_mock);

  // When OnSelfDeviceInfoDeleted arrived, but transport state is CONFIGURING,
  // we must not stop and clear service.
  EXPECT_CALL(observer_mock, OnStateChanged).Times(0);
  qorai_sync_service_impl()->OnSelfDeviceInfoDeleted(base::DoNothing());

  qorai_sync_service_impl()->RemoveObserver(&observer_mock);

  // Revert back qorai_sync_service_impl()->data_type_manager_ and
  // proper release local data_type_manager_mock_ptr
  data_type_manager_mock_ptr =
      std::move(qorai_sync_service_impl()->data_type_manager_);
  data_type_manager_mock_ptr.release();
  qorai_sync_service_impl()->data_type_manager_ =
      std::move(bak_data_type_manager);

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, PermanentlyDeleteAccount) {
  OSCryptMocker::SetUp();
  CreateSyncService();
  EXPECT_FALSE(engine());
  qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);
  task_environment_.RunUntilIdle();

  qorai_sync_service_impl()
      ->GetUserSettings()
      ->SetInitialSyncFeatureSetupComplete(
          syncer::SyncFirstSetupCompleteSource::ADVANCED_FLOW_CONFIRM);
  EXPECT_TRUE(engine());

  std::unique_ptr<testing::NiceMock<QorAIMockSyncEngine>> mock_sync_engine =
      std::make_unique<testing::NiceMock<QorAIMockSyncEngine>>();
  EXPECT_CALL(*mock_sync_engine, PermanentlyDeleteAccount).Times(1);
  std::unique_ptr<SyncEngine> engine_orig =
      std::move(qorai_sync_service_impl()->engine_);
  qorai_sync_service_impl()->engine_ = std::move(mock_sync_engine);
  qorai_sync_service_impl()->PermanentlyDeleteAccount(base::BindOnce(
      [](const syncer::SyncProtocolError& sync_protocol_error) {}));
  qorai_sync_service_impl()->engine_ = std::move(engine_orig);
  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, OnAccountDeleted_Success) {
  OSCryptMocker::SetUp();
  CreateSyncService();
  EXPECT_FALSE(engine());

  qorai_sync_service_impl()->initiated_delete_account_ = true;
  SyncProtocolError sync_protocol_error;
  sync_protocol_error.error_type = SYNC_SUCCESS;

  qorai_sync_service_impl()->OnAccountDeleted(
      1, base::BindOnce([](const syncer::SyncProtocolError& spe) {
        EXPECT_EQ(spe.error_type, SYNC_SUCCESS);
      }),
      sync_protocol_error);

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, OnAccountDeleted_FailureAndRetry) {
  OSCryptMocker::SetUp();
  CreateSyncService();
  EXPECT_FALSE(engine());

  qorai_sync_service_impl()->initiated_delete_account_ = true;
  SyncProtocolError sync_protocol_error;
  sync_protocol_error.error_type = TRANSIENT_ERROR;

  // Five unsuccessful attempts, the callback must be fired once, for the last
  // one
  bool was_callback_invoked[] = {false, false, false, false, true};

  for (size_t i = 0; i < std::size(was_callback_invoked); ++i) {
    bool on_account_deleted_invoked = false;
    qorai_sync_service_impl()->OnAccountDeleted(
        i + 1,
        base::BindOnce(
            [](bool* on_account_deleted_invoked,
               const syncer::SyncProtocolError& spe) {
              *on_account_deleted_invoked = true;
              EXPECT_EQ(spe.error_type, TRANSIENT_ERROR);
            },
            &on_account_deleted_invoked),
        sync_protocol_error);

    EXPECT_EQ(on_account_deleted_invoked, UNSAFE_TODO(was_callback_invoked[i]));
  }

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, JoinActiveOrNewChain) {
  OSCryptMocker::SetUp();
  CreateSyncService();
  EXPECT_FALSE(engine());

  EXPECT_FALSE(qorai_sync_service_impl()->join_chain_result_callback_);

  bool join_chain_callback_invoked = false;

  qorai_sync_service_impl()->SetJoinChainResultCallback(base::BindOnce(
      [](bool* join_chain_callback_invoked, bool join_succeeded) {
        *join_chain_callback_invoked = true;
        EXPECT_TRUE(join_succeeded);
      },
      &join_chain_callback_invoked));

  EXPECT_TRUE(qorai_sync_service_impl()->join_chain_result_callback_);
  EXPECT_FALSE(join_chain_callback_invoked);
  qorai_sync_service_impl()->LocalDeviceAppeared();
  EXPECT_TRUE(join_chain_callback_invoked);

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, JoinDeletedChain) {
  OSCryptMocker::SetUp();
  CreateSyncService();
  EXPECT_FALSE(engine());

  EXPECT_FALSE(qorai_sync_service_impl()->join_chain_result_callback_);

  bool join_chain_callback_invoked = false;

  qorai_sync_service_impl()->SetJoinChainResultCallback(base::BindOnce(
      [](bool* join_chain_callback_invoked, bool join_succeeded) {
        *join_chain_callback_invoked = true;
        EXPECT_FALSE(join_succeeded);
      },
      &join_chain_callback_invoked));

  EXPECT_TRUE(qorai_sync_service_impl()->join_chain_result_callback_);
  EXPECT_FALSE(join_chain_callback_invoked);
  EXPECT_FALSE(qorai_sync_service_impl()->initiated_self_device_info_deleted_);

  EXPECT_FALSE(qorai_sync_service_impl()->initiated_join_chain_);
  qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);
  EXPECT_TRUE(qorai_sync_service_impl()->initiated_join_chain_);

  // Normally sync_disabled_by_admin_ is set at
  // SyncServiceImpl::OnActionableError, but we can't invoke it, so set it
  // directly for test
  qorai_sync_service_impl()->sync_disabled_by_admin_ = true;
  qorai_sync_service_impl()->ResetEngine(
      SyncServiceImpl::ResetEngineReason::kDisabledAccount);

  EXPECT_TRUE(join_chain_callback_invoked);

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, HistoryPreconditions) {
  // This test ensures that QorAIHistoryDataTypeController and
  // QorAIHistoryDeleteDirectivesDataTypeController allow to run if
  // IsEncryptEverythingEnabled is set to true; upstream doesn't allow
  // History sync when encrypt everything is set to true.
  // The test is placed here alongside QorAISyncServiceImplTest because
  // here is the infrastructure which allows implement it.
  // Otherwise TestSyncUserSettings would not allow to override
  // IsEncryptEverythingEnabled.

  OSCryptMocker::SetUp();
  CreateSyncService();
  EXPECT_FALSE(engine());
  qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);
  task_environment_.RunUntilIdle();

  qorai_sync_service_impl()
      ->GetUserSettings()
      ->SetInitialSyncFeatureSetupComplete(
          syncer::SyncFirstSetupCompleteSource::ADVANCED_FLOW_CONFIRM);
  EXPECT_TRUE(engine());

  // Code below turns on encrypt everything
  qorai_sync_service_impl()->GetCryptoForTests()->OnEncryptedTypesChanged(
      AlwaysEncryptedUserTypes(), true);

  // Ensure encrypt everything was actually enabled
  EXPECT_TRUE(qorai_sync_service_impl()
                  ->GetUserSettings()
                  ->IsEncryptEverythingEnabled());

  auto history_data_type_controller =
      std::make_unique<history::QorAIHistoryDataTypeController>(
          qorai_sync_service_impl(), identity_manager(), nullptr,
          pref_service());

  auto history_precondition_state =
      history_data_type_controller->GetPreconditionState();
  EXPECT_EQ(history_precondition_state,
            DataTypeController::PreconditionState::kPreconditionsMet);

  auto test_data_type_store_service =
      std::make_unique<TestDataTypeStoreService>();
  auto history_delete_directives_data_type_controller =
      std::make_unique<history::QorAIHistoryDeleteDirectivesDataTypeController>(
          base::DoNothing(), qorai_sync_service_impl(),
          test_data_type_store_service.get(), nullptr, pref_service());

  auto history_delete_directives_precondition_state =
      history_delete_directives_data_type_controller->GetPreconditionState();
  EXPECT_EQ(history_delete_directives_precondition_state,
            DataTypeController::PreconditionState::kPreconditionsMet);

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, BookmarksAndPasswordsAfterSetup) {
  OSCryptMocker::SetUp();
  CreateSyncService();
  EXPECT_FALSE(engine());
  qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);
  task_environment_.RunUntilIdle();

  qorai_sync_service_impl()
      ->GetUserSettings()
      ->SetInitialSyncFeatureSetupComplete(
          syncer::SyncFirstSetupCompleteSource::ADVANCED_FLOW_CONFIRM);
  EXPECT_TRUE(engine());

  EXPECT_FALSE(
      qorai_sync_service_impl()->GetUserSettings()->IsSyncEverythingEnabled());
  auto selected_types =
      qorai_sync_service_impl()->GetUserSettings()->GetSelectedTypes();
  EXPECT_EQ(selected_types.size(), 2u);
  EXPECT_TRUE(selected_types.Has(UserSelectableType::kBookmarks));
  EXPECT_TRUE(selected_types.Has(UserSelectableType::kPasswords));

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, P3aForHistoryThroughDelegate) {
  OSCryptMocker::SetUp();
  CreateSyncService(DataTypeSet({BOOKMARKS, HISTORY, PASSWORDS}));
  EXPECT_FALSE(engine());
  qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);
  task_environment_.RunUntilIdle();

  base::HistogramTester histogram_tester;

  qorai_sync_service_impl()->synced_objects_context_.Reset(1);

  syncer::TypeEntitiesCount bookmarks_count(syncer::BOOKMARKS);
  bookmarks_count.entities = bookmarks_count.non_tombstone_entities = 1;

  qorai_sync_service_impl()->OnGetTypeEntitiesCount(bookmarks_count);

  histogram_tester.ExpectBucketCount(
      qorai_sync::p3a::kSyncedObjectsCountHistogramNameV2, 0, 1);

  // Enable History and pretend we got its number from delegate.
  // We need to have setup handle, otherwise
  // |SyncUserSettingsImpl::SetSelectedTypes| and
  // |SyncUserSettingsImpl::GetSelectedTypes| work wrong
  auto sync_blocker = qorai_sync_service_impl()->GetSetupInProgressHandle();
  auto selected_types =
      qorai_sync_service_impl()->GetUserSettings()->GetSelectedTypes();
  selected_types.Put(UserSelectableType::kHistory);
  qorai_sync_service_impl()->GetUserSettings()->SetSelectedTypes(
      false, selected_types);

  ON_CALL(*sync_service_delegate(), GetKnownToSyncHistoryCount(_))
      .WillByDefault(
          [](base::OnceCallback<void(std::pair<bool, int>)> callback) {
            std::move(callback).Run(std::pair<bool, int>(true, 10001));
          });

  qorai_sync_service_impl()->synced_objects_context_.Reset(1);
  qorai_sync_service_impl()->OnGetTypeEntitiesCount(bookmarks_count);
  histogram_tester.ExpectBucketCount(
      qorai_sync::p3a::kSyncedObjectsCountHistogramNameV2, 2, 1);

  OSCryptMocker::TearDown();
}

TEST_F(QorAISyncServiceImplTest, NoLeaveDetailsWhenInitializeIOS) {
  CreateSyncService();

  // Pretend for test that we are doing iOS behaviour for leave sync chain
  // details, becuase QorAISyncServiceImplTest.NoLeaveDetailsWhenInitializeIOS
  // is not executed on iOS
  qorai_sync_prefs()->SetAddLeaveChainDetailBehaviourForTests(
      qorai_sync::Prefs::AddLeaveChainDetailBehaviour::kAdd);

  qorai_sync_prefs()->AddLeaveChainDetail(__FILE__, __LINE__, "details");

  size_t leave_chain_pref_changed_count = 0;

  PrefChangeRegistrar qorai_sync_prefs_change_registrar_;
  qorai_sync_prefs_change_registrar_.Init(pref_service());
  qorai_sync_prefs_change_registrar_.Add(
      qorai_sync::Prefs::GetLeaveChainDetailsPathForTests(),
      base::BindRepeating(
          [](size_t* leave_chain_pref_changed_count) {
            ++(*leave_chain_pref_changed_count);
          },
          &leave_chain_pref_changed_count));
  EXPECT_FALSE(engine());

  // We expect that AddLeaveChainDetail will not be invoked at
  // SyncServiceImpl::Initialize and details will not be cleared
  EXPECT_EQ(leave_chain_pref_changed_count, 0u);
  EXPECT_FALSE(qorai_sync_prefs()->GetLeaveChainDetails().empty());
}

class QorAISyncServiceImplTest_DisableSyncDefaultPasswordsTest
    : public QorAISyncServiceImplTest {
 public:
  QorAISyncServiceImplTest_DisableSyncDefaultPasswordsTest() {
    scoped_feature_list_.InitAndDisableFeature(
        qorai_sync::features::kQorAISyncDefaultPasswords);
  }

 protected:
  base::test::ScopedFeatureList scoped_feature_list_;
};

TEST_F(QorAISyncServiceImplTest_DisableSyncDefaultPasswordsTest,
       OnlyBookmarks) {
  OSCryptMocker::SetUp();
  CreateSyncService();
  EXPECT_FALSE(engine());

  base::RunLoop engine_waiter;
  base::RepeatingClosure quit_closure = engine_waiter.QuitClosure();
  NiceMock<SyncServiceObserverMock> observer_mock;
  ON_CALL(observer_mock, OnStateChanged(_))
      .WillByDefault([this, quit_closure]() {
        if (engine()) {
          quit_closure.Run();
        }
      });
  qorai_sync_service_impl()->AddObserver(&observer_mock);

  qorai_sync_service_impl()->SetSyncCode(kValidSyncCode);

  engine_waiter.Run();

  qorai_sync_service_impl()->RemoveObserver(&observer_mock);

  qorai_sync_service_impl()
      ->GetUserSettings()
      ->SetInitialSyncFeatureSetupComplete(
          syncer::SyncFirstSetupCompleteSource::ADVANCED_FLOW_CONFIRM);
  EXPECT_TRUE(engine());

  EXPECT_FALSE(
      qorai_sync_service_impl()->GetUserSettings()->IsSyncEverythingEnabled());
  auto selected_types =
      qorai_sync_service_impl()->GetUserSettings()->GetSelectedTypes();
  EXPECT_EQ(selected_types.size(), 1u);
  EXPECT_TRUE(selected_types.Has(UserSelectableType::kBookmarks));
  EXPECT_FALSE(selected_types.Has(UserSelectableType::kPasswords));

  OSCryptMocker::TearDown();
}

namespace {
enum class GACookiesMethodType {
  kOnAccountsCookieDeletedByUserAction,
  kOnAccountsInCookieUpdated,
  kOnPrimaryAccountChanged
};
}

class QorAISyncServiceImplGACookiesTest
    : public QorAISyncServiceImplTest,
      public testing::WithParamInterface<GACookiesMethodType> {
 public:
  base::OnceCallback<void(void)> GetGACookiesMethod() {
    switch (GetParam()) {
      case GACookiesMethodType::kOnAccountsCookieDeletedByUserAction:
        return base::BindOnce(
            [](QorAISyncServiceImplGACookiesTest* p_this) {
              p_this->qorai_sync_service_impl()
                  ->OnAccountsCookieDeletedByUserAction();
            },
            this);
      case GACookiesMethodType::kOnAccountsInCookieUpdated:
        return base::BindOnce(
            [](QorAISyncServiceImplGACookiesTest* p_this) {
              p_this->qorai_sync_service_impl()->OnAccountsInCookieUpdated(
                  signin::AccountsInCookieJarInfo(), GoogleServiceAuthError());
            },
            this);
      case GACookiesMethodType::kOnPrimaryAccountChanged:
        return base::BindOnce(
            [](QorAISyncServiceImplGACookiesTest* p_this) {
              CoreAccountInfo prev_account_info;
              prev_account_info.email = "usertest@gmail.com";
              prev_account_info.gaia = GaiaId("gaia");
              prev_account_info.account_id =
                  CoreAccountId::FromGaiaId(prev_account_info.gaia);

              signin::PrimaryAccountChangeEvent primary_accountchange_event(
                  signin::PrimaryAccountChangeEvent::State(
                      prev_account_info, signin::ConsentLevel::kSignin),
                  signin::PrimaryAccountChangeEvent::State(),
                  signin_metrics::ProfileSignout::kTest);

              p_this->qorai_sync_service_impl()->OnPrimaryAccountChanged(
                  primary_accountchange_event);
            },
            this);
    }
    NOTREACHED();
  }
};

TEST_P(QorAISyncServiceImplGACookiesTest, CacheGuidIsNotWiped) {
  SyncTransportDataPrefs::RegisterProfilePrefs(pref_service()->registry());

  SyncTransportDataPrefs sync_transport_data_prefs(
      pref_service(), signin::GaiaIdHash::FromGaiaId(GaiaId("user_gaia_id")));

  sync_transport_data_prefs.SetCacheGuid(kCacheGuid);

  CreateSyncService();

  std::move(GetGACookiesMethod()).Run();

  EXPECT_EQ(sync_transport_data_prefs.GetCacheGuid(), kCacheGuid);
}

INSTANTIATE_TEST_SUITE_P(
    All,
    QorAISyncServiceImplGACookiesTest,
    testing::ValuesIn(
        {GACookiesMethodType::kOnAccountsCookieDeletedByUserAction,
         GACookiesMethodType::kOnAccountsInCookieUpdated,
         GACookiesMethodType::kOnPrimaryAccountChanged}),
    [](const testing::TestParamInfo<
        QorAISyncServiceImplGACookiesTest::ParamType>& info) {
      switch (info.param) {
        case GACookiesMethodType::kOnAccountsCookieDeletedByUserAction:
          return "OnAccountsCookieDeletedByUserAction";
        case GACookiesMethodType::kOnAccountsInCookieUpdated:
          return "OnAccountsInCookieUpdated";
        case GACookiesMethodType::kOnPrimaryAccountChanged:
          return "OnPrimaryAccountChanged";
      }
      NOTREACHED();
    });

}  // namespace syncer
