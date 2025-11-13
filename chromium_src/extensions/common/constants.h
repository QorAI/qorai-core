/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_EXTENSIONS_COMMON_CONSTANTS_H_
#define QORAI_CHROMIUM_SRC_EXTENSIONS_COMMON_CONSTANTS_H_

#include "build/build_config.h"

#if BUILDFLAG(IS_IOS) || BUILDFLAG(IS_ANDROID)
// ios and android cannot include extensions deps
namespace extensions {
inline constexpr char kExtensionScheme[] = "chrome-extension";
}
#else
#include <extensions/common/constants.h>  // IWYU pragma: export

inline constexpr int kQoraiActionLeftMarginExtra = -2;

inline constexpr char qorai_extension_id[] = "mnojpmjdmbbfmejpflffifhffcmidifd";
inline constexpr char crl_set_extension_id[] =
    "hfnkpimlhhgieaddgfemjhofmfblmnib";

inline constexpr char google_translate_extension_id[] =
    "aapbdbdomjkkjkaonfhkkikfgjllcleb";
#endif

#endif  // QORAI_CHROMIUM_SRC_EXTENSIONS_COMMON_CONSTANTS_H_
