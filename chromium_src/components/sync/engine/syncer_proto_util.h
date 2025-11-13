/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_ENGINE_SYNCER_PROTO_UTIL_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_ENGINE_SYNCER_PROTO_UTIL_H_

#define SetProtocolVersion                                                \
  SaveServerErrorMessage(const sync_pb::ClientToServerResponse& response, \
                         StatusController* status_controller);            \
  friend class QoraiSyncServerCommands;                                   \
  static void SetProtocolVersion

#include <components/sync/engine/syncer_proto_util.h>  // IWYU pragma: export

#undef SetProtocolVersion

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_ENGINE_SYNCER_PROTO_UTIL_H_
