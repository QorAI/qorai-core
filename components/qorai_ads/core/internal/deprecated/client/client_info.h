/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DEPRECATED_CLIENT_CLIENT_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DEPRECATED_CLIENT_CLIENT_INFO_H_

#include <string>

#include "base/values.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_signal_history_info.h"
#include "qorai/components/qorai_ads/core/internal/targeting/contextual/text_classification/model/text_classification_alias.h"

namespace qorai_ads {

struct ClientInfo final {
  ClientInfo();

  ClientInfo(const ClientInfo&);
  ClientInfo& operator=(const ClientInfo&);

  ClientInfo(ClientInfo&&) noexcept;
  ClientInfo& operator=(ClientInfo&&) noexcept;

  ~ClientInfo();

  base::Value::Dict ToValue() const;
  [[nodiscard]] bool FromValue(const base::Value::Dict& dict);

  std::string ToJson() const;
  [[nodiscard]] bool FromJson(const std::string& json);

  TextClassificationProbabilityList text_classification_probabilities;
  PurchaseIntentSignalHistoryMap purchase_intent_signal_history;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DEPRECATED_CLIENT_CLIENT_INFO_H_
