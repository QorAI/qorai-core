// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore

extension PrefService {
  /// Whether or not the Qorai Talk feature in general is available to use and the UI should display
  /// buttons/settings for it.
  public var isQoraiTalkAvailable: Bool {
    // Right now this feature is always available unless its managed/forced by policy
    let isDisabledByPolicy =
      isManagedPreference(forPath: kQoraiTalkDisabledByPolicyPrefName)
      && boolean(forPath: kQoraiTalkDisabledByPolicyPrefName)
    return !isDisabledByPolicy
  }
}
