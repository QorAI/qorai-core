/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_ads/services/qor_ads_service_factory_impl.h"

#include <memory>
#include <utility>

#include "base/feature_list.h"
#include "base/functional/bind.h"
#include "base/metrics/field_trial_params.h"
#include "base/task/single_thread_task_runner.h"
#include "base/task/single_thread_task_runner_thread_mode.h"
#include "base/task/thread_pool.h"
#include "base/time/time.h"
#include "qorai/components/services/qor_ads/qor_ads_service_impl.h"
#include "content/public/browser/browser_thread.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/self_owned_receiver.h"

namespace qorai_ads {

namespace {

BASE_FEATURE(kInProcessQoraiAdsServiceFeature,
             "InProcessQoraiAdsService",
             base::FEATURE_ENABLED_BY_DEFAULT);

constexpr base::FeatureParam<base::TimeDelta> kQoraiAdsServiceStartupDelay{
    &kInProcessQoraiAdsServiceFeature, "startup_delay", base::Seconds(3)};

// Binds the `receiver` to a new provider on a background task runner.
void BindInProcessQorAdsService(
    mojo::PendingReceiver<qor_ads::mojom::QorAdsService>
        qor_ads_service_pending_receiver) {
  mojo::MakeSelfOwnedReceiver(std::make_unique<qor_ads::QorAdsServiceImpl>(),
                              std::move(qor_ads_service_pending_receiver));
}

// Launches an in process Qor Ads Service.
mojo::Remote<qor_ads::mojom::QorAdsService> LaunchInProcessQorAdsService() {
  mojo::Remote<qor_ads::mojom::QorAdsService> qor_ads_service_remote;
  base::ThreadPool::CreateSingleThreadTaskRunner(
      {base::MayBlock(), base::WithBaseSyncPrimitives()},
      base::SingleThreadTaskRunnerThreadMode::DEDICATED)
      ->PostDelayedTask(
          FROM_HERE,
          base::BindOnce(&BindInProcessQorAdsService,
                         qor_ads_service_remote.BindNewPipeAndPassReceiver()),
          kQoraiAdsServiceStartupDelay.Get());
  return qor_ads_service_remote;
}

}  // namespace

QorAdsServiceFactoryImpl::QorAdsServiceFactoryImpl() = default;

QorAdsServiceFactoryImpl::~QorAdsServiceFactoryImpl() = default;

mojo::Remote<qor_ads::mojom::QorAdsService> QorAdsServiceFactoryImpl::Launch()
    const {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  return LaunchInProcessQorAdsService();
}

}  // namespace qorai_ads
