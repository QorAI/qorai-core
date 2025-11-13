/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/history/core/browser/sync/qorai_history_delete_directives_data_type_controller.h"

#include "base/check.h"
#include "components/history/core/browser/sync/history_delete_directives_data_type_controller.h"

namespace history {

QorAIHistoryDeleteDirectivesDataTypeController::
    QorAIHistoryDeleteDirectivesDataTypeController(
        const base::RepeatingClosure& dump_stack,
        syncer::SyncService* sync_service,
        syncer::DataTypeStoreService* data_type_store_service,
        HistoryService* history_service,
        PrefService* pref_service)
    : HistoryDeleteDirectivesDataTypeController(dump_stack,
                                                sync_service,
                                                data_type_store_service,
                                                history_service,
                                                pref_service) {}

QorAIHistoryDeleteDirectivesDataTypeController::
    ~QorAIHistoryDeleteDirectivesDataTypeController() = default;

syncer::DataTypeController::PreconditionState
QorAIHistoryDeleteDirectivesDataTypeController::GetPreconditionState() const {
  DCHECK(CalledOnValidThread());
  return PreconditionState::kPreconditionsMet;
}

}  // namespace history
