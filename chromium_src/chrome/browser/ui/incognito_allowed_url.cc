// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "chrome/browser/ui/incognito_allowed_url.h"

#include <string>
#include <string_view>

#include "qorai/components/constants/webui_url_constants.h"
#include "chrome/common/webui_url_constants.h"
#include "content/public/common/url_constants.h"
#include "url/gurl.h"

namespace {

bool IsURLAllowedInIncognitoQoraiImpl(const GURL& url) {
  std::string scheme = url.scheme();
  std::string_view host = url.host_piece();
  if (scheme != content::kChromeUIScheme) {
    return true;
  }

  if (host == kRewardsPageHost || host == chrome::kChromeUISyncInternalsHost ||
      host == chrome::kQoraiUISyncHost || host == kAdblockHost ||
      host == kWelcomeHost || host == kQoraiGettingStartedHost) {
    return false;
  }

  return true;
}

}  // namespace

#define QORAI_IS_URL_ALLOWED_IN_INCOGNITO     \
  if (!IsURLAllowedInIncognitoQoraiImpl(url)) \
    return false;

#include <chrome/browser/ui/incognito_allowed_url.cc>

#undef QORAI_IS_URL_ALLOWED_IN_INCOGNITO
