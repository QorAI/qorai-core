// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_RENDERER_QORAI_RENDER_FRAME_OBSERVER_H_
#define QORAI_RENDERER_QORAI_RENDER_FRAME_OBSERVER_H_

#include <string>

#include "content/public/renderer/render_frame_observer.h"
#include "services/service_manager/public/cpp/binder_registry.h"

class QoraiRenderFrameObserver : public content::RenderFrameObserver {
 public:
  explicit QoraiRenderFrameObserver(content::RenderFrame* render_frame);
  QoraiRenderFrameObserver(const QoraiRenderFrameObserver&) = delete;
  QoraiRenderFrameObserver& operator=(const QoraiRenderFrameObserver&) = delete;

  service_manager::BinderRegistry* registry() { return &registry_; }

  // content::RenderFrameObserver:
  void OnDestruct() override;
  void OnInterfaceRequestForFrame(
      const std::string& interface_name,
      mojo::ScopedMessagePipeHandle* interface_pipe) override;

 protected:
  ~QoraiRenderFrameObserver() override;

 private:
  service_manager::BinderRegistry registry_;
};

#endif  // QORAI_RENDERER_QORAI_RENDER_FRAME_OBSERVER_H_
