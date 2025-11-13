/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/confirmation_token_issuer_util.h"

#include <cstddef>
#include <optional>

#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_feature.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_info.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_util.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_types.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_util.h"

namespace qorai_ads {

bool IsConfirmationTokenIssuerValid(const IssuersInfo& issuers) {
  std::optional<TokenIssuerInfo> token_issuer =
      GetTokenIssuerForType(issuers, TokenIssuerType::kConfirmations);
  if (!token_issuer) {
    return false;
  }

  return token_issuer->public_keys.size() <=
         kMaximumTokenIssuerPublicKeys.Get();
}

}  // namespace qorai_ads
