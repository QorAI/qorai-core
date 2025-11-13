/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_OBSERVER_FACTORY_WIN_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_OBSERVER_FACTORY_WIN_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace content {
class BrowserContext;
}  // namespace content

namespace qorai_vpn {

class QoraiVpnWireguardObserverService;

class QoraiVpnWireguardObserverFactory
    : public BrowserContextKeyedServiceFactory {
 public:
  QoraiVpnWireguardObserverFactory(const QoraiVpnWireguardObserverFactory&) =
      delete;
  QoraiVpnWireguardObserverFactory& operator=(
      const QoraiVpnWireguardObserverFactory&) = delete;

  static QoraiVpnWireguardObserverFactory* GetInstance();
  static QoraiVpnWireguardObserverService* GetServiceForContext(
      content::BrowserContext* context);

 private:
  friend base::NoDestructor<QoraiVpnWireguardObserverFactory>;

  QoraiVpnWireguardObserverFactory();
  ~QoraiVpnWireguardObserverFactory() override;

  // BrowserContextKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_OBSERVER_FACTORY_WIN_H_
