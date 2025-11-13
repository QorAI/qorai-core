/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CONTENT_BROWSER_WORKER_HOST_SHARED_WORKER_HOST_H_
#define QORAI_CHROMIUM_SRC_CONTENT_BROWSER_WORKER_HOST_SHARED_WORKER_HOST_H_

#include "qorai/components/qorai_shields/core/common/shields_settings.mojom.h"

#define CreateNetworkFactoryParamsForSubresources                        \
  UnusedFunction();                                                      \
  void GetQoraiShieldsSettings(                                          \
      const GURL& url,                                                   \
      base::OnceCallback<void(qorai_shields::mojom::ShieldsSettingsPtr)> \
          callback);                                                     \
  network::mojom::URLLoaderFactoryParamsPtr                              \
      CreateNetworkFactoryParamsForSubresources

#include <content/browser/worker_host/shared_worker_host.h>  // IWYU pragma: export

#undef CreateNetworkFactoryParamsForSubresources

#endif  // QORAI_CHROMIUM_SRC_CONTENT_BROWSER_WORKER_HOST_SHARED_WORKER_HOST_H_
