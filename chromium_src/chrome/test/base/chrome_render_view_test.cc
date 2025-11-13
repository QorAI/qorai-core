/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_content_browser_client.h"
#include "qorai/common/qorai_content_client.h"
#include "qorai/renderer/qorai_content_renderer_client.h"

#define ChromeContentClient() QoraiContentClient()
#define ChromeContentBrowserClient() QoraiContentBrowserClient()
#define ChromeContentRendererClient() QoraiContentRendererClient()
#include <chrome/test/base/chrome_render_view_test.cc>
#undef ChromeContentClient
#undef ChromeContentBrowserClient
#undef ChromeContentRendererClient
