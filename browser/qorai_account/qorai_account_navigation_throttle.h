/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_NAVIGATION_THROTTLE_H_
#define QORAI_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_NAVIGATION_THROTTLE_H_

#include "content/public/browser/navigation_throttle.h"

namespace content {
class NavigationThrottleRegistry;
}  // namespace content

class QorAIAccountNavigationThrottle : public content::NavigationThrottle {
 public:
  static void MaybeCreateAndAdd(content::NavigationThrottleRegistry& registry);

  QorAIAccountNavigationThrottle(const QorAIAccountNavigationThrottle&) =
      delete;
  QorAIAccountNavigationThrottle& operator=(
      const QorAIAccountNavigationThrottle&) = delete;

  ~QorAIAccountNavigationThrottle() override;

 private:
  explicit QorAIAccountNavigationThrottle(
      content::NavigationThrottleRegistry& registry);

  // content::NavigationThrottle:
  content::NavigationThrottle::ThrottleCheckResult WillStartRequest() override;
  const char* GetNameForLogging() override;
};

#endif  // QORAI_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_NAVIGATION_THROTTLE_H_
