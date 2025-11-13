/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_GOOGLE_APIS_API_KEY_CACHE_H_
#define QORAI_CHROMIUM_SRC_GOOGLE_APIS_API_KEY_CACHE_H_

#define metrics_key                                          \
  Undefined();                                               \
  void set_api_key_for_testing(const std::string& api_key) { \
    api_key_ = api_key;                                      \
  }                                                          \
  const std::string& metrics_key

#include <google_apis/api_key_cache.h>  // IWYU pragma: export

#undef metrics_key

#endif  // QORAI_CHROMIUM_SRC_GOOGLE_APIS_API_KEY_CACHE_H_
