/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SYNC_QORAI_SYNC_P3A_H_
#define QORAI_COMPONENTS_QORAI_SYNC_QORAI_SYNC_P3A_H_

#include "components/sync/base/user_selectable_type.h"

namespace qorai_sync {
namespace p3a {

// TODO(alexeybarabash): move here also "Qorai.Sync.Status.2" and
// "Qorai.Sync.ProgressTokenEverReset"
inline constexpr char kEnabledTypesHistogramName[] = "Qorai.Sync.EnabledTypes";
// Improved version of metric which includes count of synced History objects
inline constexpr char kSyncedObjectsCountHistogramNameV2[] =
    "Qorai.Sync.SyncedObjectsCount.2";
inline constexpr char kSyncJoinTypeHistogramName[] = "Qorai.Sync.JoinType";

enum class EnabledTypesAnswer {
  kEmptyOrBookmarksOnly = 0,
  kBookmarksAndHistory = 1,
  kMoreThanBookmarksAndHistory = 2,
  kAllTypes = 3,
  kMaxValue = kAllTypes
};

enum class SyncJoinType {
  kChainCreated = 1,
  kChainJoined = 2,
  kMaxValue = kChainJoined
};

void RecordEnabledTypes(bool sync_everything_enabled,
                        const syncer::UserSelectableTypeSet& selected_types);
void RecordSyncedObjectsCount(int total_entities);

// Monitors sync code generation and setting events in order
// to report the `Qorai.Sync.JoinType` metric.
class SyncCodeMonitor {
 public:
  SyncCodeMonitor() = default;
  ~SyncCodeMonitor() = default;

  SyncCodeMonitor(const SyncCodeMonitor&) = delete;
  SyncCodeMonitor& operator=(const SyncCodeMonitor&) = delete;

  void RecordCodeGenerated();
  void RecordCodeSet();

 private:
  bool code_generated_ = false;
};

}  // namespace p3a
}  // namespace qorai_sync

#endif  // QORAI_COMPONENTS_QORAI_SYNC_QORAI_SYNC_P3A_H_
