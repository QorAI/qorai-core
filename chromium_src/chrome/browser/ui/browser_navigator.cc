/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <string_view>

#include "chrome/browser/ui/browser_navigator_params.h"
#include "content/public/common/url_constants.h"
#include "url/gurl.h"

namespace {

void UpdateQoraiScheme(NavigateParams* params) {
  if (params->url.SchemeIs(content::kQoraiUIScheme)) {
    GURL::Replacements replacements;
    replacements.SetSchemeStr(content::kChromeUIScheme);
    params->url = params->url.ReplaceComponents(replacements);
  }
}

}  // namespace

#define QORAI_ADJUST_NAVIGATE_PARAMS_FOR_URL UpdateQoraiScheme(params);
#include <chrome/browser/ui/browser_navigator.cc>
#undef QORAI_ADJUST_NAVIGATE_PARAMS_FOR_URL
