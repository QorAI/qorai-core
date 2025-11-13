/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_WEBAUDIO_REALTIME_ANALYSER_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_WEBAUDIO_REALTIME_ANALYSER_H_

#include <optional>
#include <utility>

#include "qorai/third_party/blink/renderer/platform/qorai_audio_farbling_helper.h"

#define analysis_frame_                                 \
  analysis_frame_;                                      \
                                                        \
 public:                                                \
  void set_audio_farbling_helper(                       \
      std::optional<QoraiAudioFarblingHelper> helper) { \
    audio_farbling_helper_ = std::move(helper);         \
  }                                                     \
                                                        \
 private:                                               \
  std::optional<QoraiAudioFarblingHelper> audio_farbling_helper_

#include <third_party/blink/renderer/modules/webaudio/realtime_analyser.h>  // IWYU pragma: export

#undef analysis_frame_

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_WEBAUDIO_REALTIME_ANALYSER_H_
