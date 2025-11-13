// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStrings
import QoraiUI
import Shared
import SwiftUI

public struct OnboardingBottomBarView: View {
  public var dismiss: (() -> Void)?
  public var switchBottomBar: (() -> Void)?

  public init() {}

  public var body: some View {
    VStack {
      Button {
        dismiss?()
      } label: {
        Image(qoraiSystemName: "qora.close")
          .renderingMode(.template)
          .foregroundColor(Color(.qoraiPrimary))
      }
      .frame(maxWidth: .infinity, alignment: .trailing)
      VStack(spacing: 24) {
        Image("bottom-bar-logo-bottom", bundle: .module)
          .aspectRatio(contentMode: .fit)
        Text(Strings.Callout.bottomBarCalloutTitle)
          .font(.title2.weight(.semibold))
          .foregroundColor(Color(.qoraiPrimary))
          .multilineTextAlignment(.center)
        Text(Strings.Callout.bottomBarCalloutDescription)
          .font(.body)
          .multilineTextAlignment(.center)
          .foregroundColor(Color(.qoraiPrimary))
          .padding(.horizontal, 16)
      }
      .padding(.bottom, 16)
      Button {
        switchBottomBar?()
      } label: {
        Text(Strings.Callout.bottomBarCalloutButtonTitle)
          .frame(maxWidth: .infinity, maxHeight: .infinity)
          .font(.title3.weight(.medium))
          .padding()
      }
      .frame(height: 44)
      .background(Color(.qoraiBlurple))
      .accentColor(Color(.white))
      .clipShape(Capsule())
      .padding(.horizontal, 16)
      Button {
        dismiss?()
      } label: {
        Text(Strings.Callout.bottomBarCalloutDismissButtonTitle)
          .frame(maxWidth: .infinity, maxHeight: .infinity)
          .font(.title3.weight(.medium))
          .foregroundColor(Color(.qoraiPrimary))
      }
      .frame(height: 44)
      .background(Color(.clear))
      .accentColor(Color(.white))
    }
    .frame(maxWidth: QoraiUX.baseDimensionValue)
    .padding()
    .background(Color(.qoraiBackground))
    .accessibilityEmbedInScrollView()
  }
}

#if DEBUG
struct OnboardingBottomBarView_Previews: PreviewProvider {
  static var previews: some View {
    Group {
      QoraiUI.PopupView {
        OnboardingBottomBarView()
      }
      .previewDevice("iPhone 12 Pro")

      QoraiUI.PopupView {
        OnboardingBottomBarView()
      }
      .previewDevice("iPad Pro (9.7-inch)")
    }
  }
}
#endif
