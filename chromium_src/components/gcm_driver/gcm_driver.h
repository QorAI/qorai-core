/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_GCM_DRIVER_GCM_DRIVER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_GCM_DRIVER_GCM_DRIVER_H_

#define GetGCMStatistics      \
  SetEnabled(bool enabled) {} \
  virtual void GetGCMStatistics

#include <components/gcm_driver/gcm_driver.h>  // IWYU pragma: export

#undef GetGCMStatistics

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_GCM_DRIVER_GCM_DRIVER_H_
