/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/vector_icons/vector_icons.h"

// Replaces vector_icon::kFooIcons with ours
#define vector_icons
#define kPlayArrowIcon kQoraPlayFilledIcon
#define kPauseIcon kQoraPauseFilledIcon
#define kReplayIcon kQoraReloadIcon

#include <chrome/browser/ui/views/overlay/playback_image_button.cc>

#undef kReplayIcon
#undef kPauseIcon
#undef kPlayArrowIcon
#undef vector_icons
