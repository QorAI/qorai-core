// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStrings
import DesignSystem
import SwiftUI

struct DataImporterMultipleProfilesView: View {
  var zipFileExtractedURL: URL
  var profiles: [String: [String: URL]]
  var onProfileSelected: (String) -> Void

  @Environment(\.dismiss)
  private var dismiss

  @State
  var sheetHeight: CGFloat = 0.0

  var body: some View {
    ScrollView {
      VStack(spacing: 16.0) {
        Button {
          dismiss()
        } label: {
          Label {
            Text(Strings.close)
          } icon: {
            Image(qoraiSystemName: "qora.close")
              .foregroundColor(Color(qoraiSystemName: .iconDefault))
              .padding(8)
          }
          .labelStyle(.iconOnly)
        }
        .background(Color(qoraiSystemName: .materialSeparator), in: Circle())
        .frame(maxWidth: .infinity, alignment: .trailing)

        Image("multi_profile_logo", bundle: .module)

        VStack {
          Text(Strings.DataImporter.multipleProfilesTitle)
            .font(.headline)
            .foregroundColor(Color(qoraiSystemName: .textPrimary))

          Text(Strings.DataImporter.multipleProfilesMessage)
            .font(.footnote)
            .foregroundStyle(Color(qoraiSystemName: .textSecondary))
        }
        .multilineTextAlignment(.center)
        .frame(maxWidth: .infinity)
        .fixedSize(horizontal: false, vertical: true)

        VStack {
          ForEach(Array(profiles.keys.sorted().enumerated()), id: \.element) { (offset, profile) in
            Button {
              onProfileSelected(profile)
            } label: {
              HStack {
                Image(qoraiSystemName: "qora.user.picture")
                  .foregroundStyle(Color(qoraiSystemName: .iconInteractive))

                Text(profile.localizedCapitalized)
                  .foregroundStyle(Color(qoraiSystemName: .textInteractive))
                  .padding(.vertical, 12.0)

                Spacer()

                Image(qoraiSystemName: "qora.carat.right")
                  .foregroundStyle(Color(qoraiSystemName: .iconDefault))
              }
              .padding(.horizontal, 16.0)
            }

            if offset != profiles.count - 1 {
              Divider().padding(.leading)
            }
          }
        }
        .background(
          Color(qoraiSystemName: .iosBrowserElevatedIos),
          in: RoundedRectangle(cornerRadius: 12.0, style: .continuous)
        )
        .padding()
      }
      .padding(24.0)
      .frame(maxWidth: .infinity, maxHeight: .infinity)
      .onGeometryChange(
        for: CGSize.self,
        of: { $0.size },
        action: {
          sheetHeight = $0.height
        }
      )
    }
    .presentationDetents([.height(sheetHeight)])
    .presentationDragIndicator(.visible)
    .presentationBackground(.thickMaterial)
    .presentationCornerRadius(15.0)
    .presentationCompactAdaptation(.sheet)
  }
}
