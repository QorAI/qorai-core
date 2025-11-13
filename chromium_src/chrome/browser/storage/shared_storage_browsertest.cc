/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_content_browser_client.h"

#define ChromeContentBrowserClient QoraiContentBrowserClient
#include <chrome/browser/storage/shared_storage_browsertest.cc>
#undef ChromeContentBrowserClient
