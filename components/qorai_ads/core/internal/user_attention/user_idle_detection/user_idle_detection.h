/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_IDLE_DETECTION_USER_IDLE_DETECTION_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_IDLE_DETECTION_USER_IDLE_DETECTION_H_

#include "qorai/components/qorai_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace qorai_ads {

class UserIdleDetection final : public AdsClientNotifierObserver {
 public:
  UserIdleDetection();

  UserIdleDetection(const UserIdleDetection&) = delete;
  UserIdleDetection& operator=(const UserIdleDetection&) = delete;

  ~UserIdleDetection() override;

 private:
  // AdsClientNotifierObserver:
  void OnNotifyUserDidBecomeActive(base::TimeDelta idle_time,
                                   bool screen_was_locked) override;
  void OnNotifyUserDidBecomeIdle() override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_IDLE_DETECTION_USER_IDLE_DETECTION_H_
