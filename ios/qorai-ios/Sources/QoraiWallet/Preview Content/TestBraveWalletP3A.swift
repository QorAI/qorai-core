// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore

#if DEBUG

class TestQoraiWalletP3A: QoraiWalletQoraiWalletP3A {
  var _reportProvider:
    (
      (
        _ providerType: QoraiWallet.JSProviderType, _ coinType: QoraiWallet.CoinType,
        _ allowProviderOverwrite: Bool
      ) -> Void
    )?
  func reportJsProvider(
    providerType: QoraiWallet.JSProviderType,
    coinType: QoraiWallet.CoinType,
    allowProviderOverwrite: Bool
  ) {
    _reportProvider?(providerType, coinType, allowProviderOverwrite)
  }

  var _reportOnboarding: ((_ onboardingAction: QoraiWallet.OnboardingAction) -> Void)?
  func reportOnboardingAction(_ onboardingAction: QoraiWallet.OnboardingAction) {
    _reportOnboarding?(onboardingAction)
  }

  var _reportTransactionSent: ((_ coin: QoraiWallet.CoinType, _ newSend: Bool) -> Void)?
  func reportTransactionSent(coin: QoraiWallet.CoinType, newSend: Bool) {
    _reportTransactionSent?(coin, newSend)
  }

  var _recordActiveWalletCount: ((_ count: Int32, _ coinType: QoraiWallet.CoinType) -> Void)?
  func recordActiveWalletCount(_ count: Int32, coinType: QoraiWallet.CoinType) {
    _recordActiveWalletCount?(count, coinType)
  }

  var _recordNftGalleryView: ((_ nftCount: Int32) -> Void)?
  func recordNftGalleryView(nftCount: Int32) {
    _recordNftGalleryView?(nftCount)
  }
}

#endif
