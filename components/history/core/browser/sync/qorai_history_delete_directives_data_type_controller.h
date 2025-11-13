/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_HISTORY_CORE_BROWSER_SYNC_QORAI_HISTORY_DELETE_DIRECTIVES_DATA_TYPE_CONTROLLER_H_
#define QORAI_COMPONENTS_HISTORY_CORE_BROWSER_SYNC_QORAI_HISTORY_DELETE_DIRECTIVES_DATA_TYPE_CONTROLLER_H_

#include "base/functional/callback_forward.h"
#include "components/history/core/browser/sync/history_delete_directives_data_type_controller.h"

class PrefService;

namespace syncer {
class DataTypeStoreService;
class SyncService;
}  // namespace syncer

namespace history {

class QorAIHistoryDeleteDirectivesDataTypeController
    : public HistoryDeleteDirectivesDataTypeController {
 public:
  QorAIHistoryDeleteDirectivesDataTypeController(
      const base::RepeatingClosure& dump_stack,
      syncer::SyncService* sync_service,
      syncer::DataTypeStoreService* data_type_store_service,
      HistoryService* history_service,
      PrefService* pref_service);

  QorAIHistoryDeleteDirectivesDataTypeController(
      const QorAIHistoryDeleteDirectivesDataTypeController&) = delete;
  QorAIHistoryDeleteDirectivesDataTypeController& operator=(
      const QorAIHistoryDeleteDirectivesDataTypeController&) = delete;

  ~QorAIHistoryDeleteDirectivesDataTypeController() override;

  // DataTypeController overrides.
  PreconditionState GetPreconditionState() const override;
};

}  // namespace history

#endif  // QORAI_COMPONENTS_HISTORY_CORE_BROWSER_SYNC_QORAI_HISTORY_DELETE_DIRECTIVES_DATA_TYPE_CONTROLLER_H_
