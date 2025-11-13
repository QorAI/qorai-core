/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/mac/keystone_glue.h"

#define QORAI_CHROME_BROWSER_MAIN_PARTS_MAC_PRE_CREATE_MAIN_MESSAGE_LOOP \
  [[KeystoneGlue defaultKeystoneGlue] registerWithKeystone];

#include <chrome/browser/chrome_browser_main_mac.mm>
#undef QORAI_CHROME_BROWSER_MAIN_PARTS_MAC_PRE_CREATE_MAIN_MESSAGE_LOOP
