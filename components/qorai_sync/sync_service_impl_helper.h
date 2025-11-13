/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SYNC_SYNC_SERVICE_IMPL_HELPER_H_
#define QORAI_COMPONENTS_QORAI_SYNC_SYNC_SERVICE_IMPL_HELPER_H_

#include <string>

#include "base/functional/callback.h"

namespace syncer {
class QoraiSyncServiceImpl;
class DeviceInfoSyncService;
}  // namespace syncer

namespace qorai_sync {

// Helper function to break circular dependency between
// //components/sync/service and //component/sync_device_info
void ResetSync(syncer::QoraiSyncServiceImpl* sync_service_impl,
               syncer::DeviceInfoSyncService* device_info_service,
               base::OnceClosure on_reset_done);

void DeleteDevice(syncer::QoraiSyncServiceImpl* sync_service_impl,
                  syncer::DeviceInfoSyncService* device_info_service,
                  const std::string& device_guid);

}  // namespace qorai_sync

#endif  // QORAI_COMPONENTS_QORAI_SYNC_SYNC_SERVICE_IMPL_HELPER_H_
