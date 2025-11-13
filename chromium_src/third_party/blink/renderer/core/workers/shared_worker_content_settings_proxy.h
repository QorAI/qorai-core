/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_WORKERS_SHARED_WORKER_CONTENT_SETTINGS_PROXY_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_WORKERS_SHARED_WORKER_CONTENT_SETTINGS_PROXY_H_

#include "third_party/blink/public/platform/web_content_settings_client.h"

#define AllowStorageAccessSync                                      \
  UnusedFunction() {                                                \
    return false;                                                   \
  }                                                                 \
  qorai_shields::mojom::ShieldsSettingsPtr GetQoraiShieldsSettings( \
      ContentSettingsType webcompat_settings_type) override;        \
  bool AllowStorageAccessSync

#include <third_party/blink/renderer/core/workers/shared_worker_content_settings_proxy.h>  // IWYU pragma: export

#undef AllowStorageAccessSync

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_WORKERS_SHARED_WORKER_CONTENT_SETTINGS_PROXY_H_
