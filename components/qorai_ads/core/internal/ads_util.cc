/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/ads_util.h"

#include "qorai/components/qorai_ads/core/public/common/locale/locale_util.h"
#include "qorai/components/l10n/common/ofac_sanction_util.h"

namespace qorai_ads {

bool IsSupportedRegion() {
  return !qorai_l10n::IsISOCountryCodeOFACSanctioned(CurrentCountryCode());
}

}  // namespace qorai_ads
