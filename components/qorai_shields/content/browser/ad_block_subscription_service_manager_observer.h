// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_SERVICE_MANAGER_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_SERVICE_MANAGER_OBSERVER_H_

#include "base/observer_list_types.h"

namespace qorai_shields {

class AdBlockSubscriptionServiceManagerObserver : public base::CheckedObserver {
 public:
  ~AdBlockSubscriptionServiceManagerObserver() override = default;
  virtual void OnServiceUpdateEvent() {}
};

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_SERVICE_MANAGER_OBSERVER_H_
