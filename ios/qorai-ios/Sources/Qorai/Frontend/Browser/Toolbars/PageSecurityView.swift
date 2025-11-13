// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiShared
import QoraiUI
import Foundation
import Shared
import SwiftUI
import Web

/// Displays warnings about the pages security
///
/// Currently this is only shown when the page security requires a visible warning on the URL bar
struct PageSecurityView: View {
  var displayURL: String
  var secureState: SecureContentState
  var hasCertificate: Bool
  var presentCertificateViewer: () -> Void

  @Environment(\.pixelLength) private var pixelLength

  @ViewBuilder private var warningIcon: some View {
    switch secureState {
    case .secure, .localhost:
      EmptyView()
    case .unknown:
      Image(qoraiSystemName: "qora.info.filled")
        .foregroundColor(Color(qoraiSystemName: .systemfeedbackWarningIcon))
    case .invalidCertificate, .missingSSL, .mixedContent:
      Image(qoraiSystemName: "qora.warning.triangle-filled")
        .foregroundColor(Color(qoraiSystemName: .systemfeedbackErrorIcon))
    }
  }

  @ViewBuilder private var warningTitle: some View {
    switch secureState {
    case .secure, .localhost:
      EmptyView()
    case .unknown:
      Text(Strings.PageSecurityView.pageUnknownStatusTitle)
        .foregroundColor(Color(qoraiSystemName: .systemfeedbackWarningText))
    case .invalidCertificate, .missingSSL:
      Text(Strings.PageSecurityView.pageNotSecureTitle)
        .foregroundColor(Color(qoraiSystemName: .systemfeedbackErrorText))
    case .mixedContent:
      Text(Strings.PageSecurityView.pageNotFullySecureTitle)
        .foregroundColor(Color(qoraiSystemName: .systemfeedbackErrorText))
    }
  }

  private var warningBody: String {
    switch secureState {
    case .secure, .localhost:
      return ""
    case .unknown:
      return Strings.PageSecurityView.pageUnknownStatusWarning
    case .invalidCertificate, .missingSSL, .mixedContent:
      return Strings.PageSecurityView.pageNotSecureDetailedWarning
    }
  }

  var body: some View {
    VStack(alignment: .leading, spacing: 0) {
      VStack(alignment: .leading, spacing: 16) {
        URLElidedText(text: displayURL)
          .font(.headline)
          .foregroundStyle(Color(qoraiSystemName: .textPrimary))
          .frame(maxWidth: .infinity, alignment: .leading)
          .fixedSize(horizontal: false, vertical: true)

        HStack(alignment: .firstTextBaseline) {
          warningIcon
          VStack(alignment: .leading, spacing: 4) {
            warningTitle
            Text(warningBody)
              .foregroundColor(Color(qoraiSystemName: .textTertiary))
              .font(.footnote)
          }
        }
      }
      .multilineTextAlignment(.leading)
      .font(.subheadline)
      .padding()
      if hasCertificate {
        Color(qoraiSystemName: .dividerSubtle)
          .frame(height: pixelLength)
        Button {
          presentCertificateViewer()
        } label: {
          HStack(alignment: .firstTextBaseline) {
            Label(
              Strings.PageSecurityView.viewCertificateButtonTitle,
              qoraiSystemImage: "qora.lock.plain"
            )
            Spacer()
            Image(qoraiSystemName: "qora.carat.right")
              .imageScale(.large)
          }
          .font(.subheadline)
          .foregroundColor(Color(qoraiSystemName: .textInteractive))
          .padding()
        }
      }
    }
    .background(Color(.qoraiBackground))
    .frame(maxWidth: QoraiUX.baseDimensionValue, alignment: .leading)
    #if DEBUG
    .onAppear {
      assert(
        secureState.shouldDisplayWarning,
        "Currently only supports displaying insecure warnings"
      )
    }
    #endif
  }
}

extension PageSecurityView: PopoverContentComponent {
  var popoverBackgroundColor: UIColor {
    UIColor.qoraiBackground
  }
}

#if DEBUG
#Preview {
  PageSecurityView(
    displayURL: "http.badssl.com",
    secureState: .missingSSL,
    hasCertificate: false,
    presentCertificateViewer: {}
  )
  .clipShape(RoundedRectangle(cornerRadius: 10, style: .continuous))
  .shadow(radius: 10, x: 0, y: 1)
  .padding()
}
#endif
