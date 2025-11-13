/* Copyright (c) 2020 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/sync/service/qorai_sync_service_impl.h"

#include <utility>
#include <vector>

#include "base/auto_reset.h"
#include "base/check.h"
#include "base/check_op.h"
#include "base/logging.h"
#include "base/metrics/histogram_functions.h"
#include "base/strings/string_util.h"
#include "qorai/components/qorai_sync/qorai_sync_p3a.h"
#include "qorai/components/qorai_sync/crypto/crypto.h"
#include "qorai/components/qorai_sync/features.h"
#include "qorai/components/sync/service/qorai_sync_auth_manager.h"
#include "qorai/components/sync/service/sync_service_impl_delegate.h"
#include "build/build_config.h"
#include "components/prefs/pref_service.h"
#include "components/sync/engine/sync_protocol_error.h"
#include "components/sync/model/type_entities_count.h"

namespace syncer {

void QorAISyncServiceImpl::SyncedObjectsCountContext::Reset(
    size_t types_requested_init) {
  types_requested = types_requested_init;
  types_responed = 0;
  total_objects_count = 0;
}

QorAISyncServiceImpl::QorAISyncServiceImpl(
    InitParams init_params,
    std::unique_ptr<SyncServiceImplDelegate> sync_service_impl_delegate)
    : SyncServiceImpl(std::move(init_params)),
      qorai_sync_prefs_(sync_client_->GetPrefService()),
      sync_service_impl_delegate_(std::move(sync_service_impl_delegate)),
      weak_ptr_factory_(this) {
  qorai_sync_prefs_change_registrar_.Init(sync_client_->GetPrefService());
  qorai_sync_prefs_change_registrar_.Add(
      qorai_sync::Prefs::GetSeedPath(),
      base::BindRepeating(&QorAISyncServiceImpl::OnQorAISyncPrefsChanged,
                          base::Unretained(this)));
  bool failed_to_decrypt = false;
  GetQorAISyncAuthManager()->DeriveSigningKeys(
      qorai_sync_prefs_.GetSeed(&failed_to_decrypt));
  DCHECK(!failed_to_decrypt);

  sync_service_impl_delegate_->set_profile_sync_service(this);
}

QorAISyncServiceImpl::~QorAISyncServiceImpl() {
  qorai_sync_prefs_change_registrar_.RemoveAll();
}

void QorAISyncServiceImpl::Initialize(
    DataTypeController::TypeVector controllers) {
  base::AutoReset<bool> is_initializing_resetter(&is_initializing_, true);

  SyncServiceImpl::Initialize(std::move(controllers));

  // P3A ping for those who have sync disabled
  if (!user_settings_->IsInitialSyncFeatureSetupComplete()) {
    base::UmaHistogramExactLinear("QorAI.Sync.Status.2", 0, 3);
  }
}

bool QorAISyncServiceImpl::IsSetupInProgress() const {
  return SyncServiceImpl::IsSetupInProgress() &&
         !user_settings_->IsInitialSyncFeatureSetupComplete();
}

void QorAISyncServiceImpl::StopAndClear(ResetEngineReason reset_engine_reason) {
  // StopAndClear is invoked during |SyncServiceImpl::Initialize| even if sync
  // is not enabled. This adds lots of useless lines into
  // `qorai_sync_v2.diag.leave_chain_details`
  if (!is_initializing_) {
    qorai_sync_prefs_.AddLeaveChainDetail(__FILE__, __LINE__, __func__);
  }
  // Clear prefs before StopAndClear() to make NotifyObservers() be invoked
  qorai_sync_prefs_.Clear();
  SyncServiceImpl::StopAndClear(reset_engine_reason);
}

std::string QorAISyncServiceImpl::GetOrCreateSyncCode() {
  bool failed_to_decrypt = false;
  std::string sync_code = qorai_sync_prefs_.GetSeed(&failed_to_decrypt);

  if (failed_to_decrypt) {
    // Do not try to re-create seed when OSCrypt fails, for example on macOS
    // when the keyring is locked.
    DCHECK(sync_code.empty());
    return std::string();
  }

  if (sync_code.empty()) {
    std::vector<uint8_t> seed = qorai_sync::crypto::GetSeed();
    sync_code = qorai_sync::crypto::PassphraseFromBytes32(seed);
    sync_code_monitor_.RecordCodeGenerated();
  }

  CHECK(!sync_code.empty()) << "Attempt to return empty sync code";
  CHECK(qorai_sync::crypto::IsPassphraseValid(sync_code))
      << "Attempt to return non-valid sync code";

  return sync_code;
}

bool QorAISyncServiceImpl::SetSyncCode(const std::string& sync_code) {
  std::string sync_code_trimmed;
  base::TrimString(sync_code, " \n\t", &sync_code_trimmed);
  if (!qorai_sync::crypto::IsPassphraseValid(sync_code_trimmed)) {
    return false;
  }
  if (!qorai_sync_prefs_.SetSeed(sync_code_trimmed)) {
    return false;
  }

  initiated_delete_account_ = false;
  initiated_self_device_info_deleted_ = false;
  initiated_join_chain_ = true;

  sync_code_monitor_.RecordCodeSet();

  return true;
}

void QorAISyncServiceImpl::OnSelfDeviceInfoDeleted(base::OnceClosure cb) {
  qorai_sync_prefs_.AddLeaveChainDetail(__FILE__, __LINE__, __func__);
  initiated_self_device_info_deleted_ = true;
  // This function will follow normal reset process and set SyncRequested to
  // false

  // We need this to avoid |StopAndClear| call below when initiating sync
  // chain after clear data when the sync passphrase wasn't decrypted.
  // Otherwise we have these calls:
  // ---
  // QorAISyncServiceImplDelegate::OnDeviceInfoChange()
  // ...
  // ClientTagBasedDataTypeProcessor::ClearAllMetadataAndResetStateImpl()
  // ...
  // ClientTagBasedDataTypeProcessor::OnSyncStarting()
  // ---
  // Note that `ClearAllTrackedMetadataAndResetState` will only be called during
  // init when sync seed decryption key mismatched.
  if (GetTransportState() != TransportState::CONFIGURING) {
    StopAndClear(ResetEngineReason::kResetLocalData);
  }

  std::move(cb).Run();
}

QorAISyncAuthManager* QorAISyncServiceImpl::GetQorAISyncAuthManager() {
  return static_cast<QorAISyncAuthManager*>(auth_manager_.get());
}

void QorAISyncServiceImpl::OnQorAISyncPrefsChanged(const std::string& path) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  if (path == qorai_sync::Prefs::GetSeedPath()) {
    bool failed_to_decrypt = false;
    const std::string seed = qorai_sync_prefs_.GetSeed(&failed_to_decrypt);
    DCHECK(!failed_to_decrypt);

    if (!seed.empty()) {
      GetQorAISyncAuthManager()->DeriveSigningKeys(seed);
      // Default enabled types: Bookmarks, Passwords

      // Related Chromium change: 33441a0f3f9a591693157f2fd16852ce072e6f9d
      // We need to acquire setup handle before change selected types.
      // See changes at |SyncServiceImpl::GetSyncAccountStateForPrefs| and
      // |SyncUserSettingsImpl::SetSelectedTypes|
      auto sync_blocker = GetSetupInProgressHandle();

      syncer::UserSelectableTypeSet selected_types;
      selected_types.Put(UserSelectableType::kBookmarks);
      if (base::FeatureList::IsEnabled(
              qorai_sync::features::kQorAISyncDefaultPasswords)) {
        selected_types.Put(UserSelectableType::kPasswords);
      }
      GetUserSettings()->SetSelectedTypes(false, selected_types);

      qorai_sync_prefs_.ClearLeaveChainDetails();
    } else {
      VLOG(1) << "QorAI sync seed cleared";
      qorai_sync_prefs_.AddLeaveChainDetail(__FILE__, __LINE__, __func__);
      GetQorAISyncAuthManager()->ResetKeys();
      // Send updated status here, because OnDeviceInfoChange is not triggered
      // when device leaves the chain by `Leave Sync Chain` button
      // 0 means disabled or 1 device
      base::UmaHistogramExactLinear("QorAI.Sync.Status.2", 0, 3);
    }
  }
}

void QorAISyncServiceImpl::SuspendDeviceObserverForOwnReset() {
  sync_service_impl_delegate_->SuspendDeviceObserverForOwnReset();
}

void QorAISyncServiceImpl::ResumeDeviceObserver() {
  sync_service_impl_delegate_->ResumeDeviceObserver();
}

void QorAISyncServiceImpl::OnEngineInitialized(
    bool success,
    bool is_first_time_sync_configure) {
  SyncServiceImpl::OnEngineInitialized(success, is_first_time_sync_configure);
  if (!IsEngineInitialized()) {
    return;
  }

  syncer::SyncUserSettings* sync_user_settings = GetUserSettings();
  if (!sync_user_settings->IsInitialSyncFeatureSetupComplete()) {
    // If first setup has not been complete, we don't need to force
    return;
  }

  bool failed_to_decrypt = false;
  std::string passphrase = qorai_sync_prefs_.GetSeed(&failed_to_decrypt);
  DCHECK(!failed_to_decrypt);
  if (passphrase.empty()) {
    return;
  }

  if (sync_user_settings->IsPassphraseRequired()) {
    bool set_passphrase_result =
        sync_user_settings->SetDecryptionPassphrase(passphrase);
    VLOG(1) << "Forced set decryption passphrase result is "
            << set_passphrase_result;
  }
}

SyncServiceCrypto* QorAISyncServiceImpl::GetCryptoForTests() {
  return &crypto_;
}

namespace {
constexpr int kMaxPermanentlyDeleteSyncAccountAttempts = 5;
constexpr int kDelayBetweenDeleteSyncAccountAttemptsMsec = 500;
}  // namespace

void QorAISyncServiceImpl::OnAccountDeleted(
    const int current_attempt,
    base::OnceCallback<void(const SyncProtocolError&)> callback,
    const SyncProtocolError& sync_protocol_error) {
  qorai_sync_prefs_.AddLeaveChainDetail(__FILE__, __LINE__, __func__);
  if (sync_protocol_error.error_type == SYNC_SUCCESS) {
    std::move(callback).Run(sync_protocol_error);
    // If request succeded - reset and clear all in a forced way
    // The code below cleans all on an initiator device. Other devices in the
    // chain will be cleaned at QorAISyncServiceImpl::ResetEngine
    DCHECK(initiated_delete_account_);
    QorAISyncServiceImpl::StopAndClear(ResetEngineReason::kDisabledAccount);
  } else if (current_attempt < kMaxPermanentlyDeleteSyncAccountAttempts) {
    // Server responded failure, but we need to try more
    base::SequencedTaskRunner::GetCurrentDefault()->PostDelayedTask(
        FROM_HERE,
        base::BindOnce(&QorAISyncServiceImpl::PermanentlyDeleteAccountImpl,
                       weak_ptr_factory_.GetWeakPtr(), current_attempt + 1,
                       std::move(callback)),
        base::Milliseconds(kDelayBetweenDeleteSyncAccountAttemptsMsec));
  } else {
    // Server responded failure, and we are out of our attempts
    initiated_delete_account_ = false;
    std::move(callback).Run(sync_protocol_error);
  }
}

void QorAISyncServiceImpl::PermanentlyDeleteAccountImpl(
    const int current_attempt,
    base::OnceCallback<void(const SyncProtocolError&)> callback) {
  qorai_sync_prefs_.AddLeaveChainDetail(__FILE__, __LINE__, __func__);
  if (!engine_) {
    // We can reach here if two devices almost at the same time will initiate
    // the deletion procedure
    SyncProtocolError sync_protocol_error;
    sync_protocol_error.error_type = SYNC_SUCCESS;
    std::move(callback).Run(sync_protocol_error);
    return;
  }

  DCHECK_GE(current_attempt, 1);
  DCHECK_NE(current_attempt, 10);

  engine_->PermanentlyDeleteAccount(base::BindOnce(
      &QorAISyncServiceImpl::OnAccountDeleted, weak_ptr_factory_.GetWeakPtr(),
      current_attempt, std::move(callback)));
}

void QorAISyncServiceImpl::PermanentlyDeleteAccount(
    base::OnceCallback<void(const SyncProtocolError&)> callback) {
  qorai_sync_prefs_.AddLeaveChainDetail(__FILE__, __LINE__, __func__);
  initiated_delete_account_ = true;
  PermanentlyDeleteAccountImpl(1, std::move(callback));
}

std::unique_ptr<SyncEngine> QorAISyncServiceImpl::ResetEngine(
    ResetEngineReason reset_reason) {
  auto result = SyncServiceImpl::ResetEngine(reset_reason);
  auto shutdown_reason =
      SyncServiceImpl::ShutdownReasonForResetEngineReason(reset_reason);

  if (initiated_self_device_info_deleted_) {
    return result;
  }

  if (shutdown_reason == ShutdownReason::DISABLE_SYNC_AND_CLEAR_DATA &&
      reset_reason == ResetEngineReason::kDisabledAccount &&
      sync_disabled_by_admin_ && !initiated_delete_account_ &&
      !initiated_join_chain_) {
    qorai_sync_prefs_.AddLeaveChainDetail(__FILE__, __LINE__, __func__);
    qorai_sync_prefs_.SetSyncAccountDeletedNoticePending(true);
    // Forcing stop and clear, because sync account was deleted
    QorAISyncServiceImpl::StopAndClear(ResetEngineReason::kResetLocalData);
  } else if (shutdown_reason == ShutdownReason::DISABLE_SYNC_AND_CLEAR_DATA &&
             reset_reason == ResetEngineReason::kDisabledAccount &&
             sync_disabled_by_admin_ && initiated_join_chain_) {
    qorai_sync_prefs_.AddLeaveChainDetail(__FILE__, __LINE__, __func__);
    // Forcing stop and clear, because we are trying to join the sync chain, but
    // sync account was deleted
    QorAISyncServiceImpl::StopAndClear(ResetEngineReason::kResetLocalData);
    // When it will be merged into master, iOS code will be a bit behind,
    // so don't expect join_chain_result_callback_ is set, but get CHECK back
    // once iOS changes will handle this
    LOG_IF(ERROR, !join_chain_result_callback_)
        << "[QorAISync] " << __func__
        << " join_chain_result_callback_ must be set";
    if (join_chain_result_callback_) {
      std::move(join_chain_result_callback_).Run(false);
    }
  }
  return result;
}

void QorAISyncServiceImpl::SetJoinChainResultCallback(
    base::OnceCallback<void(bool)> callback) {
  join_chain_result_callback_ = std::move(callback);

  sync_service_impl_delegate_->SetLocalDeviceAppearedCallback(
      base::BindOnce(&QorAISyncServiceImpl::LocalDeviceAppeared,
                     weak_ptr_factory_.GetWeakPtr()));
}

void QorAISyncServiceImpl::LocalDeviceAppeared() {
  initiated_join_chain_ = false;
  DCHECK(join_chain_result_callback_);
  std::move(join_chain_result_callback_).Run(true);
  SyncServiceImpl::NotifyObservers();
}

namespace {
// Typical cycle takes 30 sec, let's send P3A updates each ~30 minutes
constexpr int kCyclesBeforeUpdateP3AObjects = 60;
// And Let's do the first update in ~5 minutes after sync start
constexpr int kCyclesBeforeFirstUpdatesP3A = 10;
}  // namespace

void QorAISyncServiceImpl::OnSyncCycleCompleted(
    const SyncCycleSnapshot& snapshot) {
  SyncServiceImpl::OnSyncCycleCompleted(snapshot);
  if (completed_cycles_count_ == kCyclesBeforeFirstUpdatesP3A ||
      completed_cycles_count_ % kCyclesBeforeUpdateP3AObjects == 0) {
    UpdateP3AObjectsNumber();
  }
  ++completed_cycles_count_;
}

void QorAISyncServiceImpl::UpdateP3AObjectsNumber() {
  synced_objects_context_.Reset(GetUserSettings()->GetSelectedTypes().size());

  data_type_manager_->GetEntityCountsForDebugging(
      base::BindRepeating(&QorAISyncServiceImpl::OnGetTypeEntitiesCount,
                          weak_ptr_factory_.GetWeakPtr()));
}

void QorAISyncServiceImpl::OnGetTypeEntitiesCount(
    const TypeEntitiesCount& count) {
  ++synced_objects_context_.types_responed;
  synced_objects_context_.total_objects_count += count.non_tombstone_entities;
  if (synced_objects_context_.types_responed ==
      synced_objects_context_.types_requested) {
    if (GetUserSettings()->GetSelectedTypes().Has(
            syncer::UserSelectableType::kHistory)) {
      // History stores info about synced objects in a different way than the
      // others types. Issue a separate request to achieve this info
      sync_service_impl_delegate_->GetKnownToSyncHistoryCount(base::BindOnce(
          [](int total_entities, std::pair<bool, int> known_to_sync_count) {
            qorai_sync::p3a::RecordSyncedObjectsCount(
                total_entities + known_to_sync_count.second);
          },
          synced_objects_context_.total_objects_count));
    } else {
      qorai_sync::p3a::RecordSyncedObjectsCount(
          synced_objects_context_.total_objects_count);
    }
  }
}

void QorAISyncServiceImpl::OnSelectedTypesChanged() {
  SyncServiceImpl::OnSelectedTypesChanged();

  qorai_sync::p3a::RecordEnabledTypes(
      GetUserSettings()->IsSyncEverythingEnabled(),
      GetUserSettings()->GetSelectedTypes());
}

void QorAISyncServiceImpl::StopAndClearWithShutdownReason() {
  StopAndClear(ResetEngineReason::kShutdown);
}

void QorAISyncServiceImpl::StopAndClearWithResetLocalDataReason() {
  StopAndClear(ResetEngineReason::kResetLocalData);
}

void QorAISyncServiceImpl::OnAccountsCookieDeletedByUserAction() {}

void QorAISyncServiceImpl::OnAccountsInCookieUpdated(
    const signin::AccountsInCookieJarInfo& accounts_in_cookie_jar_info,
    const GoogleServiceAuthError& error) {}

void QorAISyncServiceImpl::OnPrimaryAccountChanged(
    const signin::PrimaryAccountChangeEvent& event_details) {}

}  // namespace syncer
