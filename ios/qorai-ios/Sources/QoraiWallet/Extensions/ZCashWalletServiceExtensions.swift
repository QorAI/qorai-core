// Copyright 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore

extension QoraiWalletZCashWalletService {
  /// - Parameters:
  ///     - accounts: A list of `QoraiWallet.AccountInfo`
  ///
  /// - Returns: A dictionary of `QoraiWallet.AccountInfo.uniqueKey` as key and associated `QoraiWallet.ZCashAccountInfo`
  func fetchZcashAccountInfo(
    accounts: [QoraiWallet.AccountInfo]
  ) async -> [String: QoraiWallet.ZCashAccountInfo] {
    await withTaskGroup(
      of: [String: QoraiWallet.ZCashAccountInfo].self,
      body: { group in
        for account in accounts {
          group.addTask {
            guard account.coin == .zec, account.address.isEmpty else { return [:] }
            if let zcashAccount = await self.zCashAccountInfo(accountId: account.accountId) {
              return [account.accountId.uniqueKey: zcashAccount]
            }
            return [:]
          }
        }
        return await group.reduce(
          into: [String: QoraiWallet.ZCashAccountInfo](),
          { partialResult, new in
            partialResult.merge(with: new)
          }
        )
      }
    )
  }

  /// Fetch all bitcoin balance types (total, available, pending) for a given account.
  /// - Parameters:
  ///     - accountId: The `QoraiWallet.AccountId` for the account
  /// - Returns: The BTC balances of the given `QoraiWallet.AccountId` in `Double`; Will return a nil if there is an issue fetching balance.
  func fetchZECTransparentBalances(
    accountId: QoraiWallet.AccountId
  ) async -> Double? {
    let (zecBalance, _) = await self.balance(accountId: accountId)

    guard
      let balance = zecBalance?.transparentBalance
    else {
      return nil
    }

    return Double(balance) / 100_000_000
  }
}
