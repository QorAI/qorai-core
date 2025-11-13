/* Copyright (c) 2018 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

namespace blink {
class LocalFrame;

namespace {
class MediaKeySystemAccessInitializer;

void MaybeOnWidevineRequest(MediaKeySystemAccessInitializer* initializer,
                            LocalFrame* frame);
}  // namespace
}  // namespace blink

// Notify Qorai about the widevine availability request.
#define QORAI_NAVIGATOR_REQUEST_MEDIA_KEY_SYSTEM_ACCESS \
  MaybeOnWidevineRequest(initializer, window->GetFrame());

#include "base/check.h"

#include <third_party/blink/renderer/modules/encryptedmedia/navigator_request_media_key_system_access.cc>
#undef QORAI_NAVIGATOR_REQUEST_MEDIA_KEY_SYSTEM_ACCESS

#include "qorai/components/qorai_drm/qorai_drm.mojom-blink.h"
#include "mojo/public/cpp/bindings/associated_remote.h"
#include "third_party/blink/public/common/associated_interfaces/associated_interface_provider.h"
#include "third_party/blink/renderer/core/frame/local_frame_client.h"
#include "third_party/blink/renderer/core/frame/web_local_frame_impl.h"

namespace blink {
namespace {

// Notifies Qorai about the widevine availability request.
void MaybeOnWidevineRequest(MediaKeySystemAccessInitializer* initializer,
                            LocalFrame* frame) {
  if (initializer->KeySystem() == "com.widevine.alpha") {
    if (frame->Client()->GetRemoteNavigationAssociatedInterfaces()) {
      mojo::AssociatedRemote<qorai_drm::mojom::blink::QoraiDRM>
          qorai_drm_binding;
      frame->Client()->GetRemoteNavigationAssociatedInterfaces()->GetInterface(
          &qorai_drm_binding);
      DCHECK(qorai_drm_binding.is_bound());
      qorai_drm_binding->OnWidevineKeySystemAccessRequest();
    }
  }
}

}  // namespace
}  // namespace blink
