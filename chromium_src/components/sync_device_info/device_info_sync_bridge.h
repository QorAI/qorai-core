// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_DEVICE_INFO_DEVICE_INFO_SYNC_BRIDGE_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_DEVICE_INFO_DEVICE_INFO_SYNC_BRIDGE_H_

#include "qorai/components/sync_device_info/qorai_device_info.h"
#include "components/sync_device_info/device_info_tracker.h"

#define ForcePulseForTest                                                    \
  DeleteDeviceInfo(const std::string& client_id, base::OnceClosure callback) \
      override;                                                              \
  std::vector<std::unique_ptr<QoraiDeviceInfo>> GetAllQoraiDeviceInfo()      \
      const override;                                                        \
  void ForcePulseForTest

#define RefreshLocalDeviceInfoIfNeeded           \
  RefreshLocalDeviceInfoIfNeeded_ChromiumImpl(); \
  void RefreshLocalDeviceInfoIfNeeded

// private:
#define StoreSpecifics                                                 \
  OnDeviceInfoDeleted(const std::string& client_id, const int attempt, \
                      base::OnceClosure callback);                     \
  void StoreSpecifics

#include <components/sync_device_info/device_info_sync_bridge.h>  // IWYU pragma: export

#undef RefreshLocalDeviceInfoIfNeeded
#undef ForcePulseForTest
#undef StoreSpecifics
#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_DEVICE_INFO_DEVICE_INFO_SYNC_BRIDGE_H_
