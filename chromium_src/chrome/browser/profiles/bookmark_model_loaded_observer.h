/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_BOOKMARK_MODEL_LOADED_OBSERVER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_BOOKMARK_MODEL_LOADED_OBSERVER_H_

#define QORAI_BOOKMARK_MODEL_LOADED_OBSERVER_H_  \
 private:                                        \
  friend class QoraiBookmarkModelLoadedObserver; \
                                                 \
 public:
#include <chrome/browser/profiles/bookmark_model_loaded_observer.h>  // IWYU pragma: export
#undef QORAI_BOOKMARK_MODEL_LOADED_OBSERVER_H_

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_BOOKMARK_MODEL_LOADED_OBSERVER_H_
