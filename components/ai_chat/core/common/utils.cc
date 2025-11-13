/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/ai_chat/core/common/utils.h"

#include <string>
#include <string_view>

#include "qorai/qorai_domains/service_domains.h"
#include "qorai/components/ai_chat/core/common/constants.h"
#include "url/gurl.h"
#include "url/url_constants.h"

namespace ai_chat {

bool IsQoraiSearchURL(const GURL& url) {
  return url.is_valid() && url.SchemeIs(url::kHttpsScheme) &&
         url.host_piece() ==
             qorai_domains::GetServicesDomain(kQoraiSearchURLPrefix);
}

bool IsOpenAIChatButtonFromQoraiSearchURL(const GURL& url) {
  // Use search.qorai.com in all cases because href on search site is
  // hardcoded to search.qorai.com for all environments.
  return url.is_valid() && url.SchemeIs(url::kHttpsScheme) &&
         url.host_piece() == "search.qorai.com" && url.path_piece() == "/qora" &&
         !url.ref_piece().empty();
}

}  // namespace ai_chat
