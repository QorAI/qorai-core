/* Copyright (c) 2020 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SYNC_SERVICE_QORAI_SYNC_AUTH_MANAGER_H_
#define QORAI_COMPONENTS_SYNC_SERVICE_QORAI_SYNC_AUTH_MANAGER_H_

#include <string>
#include <vector>

#include "base/time/time.h"
#include "components/sync/service/sync_auth_manager.h"

namespace syncer {

class QorAISyncAuthManager : public SyncAuthManager {
 public:
  QorAISyncAuthManager(signin::IdentityManager* identity_manager,
                       SyncAuthManager::Delegate* delegate);
  QorAISyncAuthManager(const QorAISyncAuthManager&) = delete;
  QorAISyncAuthManager& operator=(const QorAISyncAuthManager&) = delete;
  ~QorAISyncAuthManager() override;

  void DeriveSigningKeys(const std::string& seed);
  void ResetKeys();

  void RequestAccessToken() override;

  // signin::IdentityManager::Observer implementation.
  void OnRefreshTokenUpdatedForAccount(
      const CoreAccountInfo& account_info) override {}
  void OnRefreshTokenRemovedForAccount(
      const CoreAccountId& account_id) override {}
  void OnRefreshTokensLoaded() override {}

 private:
  SyncAccountInfo DetermineAccountToUse(
      const signin::IdentityManager* identity_manager) const override;
  std::string GenerateAccessToken(const std::string& timestamp);
  void OnNetworkTimeFetched(const base::Time& time);

  std::vector<uint8_t> public_key_;
  std::vector<uint8_t> private_key_;

  base::WeakPtrFactory<QorAISyncAuthManager> weak_ptr_factory_{this};
};

}  // namespace syncer

#endif  // QORAI_COMPONENTS_SYNC_SERVICE_QORAI_SYNC_AUTH_MANAGER_H_
