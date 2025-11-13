/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_STUDIES_STUDIES_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_STUDIES_STUDIES_H_

#include "qorai/components/qorai_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace qorai_ads {

class Studies final : public AdsClientNotifierObserver {
 public:
  Studies();

  Studies(const Studies&) = delete;
  Studies& operator=(const Studies&) = delete;

  ~Studies() override;

 private:
  // AdsClientNotifierObserver:
  void OnNotifyDidInitializeAds() override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_STUDIES_STUDIES_H_
