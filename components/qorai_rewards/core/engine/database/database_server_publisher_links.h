/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_SERVER_PUBLISHER_LINKS_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_SERVER_PUBLISHER_LINKS_H_

#include <map>
#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/engine/database/database_table.h"

namespace qorai_rewards::internal {
namespace database {

class DatabaseServerPublisherLinks : public DatabaseTable {
 public:
  explicit DatabaseServerPublisherLinks(RewardsEngine& engine);
  ~DatabaseServerPublisherLinks() override;

  void InsertOrUpdate(mojom::DBTransaction* transaction,
                      const mojom::ServerPublisherInfo& server_info);

  void DeleteRecords(mojom::DBTransaction* transaction,
                     const std::string& publisher_key_list);

  void GetRecord(const std::string& publisher_key,
                 ServerPublisherLinksCallback callback);

 private:
  void OnGetRecord(ServerPublisherLinksCallback callback,
                   mojom::DBCommandResponsePtr response);
};

}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_SERVER_PUBLISHER_LINKS_H_
