// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Strings
import SwiftUI

extension Text {
  /// Creates a text view that displays a URLOrigin, bolding the eTLD+1.
  init(urlOrigin: URLOrigin) {
    if urlOrigin == WalletConstants.qoraiWalletOrigin {
      self = Text(Strings.Wallet.qoraiWallet)
    } else {
      let origin = urlOrigin.url?.absoluteString ?? ""
      let eTldPlusOne = urlOrigin.url?.baseDomain ?? ""
      if let range = origin.range(of: eTldPlusOne) {
        let originStart = origin[origin.startIndex..<range.lowerBound]
        let etldPlusOne = origin[range.lowerBound..<range.upperBound]
        let originEnd = origin[range.upperBound...]
        self =
          Text(String(originStart).zwspOutput) + Text(etldPlusOne).bold()
          + Text(String(originEnd).zwspOutput)
      } else {
        self = Text(origin)
      }
    }
  }

  /// Creates a text view that displays a QoraiWallet.OriginInfo, bolding the eTLD+1.
  init(originInfo: QoraiWallet.OriginInfo) {
    // Internal Transaction from Qorai:
    // originInfo.eTldPlusOne=""
    // originInfo.originSpec="chrome://wallet"
    // From Uniswap:
    // originInfo.eTldPlusOne="uniswap.org"
    // originInfo.originSpec="https://app.uniswap.org"
    if originInfo.isQoraiWalletOrigin {
      self = Text(Strings.Wallet.qoraiWallet)
    } else {
      let origin = originInfo.originSpec
      let eTldPlusOne = originInfo.eTldPlusOne
      if let range = origin.range(of: eTldPlusOne) {
        let originStart = origin[origin.startIndex..<range.lowerBound]
        let etldPlusOne = origin[range.lowerBound..<range.upperBound]
        let originEnd = origin[range.upperBound...]
        self =
          Text(String(originStart).zwspOutput) + Text(etldPlusOne).bold()
          + Text(String(originEnd).zwspOutput)
      } else {
        self = Text(origin)
      }
    }
  }
}
