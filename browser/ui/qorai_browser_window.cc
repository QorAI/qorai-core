/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/qorai_browser_window.h"

#include <vector>

#include "qorai/components/speedreader/common/buildflags/buildflags.h"

// Provide a base implementation (important for `TestBrowserWindow ` in tests)
// For real implementation, see `QoraiBrowserView`.

#if BUILDFLAG(ENABLE_SPEEDREADER)
speedreader::SpeedreaderBubbleView* QoraiBrowserWindow::ShowSpeedreaderBubble(
    speedreader::SpeedreaderTabHelper* tab_helper,
    speedreader::SpeedreaderBubbleLocation location) {
  return nullptr;
}
#endif

gfx::Rect QoraiBrowserWindow::GetShieldsBubbleRect() {
  return gfx::Rect();
}

// static
QoraiBrowserWindow* QoraiBrowserWindow::From(BrowserWindow* window) {
  return static_cast<QoraiBrowserWindow*>(window);
}

#if defined(TOOLKIT_VIEWS)
sidebar::Sidebar* QoraiBrowserWindow::InitSidebar() {
  return nullptr;
}

void QoraiBrowserWindow::ToggleSidebar() {}

bool QoraiBrowserWindow::HasSelectedURL() const {
  return false;
}

void QoraiBrowserWindow::CleanAndCopySelectedURL() {}

bool QoraiBrowserWindow::ShowQoraiHelpBubbleView(const std::string& text) {
  return false;
}
#endif  // defined(TOOLKIT_VIEWS)

bool QoraiBrowserWindow::IsInTabDragging() const {
  return false;
}
