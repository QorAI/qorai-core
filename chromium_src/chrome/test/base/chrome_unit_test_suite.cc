/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/test/base/chrome_unit_test_suite.h"

#include "qorai/common/qorai_content_client.h"
#include "qorai/common/resource_bundle_helper.h"
#include "qorai/test/base/testing_qorai_browser_process.h"
#include "ui/base/resource/resource_bundle.h"

#define InitSharedInstanceWithLocale(...)    \
  InitSharedInstanceWithLocale(__VA_ARGS__); \
  qorai::InitializeResourceBundle();

#define ChromeContentClient QoraiContentClient
#include <chrome/test/base/chrome_unit_test_suite.cc>
#undef ChromeContentClient
#undef InitSharedInstanceWithLocale
