/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/history/core/browser/sync/qorai_history_data_type_controller.h"
#include "qorai/components/history/core/browser/sync/qorai_history_delete_directives_data_type_controller.h"

#define HistoryDeleteDirectivesDataTypeController \
  QoraiHistoryDeleteDirectivesDataTypeController

#define HistoryDataTypeController QoraiHistoryDataTypeController

#include <components/browser_sync/common_controller_builder.cc>

#undef HistoryDataTypeController
#undef HistoryDeleteDirectivesDataTypeController
