// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/browser/qorai_news/qorai_news_controller_factory.h"

#include <memory>

#include "base/no_destructor.h"
#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/browser/qorai_news/direct_feed_fetcher_delegate_impl.h"
#include "qorai/components/qorai_news/browser/qorai_news_controller.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/favicon/favicon_service_factory.h"
#include "chrome/browser/history/history_service_factory.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/keyed_service/core/service_access_type.h"
#include "content/public/browser/browser_context.h"

namespace qorai_news {

// static
QoraiNewsControllerFactory* QoraiNewsControllerFactory::GetInstance() {
  static base::NoDestructor<QoraiNewsControllerFactory> instance;
  return instance.get();
}

// static
QoraiNewsController* QoraiNewsControllerFactory::GetForBrowserContext(
    content::BrowserContext* context) {
  return static_cast<QoraiNewsController*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

// static
mojo::PendingRemote<mojom::QoraiNewsController>
QoraiNewsControllerFactory::GetRemoteForProfile(Profile* profile) {
  auto* service = static_cast<QoraiNewsController*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
  if (!service) {
    return mojo::PendingRemote<mojom::QoraiNewsController>();
  }

  return service->MakeRemote();
}

QoraiNewsControllerFactory::QoraiNewsControllerFactory()
    : BrowserContextKeyedServiceFactory(
          "QoraiNewsControllerFactory",
          BrowserContextDependencyManager::GetInstance()) {
  DependsOn(qorai_ads::AdsServiceFactory::GetInstance());
  DependsOn(HistoryServiceFactory::GetInstance());
  DependsOn(HostContentSettingsMapFactory::GetInstance());
}

QoraiNewsControllerFactory::~QoraiNewsControllerFactory() = default;

bool QoraiNewsControllerFactory::ServiceIsCreatedWithBrowserContext() const {
  return true;
}

std::unique_ptr<KeyedService>
QoraiNewsControllerFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  if (!Profile::FromBrowserContext(context)->IsRegularProfile()) {
    return nullptr;
  }
  auto* profile = Profile::FromBrowserContext(context);
  if (!profile) {
    return nullptr;
  }
  auto* ads_service = qorai_ads::AdsServiceFactory::GetForProfile(profile);
  auto* history_service = HistoryServiceFactory::GetForProfile(
      profile, ServiceAccessType::EXPLICIT_ACCESS);
  auto* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(profile);
  return std::make_unique<QoraiNewsController>(
      profile->GetPrefs(), ads_service, history_service,
      profile->GetURLLoaderFactory(),
      std::make_unique<DirectFeedFetcherDelegateImpl>(
          host_content_settings_map));
}

bool QoraiNewsControllerFactory::ServiceIsNULLWhileTesting() const {
  // QoraiNewsController expects non-null FaviconService, HistoryService, and
  // SharedURLLoaderFactory. All of these are nullptr in unit tests.
  return true;
}

}  // namespace qorai_news
