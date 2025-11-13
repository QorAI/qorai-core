// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiVPN
import UIKit

extension BrowserViewController {
  /// Shows a vpn screen based on vpn state.
  public func presentCorrespondingVPNViewController() {
    if QoraiSkusManager.keepShowingSessionExpiredState {
      let alert = QoraiSkusManager.sessionExpiredStateAlert(loginCallback: { [unowned self] _ in
        self.openURLInNewTab(
          .qorai.account,
          isPrivate: self.privateBrowsingManager.isPrivateBrowsing,
          isPrivileged: false
        )
      })

      present(alert, animated: true)
      return
    }

    guard QoraiVPN.vpnState.isPaywallEnabled else { return }

    let vpnPaywallView = QoraiVPNPaywallView(
      openVPNAuthenticationInNewTab: { [weak self] in
        guard let self = self else { return }

        self.popToBVC()

        self.openURLInNewTab(
          .qorai.qoraiVPNRefreshCredentials,
          isPrivate: self.privateBrowsingManager.isPrivateBrowsing,
          isPrivileged: false
        )
      },
      openDirectCheckoutInNewTab: { [weak self] in
        guard let self else { return }
        popToBVC()
        openURLInNewTab(
          .qorai.qoraiVPNCheckoutURL,
          isPrivate: self.privateBrowsingManager.isPrivateBrowsing,
          isPrivileged: false
        )
      },
      openLearnMoreInNewTab: { [weak self] in
        guard let self else { return }
        popToBVC()
        openURLInNewTab(
          .qorai.qoraiVPNLearnMoreURL,
          isPrivate: self.privateBrowsingManager.isPrivateBrowsing,
          isPrivileged: false
        )
      },
      installVPNProfile: { [weak self] in
        guard let self = self else { return }
        self.dismiss(animated: true) {
          self.present(QoraiVPNInstallViewController(), animated: true)
        }
      }
    )
    let vpnPaywallHostingVC = QoraiVPNPaywallHostingController(paywallView: vpnPaywallView)
    popToBVC(isAnimated: true) { [weak self] in
      self?.present(UINavigationController(rootViewController: vpnPaywallHostingVC), animated: true)
    }
  }
}
