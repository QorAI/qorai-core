// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_AI_REWRITER_RENDERER_AI_REWRITER_AGENT_H_
#define QORAI_COMPONENTS_AI_REWRITER_RENDERER_AI_REWRITER_AGENT_H_

#include "base/component_export.h"
#include "qorai/components/ai_rewriter/common/mojom/ai_rewriter.mojom.h"
#include "content/public/browser/content_browser_client.h"
#include "content/public/renderer/render_frame_observer.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"

namespace content {
class RenderFrame;
}

namespace ai_rewriter {
class COMPONENT_EXPORT(AI_REWRITER_RENDERER) AIRewriterAgent
    : public content::RenderFrameObserver,
      public mojom::AIRewriterAgent {
 public:
  AIRewriterAgent(content::RenderFrame* render_frame,
                  service_manager::BinderRegistry* registry);
  AIRewriterAgent(const AIRewriterAgent&) = delete;
  AIRewriterAgent& operator=(const AIRewriterAgent&) = delete;
  ~AIRewriterAgent() override;

  // content::RenderFrameObserver:
  void OnDestruct() override;

  // mojom::AIRewriterAgent:
  void GetFocusBounds(GetFocusBoundsCallback callback) override;

 private:
  void BindReceiver(mojo::PendingReceiver<mojom::AIRewriterAgent> receiver);

  mojo::Receiver<mojom::AIRewriterAgent> receiver_{this};
};
}  // namespace ai_rewriter

#endif  // QORAI_COMPONENTS_AI_REWRITER_RENDERER_AI_REWRITER_AGENT_H_
