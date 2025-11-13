/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_H_

#include <string>

#include "base/functional/callback.h"
#include "qorai/components/qorai_ads/core/internal/creatives/creative_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/database/database_table_interface.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads::database::table {

using GetCreativeAdCallback =
    base::OnceCallback<void(bool success,
                            const std::string& creative_instance_id,
                            const CreativeAdInfo& creative_ad)>;

class CreativeAds final : public TableInterface {
 public:
  void Insert(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
              const CreativeAdList& creative_ads);

  void GetForCreativeInstanceId(const std::string& creative_instance_id,
                                GetCreativeAdCallback callback) const;

  std::string GetTableName() const override;

  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;

 private:
  void MigrateToV48(const mojom::DBTransactionInfoPtr& mojom_db_transaction);

  std::string BuildInsertSql(const mojom::DBActionInfoPtr& mojom_db_action,
                             const CreativeAdList& creative_ads) const;
};

}  // namespace qorai_ads::database::table

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_H_
