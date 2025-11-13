/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/compiler_specific.h"
#include "qorai/third_party/blink/renderer/core/farbling/qorai_session_cache.h"
#include "third_party/blink/renderer/modules/mediastream/media_device_info.h"

using blink::ExecutionContext;
using blink::MediaDeviceInfoVector;

namespace qorai {

void FarbleMediaDevices(ExecutionContext* context,
                        MediaDeviceInfoVector* media_devices) {
  // |media_devices| is guaranteed not to be null here.
  if (media_devices->size() <= 2)
    return;
  if (GetQoraiFarblingLevelFor(
          context, ContentSettingsType::QORAI_WEBCOMPAT_MEDIA_DEVICES,
          QoraiFarblingLevel::OFF) == QoraiFarblingLevel::OFF) {
    return;
  }
  // Shuffle the list of devices pseudo-randomly, based on the
  // domain+session key, starting with the second device.
  FarblingPRNG prng =
      QoraiSessionCache::From(*context).MakePseudoRandomGenerator();
  MediaDeviceInfoVector::iterator it_begin = media_devices->begin();
  UNSAFE_TODO(std::shuffle(++it_begin, media_devices->end(), prng));
}

}  // namespace qorai

#define QORAI_MEDIA_DEVICES_DEVICES_ENUMERATED                        \
  if (ExecutionContext* context =                                     \
          ExecutionContext::From(result_tracker->GetScriptState())) { \
    qorai::FarbleMediaDevices(context, &media_devices);               \
  }

#include <third_party/blink/renderer/modules/mediastream/media_devices.cc>
#undef QORAI_MEDIA_DEVICES_DEVICES_ENUMERATED
