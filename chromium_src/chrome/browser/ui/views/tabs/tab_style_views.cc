/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/views/tabs/tab_style_views.h"
#include "qorai/browser/ui/color/qorai_color_id.h"
#include "qorai/browser/ui/tabs/qorai_tab_layout_constants.h"
#include "qorai/browser/ui/tabs/features.h"
#include "qorai/browser/ui/views/tabs/qorai_tab_group_header.h"
#include "qorai/browser/ui/views/tabs/vertical_tab_utils.h"
#include "chrome/browser/ui/views/tabs/tab_slot_controller.h"

#define QORAI_GM2_TAB_STYLE_H \
 protected:                   \
  virtual
#define CreateForTab CreateForTab_ChromiumImpl
#include <chrome/browser/ui/views/tabs/tab_style_views.cc>
#undef CreateForTab
#undef QORAI_GM2_TAB_STYLE_H

#include "qorai/browser/ui/views/tabs/qorai_tab_style_views.inc.cc"
