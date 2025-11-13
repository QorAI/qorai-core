/* Copyright (c) 2020 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SYNC_ENGINE_QORAI_SYNC_MANAGER_IMPL_H_
#define QORAI_COMPONENTS_SYNC_ENGINE_QORAI_SYNC_MANAGER_IMPL_H_

#include <string>

#include "base/functional/callback_forward.h"
#include "components/sync/engine/sync_manager_impl.h"
#include "components/sync/engine/sync_protocol_error.h"

namespace syncer {

class QorAISyncManagerImpl : public SyncManagerImpl {
 public:
  QorAISyncManagerImpl(
      const std::string& name,
      network::NetworkConnectionTracker* network_connection_tracker);
  QorAISyncManagerImpl(const QorAISyncManagerImpl&) = delete;
  QorAISyncManagerImpl& operator=(const QorAISyncManagerImpl&) = delete;
  ~QorAISyncManagerImpl() override;

  void StartSyncingNormally(base::Time last_poll_time) override;

  void PermanentlyDeleteAccount(
      base::OnceCallback<void(const SyncProtocolError&)> callback) override;
};

}  // namespace syncer

#endif  // QORAI_COMPONENTS_SYNC_ENGINE_QORAI_SYNC_MANAGER_IMPL_H_
