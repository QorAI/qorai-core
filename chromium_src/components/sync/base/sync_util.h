/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_BASE_SYNC_UTIL_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_BASE_SYNC_UTIL_H_

#include "qorai/components/qorai_sync/buildflags.h"

namespace syncer::internal {
inline constexpr char kSyncServerUrl[] = BUILDFLAG(QORAI_SYNC_ENDPOINT);
inline constexpr char kSyncDevServerUrl[] = BUILDFLAG(QORAI_SYNC_ENDPOINT);
}  // namespace syncer::internal

#define kSyncServerUrl kSyncServerUrl_ChromiumImpl
#define kSyncDevServerUrl kSyncDevServerUrl_ChromiumImpl

#include <components/sync/base/sync_util.h>  // IWYU pragma: export

#undef kSyncDevServerUrl
#undef kSyncServerUrl

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_BASE_SYNC_UTIL_H_
