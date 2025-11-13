// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiStrings
import QoraiUI
import DesignSystem
import SwiftUI

struct DataImporterSuccessView: View {
  var primaryAction: () -> Void

  var body: some View {
    VStack {
      VStack {
        Image("success_import_logo", bundle: .module)
          .padding(.bottom, 32.0)

        VStack {
          Text(Strings.DataImporter.importStateSuccessTitle)
            .font(.title.weight(.semibold))
            .foregroundColor(Color(qoraiSystemName: .textPrimary))

          Text(Strings.DataImporter.importStateSuccessMessage)
            .font(.subheadline)
            .foregroundStyle(Color(qoraiSystemName: .textSecondary))
        }
        .multilineTextAlignment(.center)
        .frame(maxWidth: .infinity)
        .fixedSize(horizontal: false, vertical: true)
        .padding(.horizontal, 24.0)
      }
      .frame(maxWidth: .infinity, maxHeight: .infinity)

      Spacer()

      Button(
        action: {
          primaryAction()
        },
        label: {
          Text(Strings.DataImporter.importStateSuccessContinueTitle)
            .font(.headline)
            .padding(.horizontal)
            .padding(.vertical, 12.0)
            .foregroundStyle(Color(qoraiSystemName: .schemesOnPrimary))
            .frame(maxWidth: .infinity)
            .background(
              Color(qoraiSystemName: .buttonBackground),
              in: RoundedRectangle(cornerRadius: 12.0, style: .continuous)
            )
        }
      )
      .buttonStyle(.plain)
    }
  }
}
