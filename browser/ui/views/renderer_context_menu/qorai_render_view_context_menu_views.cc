/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/renderer_context_menu/qorai_render_view_context_menu_views.h"

QoraiRenderViewContextMenuViews::QoraiRenderViewContextMenuViews(
    content::RenderFrameHost& render_frame_host,
    const content::ContextMenuParams& params)
    : RenderViewContextMenuViews(render_frame_host, params) {}

QoraiRenderViewContextMenuViews::~QoraiRenderViewContextMenuViews() = default;

// static
RenderViewContextMenuViews* QoraiRenderViewContextMenuViews::Create(
    content::RenderFrameHost& render_frame_host,
    const content::ContextMenuParams& params) {
  return new QoraiRenderViewContextMenuViews(render_frame_host, params);
}

void QoraiRenderViewContextMenuViews::Show() {
  // Removes duplicated separator if any. The duplicated separator may appear
  // in |QoraiRenderViewContextMenu::InitMenu| after remove the translate menu
  // item.
  RemoveAdjacentSeparators();
  RenderViewContextMenuViews::Show();
}
