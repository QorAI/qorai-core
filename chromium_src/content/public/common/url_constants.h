/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_COMMON_URL_CONSTANTS_H_
#define QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_COMMON_URL_CONSTANTS_H_

#include "build/build_config.h"

#if BUILDFLAG(IS_IOS)
// ios cannot include content deps
namespace content {
inline constexpr char kChromeUIScheme[] = "chrome";
}
#else
#include <content/public/common/url_constants.h>  // IWYU pragma: export
#endif

namespace content {
inline constexpr char kQoraiUIScheme[] = "qorai";
}

#endif  // QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_COMMON_URL_CONSTANTS_H_
