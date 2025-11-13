// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation

class PasswordStoreStateObserver: QoraiServiceStateObserver, PasswordStoreObserver {

  private let listener: (StateChange) -> Void

  enum StateChange {
    case passwordFormsChanged(_ formList: [PasswordForm])
    case passwordFormsRetained(_ formList: [PasswordForm])
  }

  init(_ listener: @escaping (StateChange) -> Void) {
    self.listener = listener
  }

  func passwordFormsChanged(_ changedFormList: [PasswordForm]) {
    listener(.passwordFormsChanged(changedFormList))
  }

  func passwordFormsRetained(_ retainedFormList: [PasswordForm]) {
    listener(.passwordFormsRetained(retainedFormList))
  }

}
