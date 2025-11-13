/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_PUBLISHER_INFO_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_PUBLISHER_INFO_H_

#include <string>

#include "qorai/components/qorai_rewards/core/engine/database/database_table.h"

namespace qorai_rewards::internal {
namespace database {

class DatabasePublisherInfo : public DatabaseTable {
 public:
  explicit DatabasePublisherInfo(RewardsEngine& engine);
  ~DatabasePublisherInfo() override;

  void InsertOrUpdate(mojom::PublisherInfoPtr info, ResultCallback callback);

  void GetRecord(const std::string& publisher_key,
                 GetPublisherInfoCallback callback);

  void GetPanelRecord(mojom::ActivityInfoFilterPtr filter,
                      GetPublisherPanelInfoCallback callback);

  void RestorePublishers(ResultCallback callback);

  void GetExcludedList(GetExcludedListCallback callback);

 private:
  void OnGetRecord(GetPublisherInfoCallback callback,
                   mojom::DBCommandResponsePtr response);

  void OnGetPanelRecord(GetPublisherPanelInfoCallback callback,
                        mojom::DBCommandResponsePtr response);

  void OnRestorePublishers(ResultCallback callback,
                           mojom::DBCommandResponsePtr response);

  void OnGetExcludedList(GetExcludedListCallback callback,
                         mojom::DBCommandResponsePtr response);
};

}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_PUBLISHER_INFO_H_
