/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/views/toolbar/browser_app_menu_button.h"

#include "qorai/browser/ui/toolbar/qorai_app_menu_model.h"

#define FromVectorIcon(icon, color) FromVectorIcon(icon, color, GetIconSize())
#define AppMenuModel QoraiAppMenuModel
#include <chrome/browser/ui/views/toolbar/browser_app_menu_button.cc>
#undef AppMenuModel
#undef FromVectorIcon
