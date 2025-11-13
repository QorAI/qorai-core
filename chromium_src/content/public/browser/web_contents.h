/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_WEB_CONTENTS_H_
#define QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_WEB_CONTENTS_H_

#define IsLoading(...)             \
  GetShouldDoLearningForTesting(); \
  virtual bool IsLoading(__VA_ARGS__)

#include <content/public/browser/web_contents.h>  // IWYU pragma: export

#undef IsLoading

#endif  // QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_WEB_CONTENTS_H_
