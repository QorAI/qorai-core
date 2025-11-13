/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_IPFS_SERVICE_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_IPFS_SERVICE_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

#include "base/memory/raw_ptr.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/prefs/pref_service.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver_set.h"

namespace qorai_wallet {

class QoraiWalletIpfsService : public KeyedService, public mojom::IpfsService {
 public:
  explicit QoraiWalletIpfsService(PrefService* pref_service);
  ~QoraiWalletIpfsService() override;

  QoraiWalletIpfsService(const QoraiWalletIpfsService&) = delete;
  QoraiWalletIpfsService& operator=(const QoraiWalletIpfsService&) = delete;

  mojo::PendingRemote<mojom::IpfsService> MakeRemote();
  void Bind(mojo::PendingReceiver<mojom::IpfsService> receiver);

  void TranslateToGatewayURL(const std::string& url,
                             TranslateToGatewayURLCallback callback) override;

  void ContentHashToCIDv1URL(const std::vector<uint8_t>& content_hash,
                             ContentHashToCIDv1URLCallback callback) override;

 private:
  mojo::ReceiverSet<mojom::IpfsService> receivers_;

  raw_ptr<PrefService> pref_service_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_IPFS_SERVICE_H_
