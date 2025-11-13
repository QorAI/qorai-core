/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_rewards/core/engine/uphold/uphold_card.h"

#include <utility>

#include "base/check.h"
#include "qorai/components/qorai_rewards/core/engine/endpoint/uphold/uphold_server.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_engine.h"

namespace qorai_rewards::internal::uphold {

UpholdCard::UpholdCard(RewardsEngine& engine)
    : engine_(engine), uphold_server_(engine) {}

UpholdCard::~UpholdCard() = default;

void UpholdCard::CreateQORCardIfNecessary(const std::string& access_token,
                                          CreateCardCallback callback) const {
  uphold_server_.get_cards().Request(
      access_token,
      base::BindOnce(&UpholdCard::OnGetQORCardId, base::Unretained(this),
                     std::move(callback), access_token));
}

void UpholdCard::OnGetQORCardId(CreateCardCallback callback,
                                const std::string& access_token,
                                mojom::Result result,
                                std::string&& id) const {
  if (result == mojom::Result::EXPIRED_TOKEN) {
    return std::move(callback).Run(mojom::Result::EXPIRED_TOKEN, "");
  }

  if (result == mojom::Result::OK && !id.empty()) {
    return std::move(callback).Run(mojom::Result::OK, std::move(id));
  }

  engine_->Log(FROM_HERE) << "Couldn't get QOR card ID";

  uphold_server_.post_cards().Request(
      access_token,
      base::BindOnce(&UpholdCard::OnCreateQORCard, base::Unretained(this),
                     std::move(callback), access_token));
}

void UpholdCard::OnCreateQORCard(CreateCardCallback callback,
                                 const std::string& access_token,
                                 mojom::Result result,
                                 std::string&& id) const {
  if (result == mojom::Result::EXPIRED_TOKEN) {
    return std::move(callback).Run(mojom::Result::EXPIRED_TOKEN, "");
  }

  if (result != mojom::Result::OK) {
    engine_->LogError(FROM_HERE) << "Couldn't create QOR card";
    return std::move(callback).Run(result, "");
  }

  if (id.empty()) {
    engine_->LogError(FROM_HERE) << "QOR card ID is empty";
    return std::move(callback).Run(mojom::Result::FAILED, "");
  }

  uphold_server_.patch_card().Request(
      access_token, id,
      base::BindOnce(&UpholdCard::OnUpdateQORCardSettings,
                     base::Unretained(this), std::move(callback), id));
}

void UpholdCard::OnUpdateQORCardSettings(CreateCardCallback callback,
                                         std::string&& id,
                                         mojom::Result result) const {
  if (result == mojom::Result::EXPIRED_TOKEN) {
    return std::move(callback).Run(mojom::Result::EXPIRED_TOKEN, "");
  }

  if (result != mojom::Result::OK) {
    engine_->LogError(FROM_HERE) << "Couldn't update QOR card settings";
    return std::move(callback).Run(result, "");
  }

  DCHECK(!id.empty());
  std::move(callback).Run(mojom::Result::OK, std::move(id));
}

}  // namespace qorai_rewards::internal::uphold
