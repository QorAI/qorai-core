/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/confirmations/reward/reward_credential_json_writer.h"

#include "base/check.h"
#include "base/json/json_writer.h"
#include "base/values.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/reward/reward_info.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/credential_builder.h"

namespace qorai_ads::json::writer {

std::optional<std::string> WriteRewardCredential(
    base::optional_ref<const RewardInfo> reward,
    const std::string& payload) {
  CHECK(!payload.empty());

  if (!reward) {
    return std::nullopt;
  }

  std::optional<base::Value::Dict> credential =
      cbr::MaybeBuildCredential(reward->unblinded_token, payload);
  if (!credential) {
    return std::nullopt;
  }

  std::string json;
  CHECK(base::JSONWriter::Write(*credential, &json));
  return json;
}

}  // namespace qorai_ads::json::writer
