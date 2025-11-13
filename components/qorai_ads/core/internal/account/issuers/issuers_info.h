/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_INFO_H_

#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"

namespace qorai_ads {

struct IssuersInfo final {
  IssuersInfo();

  IssuersInfo(const IssuersInfo&);
  IssuersInfo& operator=(const IssuersInfo&);

  IssuersInfo(IssuersInfo&&) noexcept;
  IssuersInfo& operator=(IssuersInfo&&) noexcept;

  ~IssuersInfo();

  bool operator==(const IssuersInfo&) const = default;

  int ping = 0;
  TokenIssuerList token_issuers;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_INFO_H_
