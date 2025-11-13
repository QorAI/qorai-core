/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"

#include <utility>

#include "base/feature_list.h"
#include "base/no_destructor.h"
#include "qorai/browser/qorai_browser_process.h"
#include "qorai/browser/qorai_vpn/vpn_utils.h"
#include "qorai/browser/misc_metrics/process_misc_metrics.h"
#include "qorai/browser/misc_metrics/uptime_monitor_impl.h"
#include "qorai/browser/skus/skus_service_factory.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "qorai/components/skus/common/features.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/storage_partition.h"

#if BUILDFLAG(IS_WIN)
#include "qorai/browser/qorai_vpn/dns/qorai_vpn_dns_observer_factory_win.h"
#include "qorai/browser/qorai_vpn/dns/qorai_vpn_dns_observer_service_win.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_service_delegate_win.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_observer_factory_win.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_observer_service_win.h"
#endif

namespace qorai_vpn {
namespace {

std::unique_ptr<KeyedService> BuildVpnService(
    content::BrowserContext* context) {
  if (!qorai_vpn::IsAllowedForContext(context)) {
    return nullptr;
  }

#if !BUILDFLAG(IS_ANDROID)
  if (!g_qorai_browser_process->qorai_vpn_connection_manager()) {
    return nullptr;
  }
#endif

  auto* default_storage_partition = context->GetDefaultStoragePartition();
  auto shared_url_loader_factory =
      default_storage_partition->GetURLLoaderFactoryForBrowserProcess();
  auto* local_state = g_browser_process->local_state();
  qorai_vpn::MigrateVPNSettings(user_prefs::UserPrefs::Get(context),
                                local_state);
  auto callback = base::BindRepeating(
      [](content::BrowserContext* context) {
        return skus::SkusServiceFactory::GetForContext(context);
      },
      context);

  // Get the UptimeMonitor from ProcessMiscMetrics
  base::WeakPtr<misc_metrics::UptimeMonitor> uptime_monitor = nullptr;
  if (g_qorai_browser_process &&
      g_qorai_browser_process->process_misc_metrics() &&
      g_qorai_browser_process->process_misc_metrics()->uptime_monitor()) {
    uptime_monitor = g_qorai_browser_process->process_misc_metrics()
                         ->uptime_monitor()
                         ->GetWeakPtr();
  }

  std::unique_ptr<QorAIVpnService> vpn_service =
      std::make_unique<QorAIVpnService>(
          g_qorai_browser_process->qorai_vpn_connection_manager(),
          shared_url_loader_factory, local_state,
          user_prefs::UserPrefs::Get(context), uptime_monitor, callback);
#if BUILDFLAG(IS_WIN)
  vpn_service->set_delegate(std::make_unique<QorAIVPNServiceDelegateWin>());
  if (auto* wg_observer_service =
          qorai_vpn::QorAIVpnWireguardObserverFactory::GetInstance()
              ->GetServiceForContext(context)) {
    wg_observer_service->Observe(vpn_service.get());
  }
  if (auto* dns_observer_service =
          qorai_vpn::QorAIVpnDnsObserverFactory::GetInstance()
              ->GetServiceForContext(context)) {
    dns_observer_service->Observe(vpn_service.get());
  }
#endif

  return vpn_service;
}

}  // namespace

// static
QorAIVpnServiceFactory* QorAIVpnServiceFactory::GetInstance() {
  static base::NoDestructor<QorAIVpnServiceFactory> instance;
  return instance.get();
}

#if BUILDFLAG(IS_ANDROID)
// static
mojo::PendingRemote<qorai_vpn::mojom::ServiceHandler>
QorAIVpnServiceFactory::GetRemoteForProfile(Profile* profile) {
  auto* service = static_cast<QorAIVpnService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));

  if (!service) {
    return mojo::PendingRemote<qorai_vpn::mojom::ServiceHandler>();
  }

  return service->MakeRemote();
}
#endif  // BUILDFLAG(IS_ANDROID)

// static
QorAIVpnService* QorAIVpnServiceFactory::GetForProfile(Profile* profile) {
  return static_cast<QorAIVpnService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

// static
void QorAIVpnServiceFactory::BindForContext(
    content::BrowserContext* context,
    mojo::PendingReceiver<qorai_vpn::mojom::ServiceHandler> receiver) {
  auto* service = static_cast<QorAIVpnService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
  if (service) {
    service->BindInterface(std::move(receiver));
  }
}

QorAIVpnServiceFactory::QorAIVpnServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "QorAIVpnService",
          BrowserContextDependencyManager::GetInstance()) {
  DependsOn(skus::SkusServiceFactory::GetInstance());
#if BUILDFLAG(IS_WIN)
  DependsOn(qorai_vpn::QorAIVpnWireguardObserverFactory::GetInstance());
  DependsOn(qorai_vpn::QorAIVpnDnsObserverFactory::GetInstance());
#endif
}

QorAIVpnServiceFactory::~QorAIVpnServiceFactory() = default;

std::unique_ptr<KeyedService>
QorAIVpnServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  return BuildVpnService(context);
}

// static
BrowserContextKeyedServiceFactory::TestingFactory
QorAIVpnServiceFactory::GetDefaultFactory() {
  return base::BindRepeating(&BuildVpnService);
}

void QorAIVpnServiceFactory::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  qorai_vpn::RegisterProfilePrefs(registry);
}

}  // namespace qorai_vpn
