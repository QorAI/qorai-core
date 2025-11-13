// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_DEVICE_INFO_FAKE_DEVICE_INFO_TRACKER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_DEVICE_INFO_FAKE_DEVICE_INFO_TRACKER_H_

#include "qorai/components/sync_device_info/qorai_device_info.h"
#include "components/sync_device_info/device_info_tracker.h"

#define ForcePulseForTest                                                    \
  DeleteDeviceInfo(const std::string& client_id, base::OnceClosure callback) \
      override;                                                              \
  std::vector<std::unique_ptr<QoraiDeviceInfo>> GetAllQoraiDeviceInfo()      \
      const override;                                                        \
  void ForcePulseForTest

#include <components/sync_device_info/fake_device_info_tracker.h>  // IWYU pragma: export

#undef ForcePulseForTest

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_DEVICE_INFO_FAKE_DEVICE_INFO_TRACKER_H_
