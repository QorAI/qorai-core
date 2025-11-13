// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import DesignSystem
import SwiftUI

public struct AIChatTermsAndConditionsView: View {
  @Environment(\.dismiss)
  private var dismiss

  @Binding
  var termsAndConditionsAccepted: Bool

  public var body: some View {
    VStack {
      ScrollView {
        LazyVStack(spacing: 16.0) {
          Text(Strings.AIChat.termsConditionsTitle)
            .multilineTextAlignment(.leading)
            .frame(maxWidth: .infinity, alignment: .leading)
            .fixedSize(horizontal: false, vertical: true)
            .font(.headline)
            .foregroundStyle(Color(qoraiSystemName: .textPrimary))

          Text(
            LocalizedStringKey(
              String.localizedStringWithFormat(
                Strings.AIChat.termsConditionsDescription,
                AIChatConstants.qoraiQoraLearnMore.absoluteString,
                AIChatConstants.qoraiQoraPrivacyPolicyURL.absoluteString
              )
            )
          )
          .multilineTextAlignment(.leading)
          .frame(maxWidth: .infinity, alignment: .leading)
          .fixedSize(horizontal: false, vertical: true)
          .foregroundStyle(Color(qoraiSystemName: .textPrimary))
          .tint(Color(qoraiSystemName: .primary50))
        }
        .padding()
      }

      Button(
        action: {
          termsAndConditionsAccepted = true
        },
        label: {
          Text(Strings.AIChat.termsConditionsApprovalActionTitle)
            .font(.subheadline.weight(.semibold))
            .padding([.top, .bottom], 12)
            .padding([.leading, .trailing], 16)
            .frame(maxWidth: .infinity)
            .foregroundStyle(Color(qoraiSystemName: .schemesOnPrimary))
            .background(Color(qoraiSystemName: .buttonBackground), in: .capsule)
        }
      )
      .buttonStyle(.plain)
      .padding(16.0)
    }
  }
}

#if DEBUG
struct AIChatTermsAndConditionsView_Preview: PreviewProvider {
  static var previews: some View {
    AIChatTermsAndConditionsView(termsAndConditionsAccepted: .constant(false))
      .previewColorSchemes()
      .previewLayout(.sizeThatFits)
  }
}
#endif
