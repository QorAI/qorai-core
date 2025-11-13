// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import DesignSystem
import SwiftUI

enum SubscriptionActionType {
  case refreshCredentials, redeemPromoCode

  var mainTitle: String {
    switch self {
    case .refreshCredentials:
      return Strings.Paywall.alreadyPurchasedTitle
    case .redeemPromoCode:
      return Strings.Paywall.havePromoCodeTitle
    }
  }

  var actionTitle: String {
    switch self {
    case .refreshCredentials:
      return Strings.Paywall.refreshCredentialsButtonTitle
    case .redeemPromoCode:
      return Strings.Paywall.redeemPromoCodeButtonTitle
    }
  }
}

struct QoraiVPNSubscriptionActionView: View {

  let refreshCredentials: () -> Void
  let redeedPromoCode: () -> Void
  let learnMore: () -> Void

  var body: some View {
    VStack(spacing: 16) {
      Button(action: learnMore) {
        Text(Strings.Paywall.qoraiVPNLearnMoreButtonTitle)
          .frame(maxWidth: .infinity)
      }
      .buttonStyle(
        QoraiFilledButtonStyle(
          size: .init(
            font: .subheadline.weight(.semibold),
            padding: .init(top: 12, leading: 12, bottom: 12, trailing: 12),
            radius: 12,
            minHeight: 20
          )
        )
      )

      QoraiVPNTitleActionsView(
        actionType: .refreshCredentials,
        action: refreshCredentials
      )

      QoraiVPNTitleActionsView(
        actionType: .redeemPromoCode,
        action: redeedPromoCode
      )
    }
    .padding(.vertical)
  }
}

struct QoraiVPNTitleActionsView: View {
  let actionType: SubscriptionActionType
  let action: () -> Void

  var body: some View {
    VStack(spacing: 10) {
      Text(actionType.mainTitle)
        .font(.subheadline)
        .foregroundColor(Color(qoraiSystemName: .primitiveBlurple98))
      Button(
        action: action,
        label: {
          Text(actionType.actionTitle)
            .font(.subheadline.weight(.semibold))
            .foregroundColor(Color(.white))
            .padding()
            .frame(maxWidth: .infinity)
            .overlay(
              RoundedRectangle(cornerRadius: 8)
                .stroke(Color(qoraiSystemName: .dividerInteractive), lineWidth: 1)
            )
        }
      )
    }
  }
}

#if DEBUG
struct QoraiVPNRefreshCredentialsView_Previews: PreviewProvider {
  static var previews: some View {

    QoraiVPNSubscriptionActionView(
      refreshCredentials: {},
      redeedPromoCode: {},
      learnMore: {}
    )
    .background(
      Color(qoraiSystemName: .primitivePrimary10)
    )
  }
}
#endif
