/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_WALLET_NOTIFICATIONS_WALLET_NOTIFICATION_SERVICE_H_
#define QORAI_BROWSER_QORAI_WALLET_NOTIFICATIONS_WALLET_NOTIFICATION_SERVICE_H_

#include <string>

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "components/keyed_service/core/keyed_service.h"
#include "mojo/public/cpp/bindings/receiver.h"

namespace content {
class BrowserContext;
}  // namespace content

namespace qorai_wallet {
class QorAIWalletService;

class WalletNotificationService : public KeyedService,
                                  public mojom::TxServiceObserver {
 public:
  WalletNotificationService(QorAIWalletService* qorai_wallet_service,
                            content::BrowserContext* context);
  ~WalletNotificationService() override;
  WalletNotificationService(const WalletNotificationService&) = delete;
  WalletNotificationService operator=(const WalletNotificationService&) =
      delete;

  // mojom::TxServiceObserver
  void OnNewUnapprovedTx(mojom::TransactionInfoPtr tx_info) override {}
  void OnUnapprovedTxUpdated(mojom::TransactionInfoPtr tx_info) override {}
  void OnTransactionStatusChanged(mojom::TransactionInfoPtr tx_info) override;
  void OnTxServiceReset() override {}

 private:
  friend class WalletNotificationServiceUnitTest;

  bool ShouldDisplayUserNotification(mojom::TransactionStatus status);
  void DisplayUserNotification(mojom::TransactionStatus status,
                               const std::string& address,
                               const std::string& tx_id);

  raw_ptr<QorAIWalletService> qorai_wallet_service_;
  raw_ptr<content::BrowserContext> context_;
  mojo::Receiver<mojom::TxServiceObserver> tx_observer_receiver_{this};
};

}  // namespace qorai_wallet

#endif  // QORAI_BROWSER_QORAI_WALLET_NOTIFICATIONS_WALLET_NOTIFICATION_SERVICE_H_
