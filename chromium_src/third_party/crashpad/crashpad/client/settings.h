/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_CRASHPAD_CRASHPAD_CLIENT_SETTINGS_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_CRASHPAD_CRASHPAD_CLIENT_SETTINGS_H_

#include "util/misc/uuid.h"

#define GetClientID                          \
  GetClientID_ChromiumImpl(UUID* client_id); \
  bool GetClientID

#include <third_party/crashpad/crashpad/client/settings.h>  // IWYU pragma: export

#undef GetClientID

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_CRASHPAD_CRASHPAD_CLIENT_SETTINGS_H_
