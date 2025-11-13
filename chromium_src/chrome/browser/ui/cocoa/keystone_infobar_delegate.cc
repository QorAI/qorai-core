/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/cocoa/keystone_infobar_delegate.h"

#include "qorai/browser/updater/buildflags.h"

#if BUILDFLAG(ENABLE_OMAHA4)
#include "qorai/browser/updater/features.h"
#define ShowUpdaterPromotionInfoBar ShowUpdaterPromotionInfoBar_ChromiumImpl
#endif

#include <chrome/browser/ui/cocoa/keystone_infobar_delegate.cc>

#if BUILDFLAG(ENABLE_OMAHA4)
#undef ShowUpdaterPromotionInfoBar
void ShowUpdaterPromotionInfoBar() {
  if (qorai_updater::ShouldUseOmaha4()) {
    ShowUpdaterPromotionInfoBar_ChromiumImpl();
  }
}
#endif
