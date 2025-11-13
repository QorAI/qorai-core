/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_SYNC_QORAI_SYNC_ALERTS_SERVICE_H_
#define QORAI_BROWSER_SYNC_QORAI_SYNC_ALERTS_SERVICE_H_

#include "base/memory/raw_ptr.h"
#include "base/scoped_multi_source_observation.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/sync/service/sync_service.h"
#include "components/sync/service/sync_service_observer.h"

class Profile;

namespace syncer {
class SyncService;
class SyncServiceObserver;
}  // namespace syncer

class QoraiSyncAlertsService : public KeyedService,
                               public syncer::SyncServiceObserver {
 public:
  explicit QoraiSyncAlertsService(Profile* profile);
  QoraiSyncAlertsService(const QoraiSyncAlertsService&) = delete;
  QoraiSyncAlertsService& operator=(const QoraiSyncAlertsService&) = delete;
  ~QoraiSyncAlertsService() override;

 private:
  // syncer::SyncServiceObserver implementation.
  void OnStateChanged(syncer::SyncService* service) override;
  void OnSyncShutdown(syncer::SyncService* sync) override;

  void ShowInfobar();

  raw_ptr<Profile> profile_ = nullptr;
  base::ScopedMultiSourceObservation<syncer::SyncService,
                                     syncer::SyncServiceObserver>
      sync_service_observer_{this};
  base::WeakPtrFactory<QoraiSyncAlertsService> weak_ptr_factory_{this};
};

#endif  // QORAI_BROWSER_SYNC_QORAI_SYNC_ALERTS_SERVICE_H_
