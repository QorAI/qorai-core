/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CREDENTIALS_CREDENTIALS_TRIGGER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CREDENTIALS_CREDENTIALS_TRIGGER_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/mojom/rewards_engine_internal.mojom.h"

namespace qorai_rewards::internal {
namespace credential {

struct CredentialsTrigger {
  CredentialsTrigger();
  CredentialsTrigger(const CredentialsTrigger& info);
  ~CredentialsTrigger();

  std::string id;
  mojom::CredsBatchType type;
  int size;
  std::vector<std::string> data;
};

}  // namespace credential
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CREDENTIALS_CREDENTIALS_TRIGGER_H_
