// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStrings
import QoraiUI
import Preferences
import Shared
import SwiftUI

struct QoraiTranslateSettingsView: View {
  @ObservedObject
  private var translateEnabled = Preferences.Translate.translateEnabled

  var body: some View {
    Form {
      Section {
        Toggle(isOn: $translateEnabled.value) {
          Text(Strings.QoraiTranslate.settingsTranslateEnabledOptionTitle)
        }
        .tint(Color.accentColor)
        .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      } footer: {
        Text(Strings.QoraiTranslate.settingsTranslateEnabledOptionDescription)
      }
    }
    .listStyle(.insetGrouped)
    .background(Color(UIColor.qoraiGroupedBackground))
    .navigationTitle(Strings.QoraiTranslate.settingsScreenTitle)
  }
}

#if DEBUG
struct QoraiTranslateSettingsView_Previews: PreviewProvider {
  static var previews: some View {
    QoraiTranslateSettingsView()
  }
}
#endif
