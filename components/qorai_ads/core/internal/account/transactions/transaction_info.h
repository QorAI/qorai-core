/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTION_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTION_INFO_H_

#include <optional>
#include <string>
#include <vector>

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

namespace qorai_ads {

struct TransactionInfo final {
  TransactionInfo();

  TransactionInfo(const TransactionInfo&);
  TransactionInfo& operator=(const TransactionInfo&);

  TransactionInfo(TransactionInfo&&) noexcept;
  TransactionInfo& operator=(TransactionInfo&&) noexcept;

  ~TransactionInfo();

  bool operator==(const TransactionInfo&) const;

  [[nodiscard]] bool IsValid() const;

  std::string id;
  std::optional<base::Time> created_at;
  std::string creative_instance_id;
  std::string segment;
  double value = 0.0;
  mojom::AdType ad_type = mojom::AdType::kUndefined;
  mojom::ConfirmationType confirmation_type =
      mojom::ConfirmationType::kUndefined;
  std::optional<base::Time> reconciled_at;
};

using TransactionList = std::vector<TransactionInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTION_INFO_H_
