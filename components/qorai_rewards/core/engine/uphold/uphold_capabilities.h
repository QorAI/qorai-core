/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UPHOLD_UPHOLD_CAPABILITIES_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UPHOLD_UPHOLD_CAPABILITIES_H_

#include <optional>

namespace qorai_rewards::internal {
namespace uphold {

struct Capabilities {
  std::optional<bool> can_receive;
  std::optional<bool> can_send;
};

}  // namespace uphold
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UPHOLD_UPHOLD_CAPABILITIES_H_
