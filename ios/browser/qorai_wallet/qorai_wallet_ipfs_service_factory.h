/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_QORAI_WALLET_QORAI_WALLET_IPFS_SERVICE_FACTORY_H_
#define QORAI_IOS_BROWSER_QORAI_WALLET_QORAI_WALLET_IPFS_SERVICE_FACTORY_H_

#include <memory>

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "ios/chrome/browser/shared/model/profile/profile_keyed_service_factory_ios.h"
#include "mojo/public/cpp/bindings/pending_remote.h"

class ProfileIOS;
class KeyedService;

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace qorai_wallet {

class QoraiWalletIpfsService;

class QoraiWalletIpfsServiceFactory : public ProfileKeyedServiceFactoryIOS {
 public:
  QoraiWalletIpfsServiceFactory(const QoraiWalletIpfsServiceFactory&) = delete;
  QoraiWalletIpfsServiceFactory& operator=(
      const QoraiWalletIpfsServiceFactory&) = delete;

  // Creates the service if it doesn't exist already for |profile|.
  static mojo::PendingRemote<mojom::IpfsService> GetForProfile(
      ProfileIOS* profile);
  static QoraiWalletIpfsService* GetServiceForState(ProfileIOS* profile);

  static QoraiWalletIpfsServiceFactory* GetInstance();

 private:
  friend base::NoDestructor<QoraiWalletIpfsServiceFactory>;

  QoraiWalletIpfsServiceFactory();
  ~QoraiWalletIpfsServiceFactory() override;

  // ProfileKeyedServiceFactoryIOS implementation.
  std::unique_ptr<KeyedService> BuildServiceInstanceFor(
      ProfileIOS* profile) const override;
};

}  // namespace qorai_wallet

#endif  // QORAI_IOS_BROWSER_QORAI_WALLET_QORAI_WALLET_IPFS_SERVICE_FACTORY_H_
