/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_observer_factory_win.h"

#include <memory>

#include "base/check.h"
#include "base/feature_list.h"
#include "base/no_destructor.h"
#include "qorai/browser/qorai_vpn/vpn_utils.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_observer_service_win.h"
#include "chrome/browser/browser_process.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "content/public/browser/browser_context.h"

namespace qorai_vpn {

// static
QoraiVpnWireguardObserverFactory*
QoraiVpnWireguardObserverFactory::GetInstance() {
  static base::NoDestructor<QoraiVpnWireguardObserverFactory> instance;
  return instance.get();
}

QoraiVpnWireguardObserverFactory::~QoraiVpnWireguardObserverFactory() = default;

QoraiVpnWireguardObserverFactory::QoraiVpnWireguardObserverFactory()
    : BrowserContextKeyedServiceFactory(
          "QoraiVpnWireguardObserverService",
          BrowserContextDependencyManager::GetInstance()) {}

std::unique_ptr<KeyedService>
QoraiVpnWireguardObserverFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  return std::make_unique<QoraiVpnWireguardObserverService>();
}

// static
QoraiVpnWireguardObserverService*
QoraiVpnWireguardObserverFactory::GetServiceForContext(
    content::BrowserContext* context) {
  DCHECK(qorai_vpn::IsAllowedForContext(context));
  return static_cast<QoraiVpnWireguardObserverService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

}  // namespace qorai_vpn
