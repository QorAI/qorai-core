/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/constants/qorai_services_key_helper.h"

#include "base/strings/pattern.h"
#include "url/gurl.h"
#include "url/url_constants.h"

namespace qorai {

inline constexpr char kQoraiProxyPattern[] = "*.qorai.com";
inline constexpr char kQoraiSoftwareProxyPattern[] = "*.qoraisoftware.com";

bool ShouldAddQoraiServicesKeyHeader(const GURL& url) {
  return url.SchemeIs(url::kHttpsScheme) &&
         (base::MatchPattern(url.host(), kQoraiProxyPattern) ||
          base::MatchPattern(url.host(), kQoraiSoftwareProxyPattern));
}

}  // namespace qorai
