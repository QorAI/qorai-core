// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation

#if DEBUG

class MockTxService: QoraiWalletTxService {
  private let txs: [QoraiWallet.TransactionInfo] = [
    .previewConfirmedERC20Approve,
    .previewConfirmedSend,
    .previewConfirmedSwap,
  ]

  func transactionInfo(
    coinType: QoraiWallet.CoinType,
    txMetaId: String,
    completion: @escaping (QoraiWallet.TransactionInfo?) -> Void
  ) {
    completion(txs.first(where: { $0.id == txMetaId }))
  }

  func addUnapprovedTransaction(
    txDataUnion: QoraiWallet.TxDataUnion,
    chainId: String,
    from: QoraiWallet.AccountId,
    completion: @escaping (Bool, String, String) -> Void
  ) {
    completion(true, "txMetaId", "")
  }

  func addUnapprovedEvmTransaction(
    params: QoraiWallet.NewEvmTransactionParams,
    completion: @escaping (Bool, String, String) -> Void
  ) {
    completion(true, "txMetaId", "")
  }

  func addUnapprovedBitcoinTransaction(
    params: QoraiWallet.NewBitcoinTransactionParams,
    completion: @escaping (Bool, String, String) -> Void
  ) {
    completion(true, "txMetaId", "")
  }

  func addUnapprovedZCashTransaction(
    params: QoraiWallet.NewZCashTransactionParams,
    completion: @escaping (Bool, String, String) -> Void
  ) {
    completion(true, "txMetaId", "")
  }

  func addUnapprovedCardanoTransaction(
    params: QoraiWallet.NewCardanoTransactionParams,
    completion: @escaping (Bool, String, String) -> Void
  ) {
    completion(true, "txMetaId", "")
  }

  func rejectTransaction(
    coinType: QoraiWallet.CoinType,
    chainId: String,
    txMetaId: String,
    completion: @escaping (Bool) -> Void
  ) {
  }

  func allTransactionInfo(
    coinType: QoraiWallet.CoinType,
    chainId: String?,
    from: QoraiWallet.AccountId?,
    completion: @escaping ([QoraiWallet.TransactionInfo]) -> Void
  ) {
    completion(
      txs.map { tx in
        tx.txStatus = .unapproved
        return tx
      }
    )
  }

  func addObserver(_ observer: QoraiWalletTxServiceObserver) {
  }

  func speedupOrCancelTransaction(
    coinType: QoraiWallet.CoinType,
    chainId: String,
    txMetaId: String,
    cancel: Bool,
    completion: @escaping (Bool, String, String) -> Void
  ) {
    completion(false, "", "Error Message")
  }

  func retryTransaction(
    coinType: QoraiWallet.CoinType,
    chainId: String,
    txMetaId: String,
    completion: @escaping (Bool, String, String) -> Void
  ) {
    completion(false, "", "Error Message")
  }

  func pendingTransactionsCount(completion: @escaping (UInt32) -> Void) {
    completion(UInt32(txs.count))
  }

  func reset() {
  }

  func approveTransaction(
    coinType: QoraiWallet.CoinType,
    chainId: String,
    txMetaId: String,
    completion: @escaping (Bool, QoraiWallet.ProviderErrorUnion, String) -> Void
  ) {
    completion(false, .init(providerError: .internalError), "Error Message")
  }
}

#endif
