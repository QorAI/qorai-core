/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/check.h"
#include "qorai/components/qorai_shields/core/common/shields_settings.mojom-blink.h"
#include "mojo/public/cpp/bindings/string_traits_wtf.h"

#include <third_party/blink/renderer/core/workers/shared_worker_content_settings_proxy.cc>

namespace blink {

qorai_shields::mojom::ShieldsSettingsPtr
SharedWorkerContentSettingsProxy::GetQoraiShieldsSettings(
    ContentSettingsType webcompat_settings_type) {
  qorai_shields::mojom::blink::ShieldsSettingsPtr blink_result;
  if (!GetService()->GetQoraiShieldsSettings(&blink_result)) {
    return qorai_shields::mojom::ShieldsSettings::New();
  }

  // Convert the blink mojo struct into a non-blink mojo struct.
  CHECK(blink_result);
  qorai_shields::mojom::ShieldsSettingsPtr result;
  CHECK(qorai_shields::mojom::ShieldsSettings::DeserializeFromMessage(
      qorai_shields::mojom::blink::ShieldsSettings::WrapAsMessage(
          std::move(blink_result)),
      &result));
  return result;
}

}  // namespace blink
