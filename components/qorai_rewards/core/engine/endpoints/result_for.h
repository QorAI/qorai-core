/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_RESULT_FOR_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_RESULT_FOR_H_

namespace qorai_rewards::internal::endpoints {

template <typename>
inline constexpr bool dependent_false_v = false;

template <typename Endpoint>
struct ResultFor {
  static_assert(dependent_false_v<Endpoint>,
                "Please explicitly specialize ResultFor<> for your endpoint!");
};

}  // namespace qorai_rewards::internal::endpoints

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_RESULT_FOR_H_
