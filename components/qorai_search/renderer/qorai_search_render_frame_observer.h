// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_RENDER_FRAME_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_RENDER_FRAME_OBSERVER_H_

#include <memory>
#include <optional>

#include "qorai/components/qorai_search/renderer/qorai_search_default_js_handler.h"
#include "content/public/renderer/render_frame.h"
#include "content/public/renderer/render_frame_observer.h"
#include "third_party/blink/public/web/web_navigation_type.h"
#include "url/gurl.h"
#include "v8/include/v8.h"

namespace qorai_search {

class QoraiSearchRenderFrameObserver : public content::RenderFrameObserver {
 public:
  explicit QoraiSearchRenderFrameObserver(content::RenderFrame* render_frame,
                                          int32_t world_id);
  QoraiSearchRenderFrameObserver(const QoraiSearchRenderFrameObserver&) =
      delete;
  QoraiSearchRenderFrameObserver& operator=(
      const QoraiSearchRenderFrameObserver&) = delete;
  ~QoraiSearchRenderFrameObserver() override;

  // RenderFrameObserver implementation.
  void DidCreateScriptContext(v8::Local<v8::Context> context,
                              int32_t world_id) override;
  void DidStartNavigation(
      const GURL& url,
      std::optional<blink::WebNavigationType> navigation_type) override;

 private:
  // RenderFrameObserver implementation.
  void OnDestruct() override;

  // Handle to "handler" JavaScript object functionality.
  std::unique_ptr<QoraiSearchDefaultJSHandler> native_javascript_handle_;
  int32_t world_id_;
  GURL url_;
};

}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_RENDER_FRAME_OBSERVER_H_
