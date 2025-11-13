/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/services/qor_ads/qor_ads_service_impl.h"

#include <memory>
#include <utility>

#include "base/check.h"
#include "base/files/file_path.h"
#include "qorai/components/services/qor_ads/qor_ads_impl.h"
#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"
#include "mojo/public/cpp/bindings/sync_call_restrictions.h"

namespace qor_ads {

struct QorAdsServiceImpl::ScopedAllowSyncCall {
  // TODO(https://github.com/qorai/qorai-browser/issues/29870): Get rid of
  // scoped allow sync calls object when Qorai Ads [Sync] mojom calls are
  // refactored. mojo::ScopedAllowSyncCallForTesting is used to avoid patching
  // of chromium sync_call_restrictions.h file.
  mojo::ScopedAllowSyncCallForTesting scoped_allow_sync_call;
};

QorAdsServiceImpl::QorAdsServiceImpl()
    : scoped_allow_sync_call_(std::make_unique<ScopedAllowSyncCall>()) {}

QorAdsServiceImpl::QorAdsServiceImpl(mojo::PendingReceiver<mojom::QorAdsService>
                                         qor_ads_service_pending_receiver)
    : qor_ads_service_receiver_(this,
                                std::move(qor_ads_service_pending_receiver)) {}

QorAdsServiceImpl::~QorAdsServiceImpl() = default;

void QorAdsServiceImpl::Create(
    const base::FilePath& service_path,
    mojo::PendingAssociatedRemote<mojom::QorAdsClient>
        qor_ads_client_pending_associated_remote,
    mojo::PendingAssociatedReceiver<mojom::QorAds>
        qor_ads_pending_associated_receiver,
    mojo::PendingReceiver<mojom::QorAdsClientNotifier>
        qor_ads_client_notifier_pending_receiver,
    CreateCallback callback) {
  CHECK(qor_ads_pending_associated_receiver.is_valid());

  qor_ads_associated_receivers_.Add(
      std::make_unique<QorAdsImpl>(
          service_path, std::move(qor_ads_client_pending_associated_remote),
          std::move(qor_ads_client_notifier_pending_receiver)),
      std::move(qor_ads_pending_associated_receiver));

  std::move(callback).Run();
}

}  // namespace qor_ads
