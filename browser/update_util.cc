/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/update_util.h"

#include "base/command_line.h"
#include "qorai/components/constants/qorai_switches.h"
#include "content/public/common/content_switches.h"

namespace qorai {

bool UpdateEnabled() {
#if defined(OFFICIAL_BUILD)
  const base::CommandLine* cmdline = base::CommandLine::ForCurrentProcess();
  return !cmdline->HasSwitch(switches::kDisableQoraiUpdate) &&
         // Don't check for updates in browser tests.
         !cmdline->HasSwitch(switches::kTestType);
#else
  return false;
#endif
}

}  // namespace qorai
