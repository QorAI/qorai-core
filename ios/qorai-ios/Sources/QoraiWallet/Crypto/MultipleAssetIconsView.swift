// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import SwiftUI

struct MultipleAssetIconsView: View {

  let tokens: [QoraiWallet.BlockchainToken]
  let maxBlockies = 3
  @ScaledMetric var iconSize = 24
  var maxIconSize: CGFloat = 32
  @ScaledMetric var blockieDotSize = 2.0

  var body: some View {
    MultipleCircleIconView(
      models: tokens,
      shape: .circle,
      iconSize: iconSize,
      maxIconSize: maxIconSize,
      iconDotSize: blockieDotSize
    ) { token in
      AssetIcon(
        token: token,
        network: nil  // not shown
      )
    }
  }
}
