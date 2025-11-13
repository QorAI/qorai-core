/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_SERVICES_QOR_ADS_SERVICE_FACTORY_IMPL_H_
#define QORAI_BROWSER_QORAI_ADS_SERVICES_QOR_ADS_SERVICE_FACTORY_IMPL_H_

#include "qorai/components/qorai_ads/browser/qor_ads_service_factory.h"
#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace qorai_ads {

class QorAdsServiceFactoryImpl final : public QorAdsServiceFactory {
 public:
  QorAdsServiceFactoryImpl();

  QorAdsServiceFactoryImpl(const QorAdsServiceFactoryImpl&) = delete;
  QorAdsServiceFactoryImpl& operator=(const QorAdsServiceFactoryImpl&) = delete;

  ~QorAdsServiceFactoryImpl() override;

  // QorAdsServiceFactory:
  mojo::Remote<qor_ads::mojom::QorAdsService> Launch() const override;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_SERVICES_QOR_ADS_SERVICE_FACTORY_IMPL_H_
