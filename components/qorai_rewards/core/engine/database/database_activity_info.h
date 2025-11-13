/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_ACTIVITY_INFO_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_ACTIVITY_INFO_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/engine/database/database_table.h"

namespace qorai_rewards::internal {
namespace database {

class DatabaseActivityInfo : public DatabaseTable {
 public:
  explicit DatabaseActivityInfo(RewardsEngine& engine);
  ~DatabaseActivityInfo() override;

  void InsertOrUpdate(mojom::PublisherInfoPtr info, ResultCallback callback);

  void NormalizeList(std::vector<mojom::PublisherInfoPtr> list,
                     ResultCallback callback);

  void GetRecordsList(const int start,
                      const int limit,
                      mojom::ActivityInfoFilterPtr filter,
                      GetActivityInfoListCallback callback);

  void DeleteRecord(const std::string& publisher_key, ResultCallback callback);

  void GetPublishersVisitedCount(base::OnceCallback<void(int)> callback);

 private:
  void CreateInsertOrUpdate(mojom::DBTransaction* transaction,
                            mojom::PublisherInfoPtr info);

  void OnNormalizeList(ResultCallback callback,
                       std::vector<mojom::PublisherInfoPtr> list,
                       mojom::DBCommandResponsePtr response);

  void OnGetRecordsList(GetActivityInfoListCallback callback,
                        mojom::DBCommandResponsePtr response);
};

}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_ACTIVITY_INFO_H_
