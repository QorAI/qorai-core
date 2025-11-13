/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_LOGGING_EVENT_LOG_UTIL_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_LOGGING_EVENT_LOG_UTIL_H_

#include <string>

#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

namespace qorai_rewards::internal {
namespace log {
std::string GetEventLogKeyForLinkingResult(mojom::ConnectExternalWalletResult);
}  // namespace log
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_LOGGING_EVENT_LOG_UTIL_H_
