/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/functional/callback.h"
#include "qorai/third_party/blink/renderer/qorai_farbling_constants.h"
#include "qorai/third_party/blink/renderer/core/farbling/qorai_session_cache.h"
#include "third_party/blink/public/platform/web_content_settings_client.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/workers/worker_global_scope.h"
#include "third_party/blink/renderer/modules/webaudio/analyser_node.h"

#define QORAI_AUDIOBUFFER_GETCHANNELDATA                                      \
  {                                                                           \
    NotShared<DOMFloat32Array> destination = getChannelData(channel_index);   \
    base::span<float> dst = destination->AsSpan();                            \
    if (!dst.empty()) {                                                       \
      if (ExecutionContext* context = ExecutionContext::From(script_state)) { \
        qorai::QoraiSessionCache::From(*context).FarbleAudioChannel(dst);     \
      }                                                                       \
    }                                                                         \
  }

#define QORAI_AUDIOBUFFER_COPYFROMCHANNEL                                 \
  if (ExecutionContext* context = ExecutionContext::From(script_state)) { \
    qorai::QoraiSessionCache::From(*context).FarbleAudioChannel(          \
        dst.first(count));                                                \
  }

#include <third_party/blink/renderer/modules/webaudio/audio_buffer.cc>

#undef QORAI_AUDIOBUFFER_GETCHANNELDATA
#undef QORAI_AUDIOBUFFER_COPYFROMCHANNEL
