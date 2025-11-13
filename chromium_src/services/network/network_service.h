/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_SERVICES_NETWORK_NETWORK_SERVICE_H_
#define QORAI_CHROMIUM_SRC_SERVICES_NETWORK_NETWORK_SERVICE_H_

#include "services/network/public/mojom/network_service.mojom.h"

#define DisableQuic                                                         \
  GetDnsRequestCountsAndReset(GetDnsRequestCountsAndResetCallback callback) \
      override;                                                             \
  void DisableQuic
#define UpdateKeyPinsList                              \
  UpdateKeyPinsList_Unused(mojom::PinListPtr pin_list, \
                           base::Time update_time);    \
  void UpdateKeyPinsList

#include <services/network/network_service.h>  // IWYU pragma: export

#undef UpdateKeyPinsList
#undef DisableQuic

#endif  // QORAI_CHROMIUM_SRC_SERVICES_NETWORK_NETWORK_SERVICE_H_
