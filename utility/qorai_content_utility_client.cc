/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/utility/qorai_content_utility_client.h"

#include <memory>
#include <utility>

#include "qorai/components/services/qor_ads/qor_ads_service_impl.h"
#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"
#include "qorai/components/services/qor_rewards/public/interfaces/rewards_engine_factory.mojom.h"
#include "qorai/components/services/qor_rewards/rewards_engine_factory.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "mojo/public/cpp/bindings/service_factory.h"

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/utility/importer/qorai_profile_import_impl.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/components/services/tor/public/interfaces/tor.mojom.h"
#include "qorai/components/services/tor/tor_launcher_impl.h"
#endif

#include "qorai/components/services/qorai_wallet/qorai_wallet_utils_service_impl.h"
#include "qorai/components/services/qorai_wallet/public/mojom/qorai_wallet_utils_service.mojom.h"

namespace {

#if !BUILDFLAG(IS_ANDROID)
auto RunQoraiProfileImporter(
    mojo::PendingReceiver<qorai::mojom::ProfileImport> receiver) {
  return std::make_unique<QoraiProfileImportImpl>(std::move(receiver));
}
#endif

#if BUILDFLAG(ENABLE_TOR)
auto RunTorLauncher(mojo::PendingReceiver<tor::mojom::TorLauncher> receiver) {
  return std::make_unique<tor::TorLauncherImpl>(std::move(receiver));
}
#endif

auto RunRewardsEngineFactory(
    mojo::PendingReceiver<qorai_rewards::mojom::RewardsEngineFactory>
        receiver) {
  return std::make_unique<qorai_rewards::internal::RewardsEngineFactory>(
      std::move(receiver));
}

auto RunQorAdsService(
    mojo::PendingReceiver<qor_ads::mojom::QorAdsService> receiver) {
  return std::make_unique<qor_ads::QorAdsServiceImpl>(std::move(receiver));
}

auto RunQoraiWalletUtilsService(
    mojo::PendingReceiver<qorai_wallet::mojom::QoraiWalletUtilsService>
        receiver) {
  return std::make_unique<qorai_wallet::QoraiWalletUtilsServiceImpl>(
      std::move(receiver));
}

}  // namespace

QoraiContentUtilityClient::QoraiContentUtilityClient() = default;
QoraiContentUtilityClient::~QoraiContentUtilityClient() = default;

void QoraiContentUtilityClient::RegisterMainThreadServices(
    mojo::ServiceFactory& services) {
#if !BUILDFLAG(IS_ANDROID)
  services.Add(RunQoraiProfileImporter);
#endif

#if BUILDFLAG(ENABLE_TOR)
  services.Add(RunTorLauncher);
#endif

  services.Add(RunRewardsEngineFactory);

  services.Add(RunQorAdsService);

  services.Add(RunQoraiWalletUtilsService);

  return ChromeContentUtilityClient::RegisterMainThreadServices(services);
}
