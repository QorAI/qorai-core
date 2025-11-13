/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_PLATFORM_LOADER_FETCH_RESOURCE_FETCHER_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_PLATFORM_LOADER_FETCH_RESOURCE_FETCHER_H_

#define HandleLoaderError                   \
  Unused();                                 \
  String GetContextCacheIdentifier() const; \
  void HandleLoaderError

#include <third_party/blink/renderer/platform/loader/fetch/resource_fetcher.h>  // IWYU pragma: export

#undef HandleLoaderError

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_PLATFORM_LOADER_FETCH_RESOURCE_FETCHER_H_
