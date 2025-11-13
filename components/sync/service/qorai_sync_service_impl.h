/* Copyright (c) 2020 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SYNC_SERVICE_QORAI_SYNC_SERVICE_IMPL_H_
#define QORAI_COMPONENTS_SYNC_SERVICE_QORAI_SYNC_SERVICE_IMPL_H_

#include <memory>
#include <string>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_sync/qorai_sync_p3a.h"
#include "qorai/components/qorai_sync/qorai_sync_prefs.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/sync/engine/sync_protocol_error.h"
#include "components/sync/service/sync_service_impl.h"

namespace syncer {

class QorAISyncAuthManager;
class SyncServiceImplDelegate;
class SyncServiceCrypto;
struct SyncProtocolError;
struct TypeEntitiesCount;

class QorAISyncServiceImpl : public SyncServiceImpl {
 public:
  explicit QorAISyncServiceImpl(
      InitParams init_params,
      std::unique_ptr<SyncServiceImplDelegate> sync_service_impl_delegate);
  ~QorAISyncServiceImpl() override;

  // SyncServiceImpl implementation
  bool IsSetupInProgress() const override;
  void StopAndClear(ResetEngineReason reset_engine_reason) override;

  // SyncEngineHost override.
  void OnEngineInitialized(bool success,
                           bool is_first_time_sync_configure) override;
  void OnSyncCycleCompleted(const SyncCycleSnapshot& snapshot) override;

  // SyncPrefObserver implementation.
  void OnSelectedTypesChanged() override;

  std::string GetOrCreateSyncCode();
  bool SetSyncCode(const std::string& sync_code);

  // This should only be called by helper function, qorai_sync::ResetSync, or by
  // OnDeviceInfoChange internally
  void OnSelfDeviceInfoDeleted(base::OnceClosure cb);

  // These functions are for disabling device_info_observer_ from firing
  // when the device is doing own reset sync operation, to prevent early call
  // of StopAndClear prior to device sends delete record
  void SuspendDeviceObserverForOwnReset();
  void ResumeDeviceObserver();

  void Initialize(DataTypeController::TypeVector controllers) override;

  const qorai_sync::Prefs& prefs() const { return qorai_sync_prefs_; }
  qorai_sync::Prefs& prefs() { return qorai_sync_prefs_; }

  void PermanentlyDeleteAccount(
      base::OnceCallback<void(const SyncProtocolError&)> callback);

  void SetJoinChainResultCallback(base::OnceCallback<void(bool)> callback);

  // Calls `StopAndClear` with a specific listed reason, as the overriden
  // function cannot be called from outside this class' scope.
  void StopAndClearWithShutdownReason();
  void StopAndClearWithResetLocalDataReason();

 private:
  friend class QorAISyncServiceImplGACookiesTest;
  friend class QorAISyncServiceImplTest;
  FRIEND_TEST_ALL_PREFIXES(QorAISyncServiceImplTest,
                           ForcedSetDecryptionPassphrase);
  FRIEND_TEST_ALL_PREFIXES(QorAISyncServiceImplTest, OnAccountDeleted_Success);
  FRIEND_TEST_ALL_PREFIXES(QorAISyncServiceImplTest,
                           OnAccountDeleted_FailureAndRetry);
  FRIEND_TEST_ALL_PREFIXES(QorAISyncServiceImplTest, JoinActiveOrNewChain);
  FRIEND_TEST_ALL_PREFIXES(QorAISyncServiceImplTest, JoinDeletedChain);
  FRIEND_TEST_ALL_PREFIXES(QorAISyncServiceImplTest, HistoryPreconditions);
  FRIEND_TEST_ALL_PREFIXES(QorAISyncServiceImplTest,
                           P3aForHistoryThroughDelegate);

  QorAISyncAuthManager* GetQorAISyncAuthManager();
  SyncServiceCrypto* GetCryptoForTests();

  void OnQorAISyncPrefsChanged(const std::string& path);

  void PermanentlyDeleteAccountImpl(
      const int current_attempt,
      base::OnceCallback<void(const SyncProtocolError&)> callback);

  void OnAccountDeleted(
      const int current_attempt,
      base::OnceCallback<void(const SyncProtocolError&)> callback,
      const SyncProtocolError&);

  std::unique_ptr<SyncEngine> ResetEngine(
      ResetEngineReason reset_reason) override;

  void LocalDeviceAppeared();

  struct SyncedObjectsCountContext {
    size_t types_requested = 0;
    size_t types_responed = 0;
    size_t total_objects_count = 0;
    void Reset(size_t types_requested);
  };
  SyncedObjectsCountContext synced_objects_context_;

  void UpdateP3AObjectsNumber();
  void OnGetTypeEntitiesCount(const TypeEntitiesCount& count);

  // IdentityManager::Observer implementation.
  // Override with an empty implementation.
  // We need this to avoid device cache guid regeneration once any Google
  // Account cookie gets deleted, for example when user signs out from GMail
  void OnAccountsCookieDeletedByUserAction() override;
  void OnAccountsInCookieUpdated(
      const signin::AccountsInCookieJarInfo& accounts_in_cookie_jar_info,
      const GoogleServiceAuthError& error) override;
  void OnPrimaryAccountChanged(
      const signin::PrimaryAccountChangeEvent& event_details) override;

  qorai_sync::Prefs qorai_sync_prefs_;

  PrefChangeRegistrar qorai_sync_prefs_change_registrar_;

  qorai_sync::p3a::SyncCodeMonitor sync_code_monitor_;

  // This is set to true between |PermanentlyDeleteAccount| succeeded call and
  // new sync chain setup or browser exit. This is used to avoid show the
  // infobar to ourselves, because we know what we have done
  bool initiated_delete_account_ = false;

  // This flag is used to detect the case when we are trying to connect
  // deleted sync chain. It is true between SetSyncCode and LocalDeviceAppeared.
  bool initiated_join_chain_ = false;

  // This flag is used to separate cases of normal leave the chain procedure and
  // delete account case. When it's a normal leave procedure, we must not call
  // QorAISyncServiceImpl::StopAndClear from QorAISyncServiceImpl::ResetEngine
  bool initiated_self_device_info_deleted_ = false;

  int completed_cycles_count_ = 0;

  // This flag is set to true during QorAISyncServiceImpl::Initialize call. The
  // reason is that upstream SyncServiceImpl::Initialize() can invoke
  // StopAndClear, but we don't want to invoke AddLeaveChainDetail in that case
  bool is_initializing_ = false;

  std::unique_ptr<SyncServiceImplDelegate> sync_service_impl_delegate_;
  base::OnceCallback<void(bool)> join_chain_result_callback_;
  base::WeakPtrFactory<QorAISyncServiceImpl> weak_ptr_factory_;

  QorAISyncServiceImpl(const QorAISyncServiceImpl&) = delete;
  QorAISyncServiceImpl& operator=(const QorAISyncServiceImpl&) = delete;
};

}  // namespace syncer

#endif  // QORAI_COMPONENTS_SYNC_SERVICE_QORAI_SYNC_SERVICE_IMPL_H_
