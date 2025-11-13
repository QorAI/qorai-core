/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#define REGISTER_QORAI_SCHEMES_DISPLAY_ISOLATED_AND_NO_JS              \
  WebString qorai_scheme(WebString::FromASCII(kQoraiUIScheme));        \
  WebSecurityPolicy::RegisterURLSchemeAsDisplayIsolated(qorai_scheme); \
  WebSecurityPolicy::RegisterURLSchemeAsNotAllowingJavascriptURLs(qorai_scheme);

#include <content/renderer/render_thread_impl.cc>
#undef REGISTER_QORAI_SCHEMES_DISPLAY_ISOLATED_AND_NO_JS
