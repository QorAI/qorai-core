/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_SERVER_PUBLISHER_BANNER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_SERVER_PUBLISHER_BANNER_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_rewards/core/engine/database/database_server_publisher_links.h"
#include "qorai/components/qorai_rewards/core/engine/database/database_table.h"

namespace qorai_rewards::internal {
namespace database {

class DatabaseServerPublisherBanner : public DatabaseTable {
 public:
  explicit DatabaseServerPublisherBanner(RewardsEngine& engine);
  ~DatabaseServerPublisherBanner() override;

  void InsertOrUpdate(mojom::DBTransaction* transaction,
                      const mojom::ServerPublisherInfo& server_info);

  void DeleteRecords(mojom::DBTransaction* transaction,
                     const std::string& publisher_key_list);

  void GetRecord(const std::string& publisher_key,
                 GetPublisherBannerCallback callback);

 private:
  void OnGetRecord(GetPublisherBannerCallback callback,
                   const std::string& publisher_key,
                   mojom::DBCommandResponsePtr response);

  void OnGetRecordLinks(const mojom::PublisherBanner& banner,
                        GetPublisherBannerCallback callback,
                        const std::map<std::string, std::string>& links);

  DatabaseServerPublisherLinks links_;
  base::WeakPtrFactory<DatabaseServerPublisherBanner> weak_factory_{this};
};

}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_SERVER_PUBLISHER_BANNER_H_
