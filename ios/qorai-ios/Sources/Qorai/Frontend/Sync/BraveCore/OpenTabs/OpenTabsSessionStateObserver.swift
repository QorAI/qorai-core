// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation

class OpenTabsStateObserver: QoraiServiceStateObserver, OpenTabsSessionStateObserver {

  private let listener: (StateChange) -> Void

  enum StateChange {
    case openTabsSyncStateChanged
    case openTabsSyncCycleCompleted
    case openTabsSyncConfigurationCompleted
    case openTabsSyncShutdown
  }

  init(_ listener: @escaping (StateChange) -> Void) {
    self.listener = listener
  }

  func openTabsSyncStateChanged() {
    listener(.openTabsSyncStateChanged)
  }

  func openTabsSyncCycleCompleted() {
    listener(.openTabsSyncCycleCompleted)
  }

  func openTabsSyncConfigurationCompleted() {
    listener(.openTabsSyncConfigurationCompleted)
  }

  func openTabsSyncShutdown() {
    listener(.openTabsSyncShutdown)
  }
}
