/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_H_

// Return true for any Qorai-specific starter packs that are "ask" oriented,
// rather than search oriented.
#define is_ask_starter_pack()                              \
  is_ask_starter_pack() const {                            \
    if (starter_pack_id() ==                               \
        template_url_starter_pack_data::kAskQoraiSearch) { \
      return true;                                         \
    }                                                      \
    return is_ask_starter_pack_chromium();                 \
  }                                                        \
  bool is_ask_starter_pack_chromium()

#include <components/search_engines/template_url.h>  // IWYU pragma: export

#undef is_ask_starter_pack

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_H_
