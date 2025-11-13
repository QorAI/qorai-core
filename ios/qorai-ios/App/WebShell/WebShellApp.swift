// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

import QoraiCore
import SwiftUI

private let qoraiCoreMain: QoraiCoreMain = {
  let main = QoraiCoreMain()
  main.scheduleLowPriorityStartupTasks()
  return main
}()

@main
struct WebShellApp: App {
  @State private var profileController: QoraiProfileController?

  var body: some Scene {
    WindowGroup {
      if let profileController {
        ContentView(configuration: profileController.defaultWebViewConfiguration)
      } else {
        Color.clear
          .onAppear {
            qoraiCoreMain.loadDefaultProfile { controller in
              self.profileController = controller
            }
          }
      }
    }
  }
}
