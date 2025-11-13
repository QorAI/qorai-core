/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/renderer/qorai_render_thread_observer.h"

#include <utility>

#include "base/no_destructor.h"
#include "third_party/blink/public/common/associated_interfaces/associated_interface_registry.h"

namespace {

qorai::mojom::DynamicParams* GetDynamicConfigParams() {
  static base::NoDestructor<qorai::mojom::DynamicParams> dynamic_params;
  return dynamic_params.get();
}

}  // namespace

QoraiRenderThreadObserver::QoraiRenderThreadObserver() = default;

QoraiRenderThreadObserver::~QoraiRenderThreadObserver() = default;

// static
const qorai::mojom::DynamicParams&
QoraiRenderThreadObserver::GetDynamicParams() {
  return *GetDynamicConfigParams();
}

void QoraiRenderThreadObserver::RegisterMojoInterfaces(
    blink::AssociatedInterfaceRegistry* associated_interfaces) {
  associated_interfaces->AddInterface<qorai::mojom::QoraiRendererConfiguration>(
      base::BindRepeating(
          &QoraiRenderThreadObserver::OnRendererConfigurationAssociatedRequest,
          base::Unretained(this)));
}

void QoraiRenderThreadObserver::UnregisterMojoInterfaces(
    blink::AssociatedInterfaceRegistry* associated_interfaces) {
  associated_interfaces->RemoveInterface(
      qorai::mojom::QoraiRendererConfiguration::Name_);
}

void QoraiRenderThreadObserver::OnRendererConfigurationAssociatedRequest(
    mojo::PendingAssociatedReceiver<qorai::mojom::QoraiRendererConfiguration>
        receiver) {
  renderer_configuration_receivers_.Add(this, std::move(receiver));
}

void QoraiRenderThreadObserver::SetInitialConfiguration(bool is_tor_process) {
  is_tor_process_ = is_tor_process;
}

void QoraiRenderThreadObserver::SetConfiguration(
    qorai::mojom::DynamicParamsPtr params) {
  *GetDynamicConfigParams() = std::move(*params);
}

bool QoraiRenderThreadObserver::IsOnionAllowed() const {
  return is_tor_process_ ||
         !GetDynamicConfigParams()->onion_only_in_tor_windows;
}
