/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_WEBUSB_USB_DEVICE_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_WEBUSB_USB_DEVICE_H_

#define serialNumber    \
  serialNumber() const; \
  String serialNumber_ChromiumImpl

#include <third_party/blink/renderer/modules/webusb/usb_device.h>  // IWYU pragma: export

#undef serialNumber

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_WEBUSB_USB_DEVICE_H_
