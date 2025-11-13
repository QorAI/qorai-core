/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/test/base/chrome_test_launcher.h"

#include "qorai/app/qorai_main_delegate.h"
#include "qorai/utility/qorai_content_utility_client.h"

#define ChromeContentUtilityClient QoraiContentUtilityClient
#define ChromeMainDelegate QoraiMainDelegate
#include <chrome/test/base/chrome_test_launcher.cc>
#undef ChromeMainDelegate
#undef ChromeContentUtilityClient
