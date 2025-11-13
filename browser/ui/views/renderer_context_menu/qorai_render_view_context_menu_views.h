/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_RENDERER_CONTEXT_MENU_QORAI_RENDER_VIEW_CONTEXT_MENU_VIEWS_H_
#define QORAI_BROWSER_UI_VIEWS_RENDERER_CONTEXT_MENU_QORAI_RENDER_VIEW_CONTEXT_MENU_VIEWS_H_

#include "chrome/browser/ui/views/renderer_context_menu/render_view_context_menu_views.h"

class QoraiRenderViewContextMenuViews : public RenderViewContextMenuViews {
 public:
  ~QoraiRenderViewContextMenuViews() override;
  QoraiRenderViewContextMenuViews(const QoraiRenderViewContextMenuViews&) =
      delete;
  QoraiRenderViewContextMenuViews& operator=(
      const QoraiRenderViewContextMenuViews&) = delete;

  // Factory function to create an instance.
  static RenderViewContextMenuViews* Create(
      // Non-const reference passed in the parent class upstream
      // NOLINTNEXTLINE(runtime/references)
      content::RenderFrameHost& render_frame_host,
      const content::ContextMenuParams& params);

  void Show() override;

 protected:
  // Non-const reference passed in the parent class upstream
  // NOLINTNEXTLINE(runtime/references)
  QoraiRenderViewContextMenuViews(content::RenderFrameHost& render_frame_host,
                                  const content::ContextMenuParams& params);
};

#endif  // QORAI_BROWSER_UI_VIEWS_RENDERER_CONTEXT_MENU_QORAI_RENDER_VIEW_CONTEXT_MENU_VIEWS_H_
