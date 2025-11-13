/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_ANDROID_YOUTUBE_SCRIPT_INJECTOR_FEATURES_H_
#define QORAI_BROWSER_ANDROID_YOUTUBE_SCRIPT_INJECTOR_FEATURES_H_

#include "base/feature_list.h"

namespace preferences {
namespace features {

BASE_DECLARE_FEATURE(kQoraiBackgroundVideoPlayback);
BASE_DECLARE_FEATURE(kQoraiPictureInPictureForYouTubeVideos);

}  // namespace features
}  // namespace preferences

#endif  // QORAI_BROWSER_ANDROID_YOUTUBE_SCRIPT_INJECTOR_FEATURES_H_
