/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_HISTORY_CORE_BROWSER_SYNC_QORAI_HISTORY_DATA_TYPE_CONTROLLER_H_
#define QORAI_COMPONENTS_HISTORY_CORE_BROWSER_SYNC_QORAI_HISTORY_DATA_TYPE_CONTROLLER_H_

#include "components/history/core/browser/sync/history_data_type_controller.h"
#include "components/sync/base/data_type.h"

class PrefService;

namespace signin {
// class AccountManagedStatusFinder;
class IdentityManager;
}  // namespace signin

namespace syncer {
// class DataTypeStoreService;
class SyncService;
}  // namespace syncer

namespace history {

class HistoryService;

class QorAIHistoryDataTypeController : public HistoryDataTypeController {
 public:
  QorAIHistoryDataTypeController(syncer::SyncService* sync_service,
                                 signin::IdentityManager* identity_manager,
                                 HistoryService* history_service,
                                 PrefService* pref_service);

  QorAIHistoryDataTypeController(const QorAIHistoryDataTypeController&) =
      delete;
  QorAIHistoryDataTypeController& operator=(
      const QorAIHistoryDataTypeController&) = delete;

  ~QorAIHistoryDataTypeController() override;

  // syncer::DataTypeController implementation.
  PreconditionState GetPreconditionState() const override;
};

}  // namespace history

#endif  // QORAI_COMPONENTS_HISTORY_CORE_BROWSER_SYNC_QORAI_HISTORY_DATA_TYPE_CONTROLLER_H_
