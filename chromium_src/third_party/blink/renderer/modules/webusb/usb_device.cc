/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "third_party/blink/renderer/modules/webusb/usb_device.h"

#include "qorai/third_party/blink/renderer/qorai_farbling_constants.h"
#include "qorai/third_party/blink/renderer/core/farbling/qorai_session_cache.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"

#include <third_party/blink/renderer/modules/webusb/usb_device.cc>

namespace blink {

String USBDevice::serialNumber() const {
  String realSerialNumber = serialNumber_ChromiumImpl();
  if (realSerialNumber.length() > 0) {
    if (ExecutionContext* context = GetExecutionContext()) {
      if (qorai::GetQoraiFarblingLevelFor(
              context,
              ContentSettingsType::QORAI_WEBCOMPAT_USB_DEVICE_SERIAL_NUMBER,
              QoraiFarblingLevel::BALANCED) != QoraiFarblingLevel::OFF) {
        StringBuilder result;
        result.Append(realSerialNumber);
        result.Append("WEBUSB_SERIAL_NUMBER");
        return qorai::QoraiSessionCache::From(*context).GenerateRandomString(
            result.ToString().Utf8(), 16);
      }
    }
  }
  return realSerialNumber;
}

}  // namespace blink
