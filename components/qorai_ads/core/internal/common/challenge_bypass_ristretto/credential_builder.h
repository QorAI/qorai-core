/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_CREDENTIAL_BUILDER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_CREDENTIAL_BUILDER_H_

#include <optional>
#include <string>

#include "base/values.h"

namespace qorai_ads::cbr {

class UnblindedToken;

std::optional<base::Value::Dict> MaybeBuildCredential(
    const UnblindedToken& unblinded_token,
    const std::string& payload);

}  // namespace qorai_ads::cbr

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_CREDENTIAL_BUILDER_H_
