/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/frame/qorai_browser_view.h"
#include "qorai/browser/ui/views/frame/qorai_browser_widget.h"
#include "chrome/browser/ui/views/frame/browser_view.h"

#define BrowserWidget QoraiBrowserWidget
#define BrowserView QoraiBrowserView
#include <chrome/browser/ui/views/frame/browser_window_factory.cc>
#undef BrowserView
#undef BrowserWidget
