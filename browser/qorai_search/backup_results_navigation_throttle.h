/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_SEARCH_BACKUP_RESULTS_NAVIGATION_THROTTLE_H_
#define QORAI_BROWSER_QORAI_SEARCH_BACKUP_RESULTS_NAVIGATION_THROTTLE_H_

#include "content/public/browser/navigation_throttle.h"

namespace qorai_search {

class BackupResultsNavigationThrottle : public content::NavigationThrottle {
 public:
  explicit BackupResultsNavigationThrottle(
      content::NavigationThrottleRegistry& registry);
  ~BackupResultsNavigationThrottle() override;

  BackupResultsNavigationThrottle(const BackupResultsNavigationThrottle&) =
      delete;
  BackupResultsNavigationThrottle& operator=(
      const BackupResultsNavigationThrottle&) = delete;

  static void MaybeCreateAndAdd(content::NavigationThrottleRegistry& registry);

 private:
  // content::NavigationThrottle overrides:
  ThrottleCheckResult WillStartRequest() override;
  ThrottleCheckResult WillRedirectRequest() override;

  const char* GetNameForLogging() override;
};

}  // namespace qorai_search

#endif  // QORAI_BROWSER_QORAI_SEARCH_BACKUP_RESULTS_NAVIGATION_THROTTLE_H_
