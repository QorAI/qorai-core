/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/sync/service/sync_internals_util.h"

#include "base/check_op.h"
#include "qorai/components/sync/service/qorai_sync_service_impl.h"
#include "components/os_crypt/sync/os_crypt.h"

#define ConstructAboutInformation ConstructAboutInformation_ChromiumImpl
#include <components/sync/service/sync_internals_util.cc>
#undef ConstructAboutInformation

namespace syncer::sync_ui_util {

base::Value::Dict ConstructAboutInformation(
    IncludeSensitiveData include_sensitive_data,
    SyncService* service,
    const std::string& channel) {
  auto about_info = ConstructAboutInformation_ChromiumImpl(
      include_sensitive_data, service, channel);

  Section section_qorai_sync("Qorai Sync", /*is_sensitive=*/false);

  Stat<bool>* is_passphrase_set =
      section_qorai_sync.AddBoolStat("Passphrase is set");
  QoraiSyncServiceImpl* qorai_sync_service =
      static_cast<QoraiSyncServiceImpl*>(service);
  bool failed_to_decrypt = false;
  std::string seed = qorai_sync_service->prefs().GetSeed(&failed_to_decrypt);
  // If the passphrase has been set, either we can see it or we failed to
  // decrypt it
  bool is_passphrase_set_val = !seed.empty() || failed_to_decrypt;
  is_passphrase_set->Set(is_passphrase_set_val);

  // OSCrypt behavior varies depending on OS. It is possible that
  // OSCrypt::IsEncryptionAvailable reports false, but OSCrypt::DecryptString
  // succeeds. So put the additional field with actual decryption result.
  if (failed_to_decrypt) {
    Stat<bool>* failed_to_decrypt_passphrase =
        section_qorai_sync.AddBoolStat("Passphrase decryption failed");
    failed_to_decrypt_passphrase->Set(true);
  }

  Stat<bool>* is_os_encryption_available =
      section_qorai_sync.AddBoolStat("OS encryption available");
  is_os_encryption_available->Set(OSCrypt::IsEncryptionAvailable());

  Stat<std::string>* leave_chain_details =
      section_qorai_sync.AddStringStat("Leave chain details");
  leave_chain_details->Set(qorai_sync_service->prefs().GetLeaveChainDetails());

  base::Value::List* details = about_info.FindList(kDetailsKey);
  DCHECK_NE(details, nullptr);

  details->Append(section_qorai_sync.ToValue());
  return about_info;
}

}  // namespace syncer::sync_ui_util
