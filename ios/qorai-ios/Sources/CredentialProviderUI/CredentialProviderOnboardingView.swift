// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

import QoraiUI
import DesignSystem
import Foundation
import Strings
import SwiftUI

public struct CredentialProviderOnboardingView: View {
  public var action: () -> Void
  public init(action: @escaping () -> Void) {
    self.action = action
  }
  public var body: some View {
    VStack(spacing: 40) {
      Image(sharedName: "qorai.logo")
        .resizable()
        .aspectRatio(contentMode: .fit)
        .frame(height: 120)
      VStack {
        VStack(spacing: 12) {
          Text(Strings.CredentialProvider.onboardingViewTitle)
            .font(.title.bold())
            .foregroundColor(Color(qoraiSystemName: .textPrimary))
          Text(Strings.CredentialProvider.onboardingViewSubtitle)
            .font(.subheadline)
            .foregroundColor(Color(qoraiSystemName: .textSecondary))
          Text(Strings.CredentialProvider.onboardingViewFootnote)
            .font(.footnote)
            .foregroundColor(Color(qoraiSystemName: .textTertiary))
        }
        .multilineTextAlignment(.center)
        .padding(.horizontal)
        Spacer()
        Button {
          action()
        } label: {
          Text(Strings.CredentialProvider.onboardingViewContinueCTA)
            .frame(maxWidth: .infinity)
        }
        .buttonStyle(QoraiFilledButtonStyle(size: .large))
      }
    }
    .padding(.horizontal, 20)
    .padding(.vertical, 40)
    .background(Color(qoraiSystemName: .containerBackground))
  }
}

#if DEBUG
#Preview {
  CredentialProviderOnboardingView(action: {})
}
#endif
