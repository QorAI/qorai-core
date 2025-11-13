// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiShields
import QoraiUI
import Strings
import SwiftUI

/// View for displaying global Shred settings
struct ShredSettingsView: View {
  @ObservedObject var settings: AdvancedShieldsSettings

  var body: some View {
    Form {
      FormPicker(selection: $settings.shredLevel) {
        ForEach(SiteShredLevel.allCases) { level in
          Text(level.localizedTitle)
            .foregroundColor(Color(.secondaryQoraiLabel))
            .tag(level)
        }
      } label: {
        LabelView(
          title: Strings.Shields.autoShred,
          subtitle: nil
        )
      }
      ToggleView(
        title: Strings.Shields.shredHistoryRowTitle,
        subtitle: Strings.Shields.shredHistoryRowDescription,
        toggle: $settings.shredHistoryItems
      )
    }
    .navigationTitle(Strings.Shields.shredSettingsViewTitle)
  }
}
