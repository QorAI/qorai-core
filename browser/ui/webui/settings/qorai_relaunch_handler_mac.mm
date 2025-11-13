/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_relaunch_handler_mac.h"

#import "qorai/browser/mac/sparkle_glue.h"
#include "qorai/browser/updater/buildflags.h"

#if BUILDFLAG(ENABLE_OMAHA4)
#include "qorai/browser/updater/features.h"
#endif

namespace qorai_relaunch_handler {

bool RelaunchOnMac() {
#if BUILDFLAG(ENABLE_OMAHA4)
  if (qorai_updater::ShouldUseOmaha4()) {
    return false;
  }
#endif
  return [SparkleGlue sharedSparkleGlue] &&
         [[SparkleGlue sharedSparkleGlue] relaunch];
}

}  // namespace qorai_relaunch_handler
