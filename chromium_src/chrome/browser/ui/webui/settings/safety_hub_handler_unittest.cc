/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/safety_hub/safety_hub_test_util.h"
#include "components/content_settings/core/common/content_settings_types.h"

// clang-format off
#define FILE_SYSTEM_ACCESS_EXTENDED_PERMISSION      \
  FILE_SYSTEM_ACCESS_EXTENDED_PERMISSION,           \
      ContentSettingsType::QORAI_FINGERPRINTING_V2, \
      ContentSettingsType::QORAI_HTTPS_UPGRADE
// clang-format on

#define MIDI                                                         \
  QORAI_WEBCOMPAT_NONE, ContentSettingsType::QORAI_WEBCOMPAT_AUDIO,  \
      ContentSettingsType::QORAI_WEBCOMPAT_CANVAS,                   \
      ContentSettingsType::QORAI_WEBCOMPAT_DEVICE_MEMORY,            \
      ContentSettingsType::QORAI_WEBCOMPAT_EVENT_SOURCE_POOL,        \
      ContentSettingsType::QORAI_WEBCOMPAT_FONT,                     \
      ContentSettingsType::QORAI_WEBCOMPAT_HARDWARE_CONCURRENCY,     \
      ContentSettingsType::QORAI_WEBCOMPAT_KEYBOARD,                 \
      ContentSettingsType::QORAI_WEBCOMPAT_LANGUAGE,                 \
      ContentSettingsType::QORAI_WEBCOMPAT_MEDIA_DEVICES,            \
      ContentSettingsType::QORAI_WEBCOMPAT_PLUGINS,                  \
      ContentSettingsType::QORAI_WEBCOMPAT_SCREEN,                   \
      ContentSettingsType::QORAI_WEBCOMPAT_SPEECH_SYNTHESIS,         \
      ContentSettingsType::QORAI_WEBCOMPAT_USB_DEVICE_SERIAL_NUMBER, \
      ContentSettingsType::QORAI_WEBCOMPAT_USER_AGENT,               \
      ContentSettingsType::QORAI_WEBCOMPAT_WEBGL,                    \
      ContentSettingsType::QORAI_WEBCOMPAT_WEBGL2,                   \
      ContentSettingsType::QORAI_WEBCOMPAT_WEB_SOCKETS_POOL,         \
      ContentSettingsType::QORAI_WEBCOMPAT_ALL, ContentSettingsType::MIDI

#include <chrome/browser/ui/webui/settings/safety_hub_handler_unittest.cc>
#undef FILE_SYSTEM_ACCESS_EXTENDED_PERMISSION
#undef MIDI
