/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_ENGINE_SYNC_ENGINE_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_ENGINE_SYNC_ENGINE_H_

#include "base/functional/callback_forward.h"
#include "components/sync/engine/sync_protocol_error.h"

#define DisableProtocolEventForwarding                                \
  PermanentlyDeleteAccount(                                           \
      base::OnceCallback<void(const SyncProtocolError&)> callback) {} \
  virtual void DisableProtocolEventForwarding

#include <components/sync/engine/sync_engine.h>  // IWYU pragma: export

#undef DisableProtocolEventForwarding

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_ENGINE_SYNC_ENGINE_H_
