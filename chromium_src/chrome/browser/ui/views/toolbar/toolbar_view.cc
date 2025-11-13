/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/profiles/qorai_avatar_toolbar_button.h"
#include "qorai/browser/ui/views/toolbar/qorai_browser_app_menu_button.h"
#include "extensions/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "qorai/browser/ui/views/location_bar/qorai_location_bar_view.h"
#include "chrome/browser/ui/views/location_bar/location_bar_view.h"

#define LocationBarView QoraiLocationBarView
#endif

#define BrowserAppMenuButton QoraiBrowserAppMenuButton
#define QORAI_TOOLBAR_VIEW_INIT                                   \
  avatar_ = container_view_->AddChildView(                        \
      std::make_unique<QoraiAvatarToolbarButton>(browser_view_)); \
  if (false)

#include <chrome/browser/ui/views/toolbar/toolbar_view.cc>
#undef QORAI_TOOLBAR_VIEW_INIT
#undef BrowserAppMenuButton
#if BUILDFLAG(ENABLE_EXTENSIONS)
#undef LocationBarView
#endif
