// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation
import Storage
import Web

extension TabDataValues {
  private struct QoraiUserAgentExceptionsKey: TabDataKey {
    static var defaultValue: QoraiUserAgentExceptionsIOS?
  }

  /// A reference to a Qorai user agent exceptions list that can be used to check
  /// if we should show Qorai in the user agent for a given website.
  public var qoraiUserAgentExceptions: QoraiUserAgentExceptionsIOS? {
    get { self[QoraiUserAgentExceptionsKey.self] }
    set {
      if !FeatureList.kUseQoraiUserAgent.enabled {
        return
      }
      self[QoraiUserAgentExceptionsKey.self] = newValue
    }
  }
}
