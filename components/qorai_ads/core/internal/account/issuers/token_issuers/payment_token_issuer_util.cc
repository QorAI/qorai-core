/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/payment_token_issuer_util.h"

#include <optional>

#include "base/containers/flat_map.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_feature.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_info.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_util.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_types.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_util.h"

namespace qorai_ads {

bool IsPaymentTokenIssuerValid(const IssuersInfo& issuers) {
  std::optional<TokenIssuerInfo> payment_token_issuer =
      GetTokenIssuerForType(issuers, TokenIssuerType::kPayments);
  if (!payment_token_issuer) {
    return false;
  }

  const size_t maximum_token_issuer_public_keys =
      kMaximumTokenIssuerPublicKeys.Get();

  base::flat_map<double, size_t> buckets;
  for (const auto& [_, associated_value] : payment_token_issuer->public_keys) {
    ++buckets[associated_value];
    if (buckets[associated_value] > maximum_token_issuer_public_keys) {
      return false;
    }
  }

  return true;
}

}  // namespace qorai_ads
