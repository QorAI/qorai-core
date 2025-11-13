/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_REWARDS_PROTOCOL_NAVIGATION_THROTTLE_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_REWARDS_PROTOCOL_NAVIGATION_THROTTLE_H_

#include "content/public/browser/navigation_throttle.h"

namespace qorai_rewards {

class RewardsProtocolNavigationThrottle : public content::NavigationThrottle {
 public:
  explicit RewardsProtocolNavigationThrottle(
      content::NavigationThrottleRegistry& registry);
  ~RewardsProtocolNavigationThrottle() override;

  RewardsProtocolNavigationThrottle(const RewardsProtocolNavigationThrottle&) =
      delete;
  RewardsProtocolNavigationThrottle& operator=(
      const RewardsProtocolNavigationThrottle&) = delete;

  static void MaybeCreateAndAdd(content::NavigationThrottleRegistry& registry);

  // Implements content::NavigationThrottle.
  ThrottleCheckResult WillStartRequest() override;
  ThrottleCheckResult WillRedirectRequest() override;
  const char* GetNameForLogging() override;

 private:
  ThrottleCheckResult MaybeRedirect();
};

}  // namespace qorai_rewards

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_REWARDS_PROTOCOL_NAVIGATION_THROTTLE_H_
