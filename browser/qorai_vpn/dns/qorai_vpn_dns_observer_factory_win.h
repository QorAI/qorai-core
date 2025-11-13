/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_DNS_QORAI_VPN_DNS_OBSERVER_FACTORY_WIN_H_
#define QORAI_BROWSER_QORAI_VPN_DNS_QORAI_VPN_DNS_OBSERVER_FACTORY_WIN_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace content {
class BrowserContext;
}  // namespace content

namespace user_prefs {
class PrefRegistrySyncable;
}  // namespace user_prefs

namespace qorai_vpn {

class QoraiVpnDnsObserverService;

class QoraiVpnDnsObserverFactory : public BrowserContextKeyedServiceFactory {
 public:
  QoraiVpnDnsObserverFactory(const QoraiVpnDnsObserverFactory&) = delete;
  QoraiVpnDnsObserverFactory& operator=(const QoraiVpnDnsObserverFactory&) =
      delete;

  static QoraiVpnDnsObserverFactory* GetInstance();
  static QoraiVpnDnsObserverService* GetServiceForContext(
      content::BrowserContext* context);
  void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) override;

 private:
  friend base::NoDestructor<QoraiVpnDnsObserverFactory>;

  QoraiVpnDnsObserverFactory();
  ~QoraiVpnDnsObserverFactory() override;

  // BrowserContextKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_DNS_QORAI_VPN_DNS_OBSERVER_FACTORY_WIN_H_
