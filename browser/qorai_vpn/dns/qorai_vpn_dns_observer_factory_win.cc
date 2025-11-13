/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/dns/qorai_vpn_dns_observer_factory_win.h"

#include <cstddef>
#include <memory>
#include <string>

#include "base/check.h"
#include "base/feature_list.h"
#include "base/no_destructor.h"
#include "qorai/browser/qorai_vpn/dns/qorai_vpn_dns_observer_service_win.h"
#include "qorai/browser/qorai_vpn/vpn_utils.h"
#include "qorai/components/qorai_vpn/common/features.h"
#include "qorai/components/qorai_vpn/common/pref_names.h"
#include "chrome/browser/browser_process.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_context.h"

namespace qorai_vpn {

// static
QoraiVpnDnsObserverFactory* QoraiVpnDnsObserverFactory::GetInstance() {
  static base::NoDestructor<QoraiVpnDnsObserverFactory> instance;
  return instance.get();
}

QoraiVpnDnsObserverFactory::~QoraiVpnDnsObserverFactory() = default;

QoraiVpnDnsObserverFactory::QoraiVpnDnsObserverFactory()
    : BrowserContextKeyedServiceFactory(
          "QoraiVpnDNSObserverService",
          BrowserContextDependencyManager::GetInstance()) {}

std::unique_ptr<KeyedService>
QoraiVpnDnsObserverFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  return std::make_unique<QoraiVpnDnsObserverService>(
      g_browser_process->local_state(), user_prefs::UserPrefs::Get(context));
}

// static
QoraiVpnDnsObserverService* QoraiVpnDnsObserverFactory::GetServiceForContext(
    content::BrowserContext* context) {
  if (!base::FeatureList::IsEnabled(
          qorai_vpn::features::kQoraiVPNDnsProtection)) {
    return nullptr;
  }
  DCHECK(qorai_vpn::IsAllowedForContext(context));
  return static_cast<QoraiVpnDnsObserverService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

void QoraiVpnDnsObserverFactory::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(prefs::kQoraiVpnShowDNSPolicyWarningDialog,
                                true);
}

}  // namespace qorai_vpn
