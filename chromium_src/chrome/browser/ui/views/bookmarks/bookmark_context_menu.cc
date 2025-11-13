/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/views/bookmarks/bookmark_context_menu.h"

#include "qorai/browser/ui/toolbar/qorai_bookmark_context_menu_controller.h"

#define BookmarkContextMenuController QoraiBookmarkContextMenuController
#include <chrome/browser/ui/views/bookmarks/bookmark_context_menu.cc>
#undef BookmarkContextMenuController
