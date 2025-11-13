/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_SERVICE_IMPL_H_
#define QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_SERVICE_IMPL_H_

#include <memory>

#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"
#include "mojo/public/cpp/bindings/pending_associated_remote.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/unique_associated_receiver_set.h"

namespace qor_ads {

class QorAdsServiceImpl final : public mojom::QorAdsService {
 public:
  // This constructor assumes the `QorAdsServiceImpl` will be bound to an
  // externally owned receiver, such as through `mojo::MakeSelfOwnedReceiver()`.
  QorAdsServiceImpl();

  explicit QorAdsServiceImpl(mojo::PendingReceiver<mojom::QorAdsService>
                                 qor_ads_service_pending_receiver);

  QorAdsServiceImpl(const QorAdsServiceImpl&) = delete;
  QorAdsServiceImpl& operator=(const QorAdsServiceImpl&) = delete;

  ~QorAdsServiceImpl() override;

  // mojom::QorAdsService:
  void Create(const base::FilePath& service_path,
              mojo::PendingAssociatedRemote<mojom::QorAdsClient>
                  qor_ads_client_pending_associated_remote,
              mojo::PendingAssociatedReceiver<mojom::QorAds>
                  qor_ads_pending_associated_receiver,
              mojo::PendingReceiver<mojom::QorAdsClientNotifier>
                  qor_ads_client_notifier_pending_receiver,
              CreateCallback callback) override;

 private:
  mojo::Receiver<mojom::QorAdsService> qor_ads_service_receiver_{this};
  mojo::UniqueAssociatedReceiverSet<mojom::QorAds>
      qor_ads_associated_receivers_;

  struct ScopedAllowSyncCall;
  std::unique_ptr<ScopedAllowSyncCall> scoped_allow_sync_call_;
};

}  // namespace qor_ads

#endif  // QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_SERVICE_IMPL_H_
