/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DATABASE_DATABASE_MAINTENANCE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DATABASE_DATABASE_MAINTENANCE_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_ads/core/internal/common/timer/timer.h"
#include "qorai/components/qorai_ads/core/internal/database/database_manager_observer.h"
#include "qorai/components/qorai_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace qorai_ads::database {

class Maintenance final : public AdsClientNotifierObserver,
                          public DatabaseManagerObserver {
 public:
  Maintenance();

  Maintenance(const Maintenance&) = delete;
  Maintenance& operator=(const Maintenance&) = delete;

  ~Maintenance() override;

 private:
  void RepeatedlyScheduleAfter(base::TimeDelta after);
  void RepeatedlyScheduleAfterCallback();

  // AdsClientNotifierObserver:
  void OnNotifyPrefDidChange(const std::string& path) override;

  // DatabaseManagerObserver:
  void OnDatabaseIsReady() override;

  Timer timer_;

  base::WeakPtrFactory<Maintenance> weak_factory_{this};
};

}  // namespace qorai_ads::database

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DATABASE_DATABASE_MAINTENANCE_H_
