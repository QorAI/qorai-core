/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_ads/ads_service_factory.h"

#include <memory>
#include <utility>

#include "base/check.h"
#include "base/no_destructor.h"
#include "qorai/browser/qorai_adaptive_captcha/qorai_adaptive_captcha_service_factory.h"
#include "qorai/browser/qorai_ads/ad_units/notification_ad/notification_ad_platform_bridge.h"
#include "qorai/browser/qorai_ads/ads_service_delegate.h"
#include "qorai/browser/qorai_ads/device_id/device_id_impl.h"
#include "qorai/browser/qorai_ads/services/qor_ads_service_factory_impl.h"
#include "qorai/browser/qorai_ads/tooltips/ads_tooltips_delegate_impl.h"
#include "qorai/browser/qorai_ads/virtual_pref_provider_delegate.h"
#include "qorai/browser/qorai_browser_process.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_util.h"
#include "qorai/common/qorai_channel_info.h"
#include "qorai/components/qorai_ads/browser/ads_service_impl.h"
#include "qorai/components/qorai_ads/core/browser/service/ads_service.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/history/history_service_factory.h"
#include "chrome/browser/notifications/notification_display_service.h"
#include "chrome/browser/notifications/notification_display_service_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "content/public/browser/storage_partition.h"

namespace qorai_ads {

// static
AdsService* AdsServiceFactory::GetForProfile(Profile* profile) {
  if (!qorai_rewards::IsSupportedForProfile(profile)) {
    return nullptr;
  }

  return static_cast<AdsService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

// static
AdsServiceFactory* AdsServiceFactory::GetInstance() {
  static base::NoDestructor<AdsServiceFactory> instance;
  return instance.get();
}

AdsServiceFactory::AdsServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "AdsService",
          BrowserContextDependencyManager::GetInstance()) {
  DependsOn(NotificationDisplayServiceFactory::GetInstance());
  DependsOn(qorai_rewards::RewardsServiceFactory::GetInstance());
  DependsOn(HistoryServiceFactory::GetInstance());
  DependsOn(qorai_adaptive_captcha::QoraiAdaptiveCaptchaServiceFactory::
                GetInstance());
  DependsOn(HostContentSettingsMapFactory::GetInstance());
}

AdsServiceFactory::~AdsServiceFactory() = default;

std::unique_ptr<AdsTooltipsDelegateImpl>
AdsServiceFactory::CreateAdsTooltipsDelegate() const {
#if BUILDFLAG(IS_ANDROID)
  return nullptr;
#else
  return std::make_unique<AdsTooltipsDelegateImpl>();
#endif
}

std::unique_ptr<KeyedService>
AdsServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  auto* profile = Profile::FromBrowserContext(context);

  auto* qorai_adaptive_captcha_service =
      qorai_adaptive_captcha::QoraiAdaptiveCaptchaServiceFactory::GetForProfile(
          profile);
  CHECK(qorai_adaptive_captcha_service);

  auto delegate = std::make_unique<AdsServiceDelegate>(
      *profile, g_browser_process->local_state(),
      *qorai_adaptive_captcha_service,
      std::make_unique<NotificationAdPlatformBridge>(*profile));

  auto* history_service = HistoryServiceFactory::GetForProfile(
      profile, ServiceAccessType::EXPLICIT_ACCESS);

  auto* rewards_service =
      qorai_rewards::RewardsServiceFactory::GetForProfile(profile);

  auto* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(profile);

  return std::make_unique<AdsServiceImpl>(
      std::move(delegate), profile->GetPrefs(),
      g_browser_process->local_state(),
      std::make_unique<VirtualPrefProviderDelegate>(*profile),
      profile->GetDefaultStoragePartition()
          ->GetURLLoaderFactoryForBrowserProcess(),
      qorai::GetChannelName(), profile->GetPath(), CreateAdsTooltipsDelegate(),
      std::make_unique<DeviceIdImpl>(),
      std::make_unique<QorAdsServiceFactoryImpl>(),
      g_qorai_browser_process->resource_component(), history_service,
      rewards_service, host_content_settings_map);
}

bool AdsServiceFactory::ServiceIsNULLWhileTesting() const {
  return true;
}

}  // namespace qorai_ads
