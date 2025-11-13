/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_HTML_HTML_SCRIPT_ELEMENT_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_HTML_HTML_SCRIPT_ELEMENT_H_

#define supports                              \
  supports_ChromiumImpl(const AtomicString&); \
  static bool supports

#include <third_party/blink/renderer/core/html/html_script_element.h>  // IWYU pragma: export
#undef supports

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_HTML_HTML_SCRIPT_ELEMENT_H_
