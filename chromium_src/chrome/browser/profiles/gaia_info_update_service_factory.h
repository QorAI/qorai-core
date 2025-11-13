/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_GAIA_INFO_UPDATE_SERVICE_FACTORY_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_GAIA_INFO_UPDATE_SERVICE_FACTORY_H_

// Include to prevent redefining BuildServiceInstanceForBrowserContext
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

#define BuildServiceInstanceForBrowserContext         \
  BuildServiceInstanceForBrowserContext_ChromiumImpl( \
      content::BrowserContext* context) const;        \
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext

#include <chrome/browser/profiles/gaia_info_update_service_factory.h>  // IWYU pragma: export
#undef BuildServiceInstanceForBrowserContext

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_GAIA_INFO_UPDATE_SERVICE_FACTORY_H_
