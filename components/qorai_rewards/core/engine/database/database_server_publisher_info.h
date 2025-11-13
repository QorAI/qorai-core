/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_SERVER_PUBLISHER_INFO_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_SERVER_PUBLISHER_INFO_H_

#include <string>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_rewards/core/engine/database/database_server_publisher_banner.h"
#include "qorai/components/qorai_rewards/core/engine/database/database_table.h"

namespace qorai_rewards::internal {
namespace database {

class DatabaseServerPublisherInfo : public DatabaseTable {
 public:
  explicit DatabaseServerPublisherInfo(RewardsEngine& engine);
  ~DatabaseServerPublisherInfo() override;

  void InsertOrUpdate(const mojom::ServerPublisherInfo& server_info,
                      ResultCallback callback);

  void GetRecord(const std::string& publisher_key,
                 GetServerPublisherInfoCallback callback);

  void DeleteExpiredRecords(int64_t max_age_seconds, ResultCallback callback);

 private:
  void OnGetRecordBanner(const std::string& publisher_key,
                         GetServerPublisherInfoCallback callback,
                         mojom::PublisherBannerPtr banner);

  void OnGetRecord(GetServerPublisherInfoCallback callback,
                   const std::string& publisher_key,
                   mojom::PublisherBannerPtr banner,
                   mojom::DBCommandResponsePtr response);

  void OnExpiredRecordsSelected(ResultCallback callback,
                                mojom::DBCommandResponsePtr response);

  DatabaseServerPublisherBanner banner_;
  base::WeakPtrFactory<DatabaseServerPublisherInfo> weak_factory_{this};
};

}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_SERVER_PUBLISHER_INFO_H_
