/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/third_party/blink/renderer/core/farbling/qorai_session_cache.h"
#include "third_party/blink/public/platform/web_content_settings_client.h"
#include "ui/gfx/skia_span_util.h"

#define QORAI_CANVAS_ASYNC_BLOB_CREATOR                    \
  qorai::QoraiSessionCache::From(*context_).PerturbPixels( \
      gfx::SkPixmapToWritableSpan(src_data_));

#include <third_party/blink/renderer/core/html/canvas/canvas_async_blob_creator.cc>

#undef QORAI_CANVAS_ASYNC_BLOB_CREATOR
