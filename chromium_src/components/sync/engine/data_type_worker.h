/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_ENGINE_DATA_TYPE_WORKER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_ENGINE_DATA_TYPE_WORKER_H_

#include "base/gtest_prod_util.h"

namespace syncer {

FORWARD_DECLARE_TEST(QoraiDataTypeWorkerTest, ResetProgressMarker);
FORWARD_DECLARE_TEST(QoraiDataTypeWorkerTest, ResetProgressMarkerMaxPeriod);

}  // namespace syncer

#define QORAI_MODEL_TYPE_WORKER_H_                                        \
 private:                                                                 \
  friend class QoraiDataTypeWorker;                                       \
  friend class QoraiDataTypeWorkerTest;                                   \
  FRIEND_TEST_ALL_PREFIXES(QoraiDataTypeWorkerTest, ResetProgressMarker); \
  FRIEND_TEST_ALL_PREFIXES(QoraiDataTypeWorkerTest,                       \
                           ResetProgressMarkerMaxPeriod);

#define OnCommitResponse virtual OnCommitResponse

#include <components/sync/engine/data_type_worker.h>  // IWYU pragma: export

#undef OnCommitResponse
#undef QORAI_MODEL_TYPE_WORKER_H_

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_ENGINE_DATA_TYPE_WORKER_H_
