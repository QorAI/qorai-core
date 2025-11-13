/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// Temporary fix for https://github.com/qorai/qorai-browser/issues/35938
#define QORAI_ACCESSIBILITY_PARENT  \
  if (self == _accessibilityParent) \
    return [super accessibilityParent];
#include <content/app_shim_remote_cocoa/render_widget_host_view_cocoa.mm>
#undef QORAI_ACCESSIBILITY_PARENT
