/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_UTIL_H_

#include <optional>

namespace qorai_ads {

struct IssuersInfo;

void SetIssuers(const IssuersInfo& issuers);
std::optional<IssuersInfo> GetIssuers();

bool IsIssuersValid(const IssuersInfo& issuers);

bool HasIssuers();
bool HasIssuersChanged(const IssuersInfo& other);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_UTIL_H_
