/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_QORAI_VPN_SERVICE_FACTORY_H_
#define QORAI_BROWSER_QORAI_VPN_QORAI_VPN_SERVICE_FACTORY_H_

#include <memory>

#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"
#include "build/build_config.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#if BUILDFLAG(IS_ANDROID)
#include "mojo/public/cpp/bindings/pending_remote.h"
#endif  // BUILDFLAG(IS_ANDROID)

class Profile;

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace qorai_vpn {

class QorAIVpnService;

class QorAIVpnServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  static QorAIVpnService* GetForProfile(Profile* profile);
#if BUILDFLAG(IS_ANDROID)
  static mojo::PendingRemote<qorai_vpn::mojom::ServiceHandler>
  GetRemoteForProfile(Profile* profile);
#endif  // BUILDFLAG(IS_ANDROID)
  static QorAIVpnServiceFactory* GetInstance();

  QorAIVpnServiceFactory(const QorAIVpnServiceFactory&) = delete;
  QorAIVpnServiceFactory& operator=(const QorAIVpnServiceFactory&) = delete;

  static void BindForContext(
      content::BrowserContext* context,
      mojo::PendingReceiver<qorai_vpn::mojom::ServiceHandler> receiver);

  // Returns the default factory, useful in tests.
  static TestingFactory GetDefaultFactory();

 private:
  friend base::NoDestructor<QorAIVpnServiceFactory>;

  QorAIVpnServiceFactory();
  ~QorAIVpnServiceFactory() override;

  // BrowserContextKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) override;
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_QORAI_VPN_SERVICE_FACTORY_H_
