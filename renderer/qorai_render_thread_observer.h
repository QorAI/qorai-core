/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_RENDERER_QORAI_RENDER_THREAD_OBSERVER_H_
#define QORAI_RENDERER_QORAI_RENDER_THREAD_OBSERVER_H_

#include "qorai/common/qorai_renderer_configuration.mojom.h"
#include "content/public/renderer/render_thread_observer.h"
#include "mojo/public/cpp/bindings/associated_receiver_set.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"

namespace blink {
class AssociatedInterfaceRegistry;
}

class QoraiRenderThreadObserver
    : public content::RenderThreadObserver,
      public qorai::mojom::QoraiRendererConfiguration {
 public:
  QoraiRenderThreadObserver(const QoraiRenderThreadObserver&) = delete;
  QoraiRenderThreadObserver& operator=(const QoraiRenderThreadObserver&) =
      delete;
  QoraiRenderThreadObserver();
  ~QoraiRenderThreadObserver() override;

  bool IsOnionAllowed() const;

  // Return the dynamic parameters - those that may change while the
  // render process is running.
  static const qorai::mojom::DynamicParams& GetDynamicParams();

 private:
  // content::RenderThreadObserver:
  void RegisterMojoInterfaces(
      blink::AssociatedInterfaceRegistry* associated_interfaces) override;
  void UnregisterMojoInterfaces(
      blink::AssociatedInterfaceRegistry* associated_interfaces) override;

  // qorai::mojom::QoraiRendererConfiguration:
  void SetInitialConfiguration(bool is_tor_process) override;
  void SetConfiguration(qorai::mojom::DynamicParamsPtr params) override;

  void OnRendererConfigurationAssociatedRequest(
      mojo::PendingAssociatedReceiver<qorai::mojom::QoraiRendererConfiguration>
          receiver);

  bool is_tor_process_ = false;
  mojo::AssociatedReceiverSet<qorai::mojom::QoraiRendererConfiguration>
      renderer_configuration_receivers_;
};

#endif  // QORAI_RENDERER_QORAI_RENDER_THREAD_OBSERVER_H_
