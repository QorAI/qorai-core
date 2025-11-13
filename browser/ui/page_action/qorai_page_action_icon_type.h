/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_PAGE_ACTION_QORAI_PAGE_ACTION_ICON_TYPE_H_
#define QORAI_BROWSER_UI_PAGE_ACTION_QORAI_PAGE_ACTION_ICON_TYPE_H_

#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "chrome/browser/ui/page_action/page_action_icon_type.h"

namespace qorai {

#define DECLARE_QORAI_PAGE_ACTION_ICON_TYPE(NAME, VALUE) \
  constexpr PageActionIconType NAME = static_cast<PageActionIconType>(VALUE)

// Use negative values so that our values doesn't conflict with upstream values.
DECLARE_QORAI_PAGE_ACTION_ICON_TYPE(kUndefinedPageActionIconType, -1);
DECLARE_QORAI_PAGE_ACTION_ICON_TYPE(kPlaylistPageActionIconType, -2);
// -3 was used for Qorai Player
#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
DECLARE_QORAI_PAGE_ACTION_ICON_TYPE(kWaybackMachineActionIconType, -4);
#endif
#if BUILDFLAG(ENABLE_SPEEDREADER)
DECLARE_QORAI_PAGE_ACTION_ICON_TYPE(kSpeedreaderPageActionIconType, -5);
#endif

#undef DECLARE_QORAI_PAGE_ACTION_ICON_TYPE

}  // namespace qorai

#endif  // QORAI_BROWSER_UI_PAGE_ACTION_QORAI_PAGE_ACTION_ICON_TYPE_H_
