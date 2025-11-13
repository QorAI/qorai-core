/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SYNC_ENGINE_QORAI_SYNC_SERVER_COMMANDS_H_
#define QORAI_COMPONENTS_SYNC_ENGINE_QORAI_SYNC_SERVER_COMMANDS_H_

#include "base/functional/callback_forward.h"
#include "components/sync/engine/sync_protocol_error.h"

namespace syncer {

class SyncCycle;
struct SyncProtocolError;

class QorAISyncServerCommands {
 public:
  QorAISyncServerCommands(const QorAISyncServerCommands&) = delete;
  QorAISyncServerCommands& operator=(const QorAISyncServerCommands&) = delete;

  static void PermanentlyDeleteAccount(
      SyncCycle* cycle,
      base::OnceCallback<void(const SyncProtocolError&)> callback);

 private:
  QorAISyncServerCommands() = default;
};

}  // namespace syncer

#endif  // QORAI_COMPONENTS_SYNC_ENGINE_QORAI_SYNC_SERVER_COMMANDS_H_
