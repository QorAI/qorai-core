/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/overlay/qorai_back_to_tab_label_button.h"
#include "qorai/browser/ui/views/overlay/qorai_video_overlay_window_views.h"

#define QORAI_UPDATE_MAX_SIZE max_size_ = work_area.size();
#define BackToTabLabelButton QoraiBackToTabLabelButton

#include <chrome/browser/ui/views/overlay/video_overlay_window_views.cc>

#undef BackToTabLabelButton
#undef QORAI_UPDATE_MAX_SIZE
