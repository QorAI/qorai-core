// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation
import Shared
import UIKit
import Web

extension BrowserViewController {
  func launchNativeQoraiTalk(tab: (any TabState)?, room: String, token: String) {
    guard let host = tab?.lastCommittedURL?.host else { return }
    qoraiTalkJitsiCoordinator.launchNativeQoraiTalk(
      for: room,
      token: token,
      host: host,
      onEnterCall: { [weak tab] in
        tab?.stopLoading()
      },
      onExitCall: { [weak self] in
        guard let self = self else { return }
        // When we close the call, redirect to Qorai Talk home page if the selected tab is still the original
        // talk URL
        if let url = self.tabManager.selectedTab?.visibleURL,
          let currentHost = url.host,
          DomainUserScript.qoraiTalkHelper.associatedDomains.contains(currentHost)
        {
          var components = URLComponents()
          components.host = currentHost
          components.scheme = url.scheme
          self.select(url: components.url!, isUserDefinedURLNavigation: false)
        }
      }
    )
  }
}
