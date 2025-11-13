/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_PUBLISHER_PUBLISHER_STATUS_HELPER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_PUBLISHER_PUBLISHER_STATUS_HELPER_H_

#include <vector>

#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace publisher {

using RefreshPublisherStatusCallback =
    base::OnceCallback<void(std::vector<mojom::PublisherInfoPtr>)>;

// Refreshes the publisher status for each entry in the specified list
void RefreshPublisherStatus(RewardsEngine& engine,
                            std::vector<mojom::PublisherInfoPtr>&& info_list,
                            RefreshPublisherStatusCallback callback);

}  // namespace publisher
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_PUBLISHER_PUBLISHER_STATUS_HELPER_H_
