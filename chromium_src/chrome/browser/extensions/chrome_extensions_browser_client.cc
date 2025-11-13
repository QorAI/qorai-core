/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/extensions/chrome_extensions_browser_client.h"

#include "qorai/browser/extensions/api/qorai_extensions_api_client.h"
#include "qorai/browser/extensions/updater/qorai_update_client_config.h"
#include "chrome/browser/extensions/api/chrome_extensions_api_client.h"
#include "chrome/browser/extensions/updater/chrome_update_client_config.h"

#define ChromeExtensionsAPIClient QoraiExtensionsAPIClient
#define ChromeUpdateClientConfig QoraiUpdateClientConfig
#include <chrome/browser/extensions/chrome_extensions_browser_client.cc>
#undef ChromeUpdateClientConfig
#undef ChromeExtensionsAPIClient
