/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "ios/chrome/browser/web/model/chrome_main_parts.h"
#include "qorai/ios/browser/application_context/qorai_application_context_impl.h"

#define PreCreateMainMessageLoop PreCreateMainMessageLoop_ChromiumImpl
#define ApplicationContextImpl QoraiApplicationContextImpl
#include <ios/chrome/browser/web/model/chrome_main_parts.mm>
#undef ApplicationContextImpl
#undef PreCreateMainMessageLoop

void IOSChromeMainParts::PreCreateMainMessageLoop() {
  IOSChromeMainParts::PreCreateMainMessageLoop_ChromiumImpl();
}
