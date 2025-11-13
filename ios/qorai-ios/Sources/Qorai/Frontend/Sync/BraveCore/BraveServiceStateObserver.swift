// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation

public class QoraiServiceStateObserver: NSObject {

  // MARK: Static

  public static let coreServiceLoadedNotification: Notification.Name = .init(
    rawValue: "QoraiServiceStateDidLoaded"
  )

  static var isServiceLoadStatePosted = false

  // MARK: Private

  func postServiceLoadedNotification() {
    guard !QoraiServiceStateObserver.isServiceLoadStatePosted else {
      return
    }

    NotificationCenter.default.post(
      name: QoraiServiceStateObserver.coreServiceLoadedNotification,
      object: nil
    )

    QoraiServiceStateObserver.isServiceLoadStatePosted = true
  }
}
