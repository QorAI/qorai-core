/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/third_party/blink/renderer/core/farbling/qorai_session_cache.h"
#include "third_party/blink/renderer/bindings/core/v8/binding_security.h"

#define BindingSecurity             \
  qorai::QoraiSessionCache::Init(); \
  BindingSecurity

#include <third_party/blink/renderer/core/core_initializer.cc>
#undef BindingSecurity
