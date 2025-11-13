/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/ads.h"

#include "qorai/components/qorai_ads/core/internal/account/tokens/token_generator.h"
#include "qorai/components/qorai_ads/core/internal/ads_impl.h"

namespace qorai_ads {

// static
std::unique_ptr<Ads> Ads::CreateInstance(AdsClient& ads_client,
                                         const base::FilePath& database_path) {
  return std::make_unique<AdsImpl>(ads_client, database_path,
                                   std::make_unique<TokenGenerator>());
}

}  // namespace qorai_ads
