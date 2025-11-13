/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_BROWSER_QOR_ADS_SERVICE_FACTORY_H_
#define QORAI_COMPONENTS_QORAI_ADS_BROWSER_QOR_ADS_SERVICE_FACTORY_H_

#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace qorai_ads {

class QorAdsServiceFactory {
 public:
  virtual ~QorAdsServiceFactory() = default;

  // Launches a new Qor Ads Service.
  virtual mojo::Remote<qor_ads::mojom::QorAdsService> Launch() const = 0;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_BROWSER_QOR_ADS_SERVICE_FACTORY_H_
