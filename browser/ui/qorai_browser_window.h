/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_BROWSER_WINDOW_H_
#define QORAI_BROWSER_UI_QORAI_BROWSER_WINDOW_H_

#include <string>

#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/playlist/core/common/buildflags/buildflags.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "chrome/browser/ui/browser_window.h"

namespace content {
class WebContents;
}  // namespace content

#if defined(TOOLKIT_VIEWS)
namespace sidebar {
class Sidebar;
}  // namespace sidebar
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
namespace speedreader {
class SpeedreaderBubbleView;
class SpeedreaderTabHelper;
enum class SpeedreaderBubbleLocation : int;
}  // namespace speedreader
#endif

class QoraiBrowserWindow : public BrowserWindow {
 public:
  ~QoraiBrowserWindow() override {}

  static QoraiBrowserWindow* From(BrowserWindow*);

  virtual void StartTabCycling() {}

  // Returns the rectangle info of the Shield's panel.
  // Renderers will call this to check if the bottom of the panel exceeds
  // the overall screen's height
  virtual gfx::Rect GetShieldsBubbleRect();

#if BUILDFLAG(ENABLE_SPEEDREADER)
  virtual speedreader::SpeedreaderBubbleView* ShowSpeedreaderBubble(
      speedreader::SpeedreaderTabHelper* tab_helper,
      speedreader::SpeedreaderBubbleLocation location);
  virtual void UpdateReaderModeToolbar() {}
#endif

#if defined(TOOLKIT_VIEWS)
  virtual sidebar::Sidebar* InitSidebar();
  virtual void ToggleSidebar();
  virtual bool HasSelectedURL() const;
  virtual void CleanAndCopySelectedURL();

  // Returns true when bubble is shown.
  virtual bool ShowQoraiHelpBubbleView(const std::string& text);
#endif

#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
  virtual void ShowPlaylistBubble() {}
#endif

#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
  virtual void ShowWaybackMachineBubble() {}
#endif

  // Returns true if all tabs in this window is being dragged.
  virtual bool IsInTabDragging() const;
  virtual void ReadyToListenFullscreenChanges() {}
};

#endif  // QORAI_BROWSER_UI_QORAI_BROWSER_WINDOW_H_
