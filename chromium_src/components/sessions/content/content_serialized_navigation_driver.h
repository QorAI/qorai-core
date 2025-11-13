/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SESSIONS_CONTENT_CONTENT_SERIALIZED_NAVIGATION_DRIVER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SESSIONS_CONTENT_CONTENT_SERIALIZED_NAVIGATION_DRIVER_H_

#include <string>

#include "components/sessions/core/serialized_navigation_driver.h"
#include "components/sessions/core/serialized_navigation_entry.h"

#define GetSanitizedPageStateForPickle                    \
  GetSanitizedPageStateForPickle_ChromiumImpl(            \
      const SerializedNavigationEntry* navigation) const; \
  std::string GetSanitizedPageStateForPickle
#include <components/sessions/content/content_serialized_navigation_driver.h>  // IWYU pragma: export
#undef GetSanitizedPageStateForPickle

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SESSIONS_CONTENT_CONTENT_SERIALIZED_NAVIGATION_DRIVER_H_
