// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiShared
import QoraiUI
import DesignSystem
import Shared
import SwiftUI

public struct VPNLinkReceiptView: View {
  @Environment(\.presentationMode) @Binding private var presentationMode

  private let dynamicTypeRange = (...DynamicTypeSize.xLarge)

  public var linkReceiptAction: (() -> Void)?

  public init() {}

  public var body: some View {
    VStack(spacing: 24) {
      Image("link_receipt_image", bundle: .module)
        .resizable()
        .aspectRatio(contentMode: .fit)
        .accessibilityHidden(true)
      Text(Strings.Onboarding.linkReceiptTitle)
        .font(.title.weight(.medium))
        .multilineTextAlignment(.center)
      Text(Strings.Onboarding.linkReceiptDescription)
        .font(.subheadline)
        .multilineTextAlignment(.center)

      Button {
        linkReceiptAction?()
        presentationMode.dismiss()
      } label: {
        Text(Strings.Onboarding.linkReceiptButton)
      }
      .buttonStyle(QoraiFilledButtonStyle(size: .large))

      HStack(spacing: 8) {
        Text(Strings.VPN.poweredBy)
          .font(.footnote)
          .foregroundColor(Color(.qoraiPrimary))
          .multilineTextAlignment(.center)
        Image(sharedName: "vpn_brand")
          .renderingMode(.template)
          .foregroundColor(Color(.qoraiPrimary))
          .accessibilityHidden(true)
      }
    }
    .frame(maxWidth: QoraiUX.baseDimensionValue)
    .padding(32)
    .background(Color(.qoraiBackground))
    .dynamicTypeSize(dynamicTypeRange)
    .overlay {
      Button {
        presentationMode.dismiss()
      } label: {
        Image(qoraiSystemName: "qora.close")
          .renderingMode(.template)
          .dynamicTypeSize(dynamicTypeRange)
          .foregroundColor(Color(.qoraiPrimary))
      }
      .frame(maxWidth: .infinity, maxHeight: .infinity, alignment: .topTrailing)
      .padding([.top, .trailing], 20)
    }
  }
}

#if DEBUG
struct VPNLinkReceiptView_Previews: PreviewProvider {
  static var previews: some View {
    VPNLinkReceiptView()
  }
}
#endif
