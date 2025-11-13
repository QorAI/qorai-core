/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/profile/model/qorai_keyed_service_factories.h"

#include "qorai/components/qorai_account/features.h"
#include "qorai/ios/browser/ai_chat/ai_chat_service_factory.h"
#include "qorai/ios/browser/ai_chat/model_service_factory.h"
#include "qorai/ios/browser/api/webcompat_reporter/webcompat_reporter_service_factory.h"
#include "qorai/ios/browser/qorai_account/qorai_account_service_factory_ios.h"
#include "qorai/ios/browser/qorai_ads/ads_service_factory_ios.h"
#include "qorai/ios/browser/qorai_shields/qorai_shields_settings_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/asset_ratio_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/qorai_wallet_ipfs_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/meld_integration_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/swap_service_factory.h"
#include "qorai/ios/browser/debounce/debounce_service_factory+private.h"
#include "qorai/ios/browser/favicon/qorai_ios_favicon_loader_factory.h"
#include "qorai/ios/browser/misc_metrics/profile_misc_metrics_service_factory.h"
#include "qorai/ios/browser/skus/skus_service_factory.h"
#include "qorai/ios/browser/url_sanitizer/url_sanitizer_service_factory+private.h"

namespace qorai {

void EnsureProfileKeyedServiceFactoriesBuilt() {
  misc_metrics::ProfileMiscMetricsServiceFactory::GetInstance();
  ai_chat::ModelServiceFactory::GetInstance();
  ai_chat::AIChatServiceFactory::GetInstance();
  if (qorai_account::features::IsQoraiAccountEnabled()) {
    qorai_account::QoraiAccountServiceFactoryIOS::GetInstance();
  }
  qorai_ads::AdsServiceFactoryIOS::GetInstance();
  qorai_favicon::QoraiIOSFaviconLoaderFactory::GetInstance();
  qorai_shields::QoraiShieldsSettingsServiceFactory::GetInstance();
  qorai_wallet::AssetRatioServiceFactory::GetInstance();
  qorai_wallet::QoraiWalletIpfsServiceFactory::GetInstance();
  qorai_wallet::QoraiWalletServiceFactory::GetInstance();
  qorai_wallet::MeldIntegrationServiceFactory::GetInstance();
  qorai_wallet::SwapServiceFactory::GetInstance();
  skus::SkusServiceFactory::GetInstance();
  qorai::URLSanitizerServiceFactory::GetInstance();
  debounce::DebounceServiceFactory::GetInstance();
  webcompat_reporter::WebcompatReporterServiceFactory::GetInstance();
}

}  // namespace qorai
