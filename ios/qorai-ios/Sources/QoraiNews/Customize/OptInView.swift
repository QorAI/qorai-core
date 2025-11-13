// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStrings
import QoraiUI
import DesignSystem
import Foundation
import Lottie
import SwiftUI

struct OptInView: View {
  var tappedTurnOn: @Sendable () async throws -> Void
  var tappedLearnMore: () -> Void

  @State private var isLoading: Bool = false

  var body: some View {
    VStack(spacing: 36) {
      Image("opt-in-news-graphic", bundle: .module)
        .resizable()
        .aspectRatio(contentMode: .fit)
        .padding(.horizontal)
      VStack(spacing: 12) {
        Text(Strings.QoraiNews.introCardTitle)
          .font(.title3.bold())
          .multilineTextAlignment(.center)
          .foregroundColor(Color(.qoraiPrimary))
        Text(Strings.QoraiNews.introCardBody)
          .font(.subheadline)
          .multilineTextAlignment(.center)
          .foregroundColor(Color(.qoraiLabel))
      }
      VStack(spacing: 16) {
        Button {
          isLoading = true
          Task {
            try await tappedTurnOn()
            isLoading = false
          }
        } label: {
          Text(Strings.QoraiNews.turnOnQoraiNews)
            .opacity(isLoading ? 0 : 1)
            .overlay(
              ProgressView()
                .progressViewStyle(.qoraiCircular(size: .small, tint: .white))
                .opacity(isLoading ? 1 : 0)
            )
            .animation(.default, value: isLoading)
        }
        .buttonStyle(QoraiFilledButtonStyle(size: .large))
        Button(action: tappedLearnMore) {
          Text(Strings.QoraiNews.learnMoreTitle)
            .font(.subheadline.weight(.semibold))
            .foregroundColor(Color(.qoraiBlurpleTint))
        }
      }
    }
    .padding()
    .accessibilityEmbedInScrollView()
  }
}

#if DEBUG
struct OptInView_PreviewProvider: PreviewProvider {
  static var previews: some View {
    OptInView(
      tappedTurnOn: {
        try await Task.sleep(nanoseconds: NSEC_PER_SEC * 2)
      },
      tappedLearnMore: {}
    )
  }
}
#endif
