/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_INSTALL_STATIC_INSTALL_UTIL_H_
#define QORAI_CHROMIUM_SRC_CHROME_INSTALL_STATIC_INSTALL_UTIL_H_

#define GetChromeChannel           \
  GetChromeChannel_ChromiumImpl(); \
  version_info::Channel GetChromeChannel

#include <chrome/install_static/install_util.h>  // IWYU pragma: export
#undef GetChromeChannel

#endif  // QORAI_CHROMIUM_SRC_CHROME_INSTALL_STATIC_INSTALL_UTIL_H_
