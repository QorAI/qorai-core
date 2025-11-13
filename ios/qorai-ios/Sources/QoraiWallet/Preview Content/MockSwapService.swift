// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation

#if DEBUG

class MockSwapService: QoraiWalletSwapService {
  func liFiStatus(
    txHash: String,
    completion: @escaping (QoraiWallet.LiFiStatus?, QoraiWallet.LiFiError?, String) -> Void
  ) {
    completion(.none, .init(message: "Error", code: .defaultError), "Error")
  }

  func isSwapSupported(chainId: String, completion: @escaping (Bool) -> Void) {
    completion(true)
  }

  func transaction(
    params: QoraiWallet.SwapTransactionParamsUnion,
    completion: @escaping (QoraiWallet.SwapTransactionUnion?, QoraiWallet.SwapErrorUnion?, String)
      -> Void
  ) {
    completion(
      .init(
        zeroExTransaction: .init(
          to: "",
          data: "",
          gas: "",
          gasPrice: "",
          value: ""
        )
      ),
      nil,
      ""
    )
  }

  func quote(
    params: QoraiWallet.SwapQuoteParams,
    completion: @escaping (
      QoraiWallet.SwapQuoteUnion?, QoraiWallet.SwapFees?, QoraiWallet.SwapErrorUnion?, String
    ) -> Void
  ) {
    completion(nil, nil, nil, "Error Message")
  }
}

#endif
