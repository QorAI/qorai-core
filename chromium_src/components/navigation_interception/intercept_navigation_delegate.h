/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_NAVIGATION_INTERCEPTION_INTERCEPT_NAVIGATION_DELEGATE_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_NAVIGATION_INTERCEPTION_INTERCEPT_NAVIGATION_DELEGATE_H_

#define ShouldIgnoreNavigation virtual ShouldIgnoreNavigation
#include <components/navigation_interception/intercept_navigation_delegate.h>  // IWYU pragma: export
#undef ShouldIgnoreNavigation

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_NAVIGATION_INTERCEPTION_INTERCEPT_NAVIGATION_DELEGATE_H_
