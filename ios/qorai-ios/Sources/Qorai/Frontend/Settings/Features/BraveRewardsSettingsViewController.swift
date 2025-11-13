// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiShared
import QoraiUI
import Combine
import Shared
import SwiftUI
import UIKit
import Web

private class QoraiRewardsSettingsViewModel: ObservableObject {
  let rewards: QoraiRewards
  private var rewardsObserver: RewardsObserver?
  private var isEnabledObserver: NSKeyValueObservation?

  init(rewards: QoraiRewards) {
    self.rewards = rewards

    if let rewardsAPI = rewards.rewardsAPI {
      isWalletInitialized = rewardsAPI.isInitialized
    }

    isEnabledObserver = rewards.ads.observe(\.isEnabled, options: [.new]) { [weak self] _, change in
      if let newValue = change.newValue {
        self?.isRewardsEnabled = newValue
      }
    }
  }

  var isRewardsEnabled: Bool {
    get {
      rewards.isEnabled || rewards.isTurningOnRewards
    }
    set {
      if rewards.rewardsAPI == nil {
        rewards.startRewardsService { [weak self] in
          guard let self else { return }
          if let rewardsAPI = self.rewards.rewardsAPI {
            let observer = RewardsObserver(rewardsAPI: rewardsAPI)
            rewardsAPI.add(observer)
            self.rewardsObserver = observer
            observer.walletInitalized = { [weak self] _ in
              DispatchQueue.main.async {
                self?.isWalletInitialized = true
              }
            }
          }
          self.rewards.isEnabled = newValue
          self.objectWillChange.send()
        }
      } else {
        rewards.isEnabled = newValue
        self.objectWillChange.send()
      }
    }
  }

  @Published private(set) var isWalletInitialized: Bool = false
}

struct QoraiRewardsSettingsView: View {
  @ObservedObject private var model: QoraiRewardsSettingsViewModel
  fileprivate init(model: QoraiRewardsSettingsViewModel) {
    self.model = model
  }
  var body: some View {
    Form {
      Section {
        Toggle(isOn: $model.isRewardsEnabled) {
          VStack(alignment: .leading) {
            Text(Strings.Rewards.settingsToggleTitle)
            Text(Strings.Rewards.settingsToggleMessage)
              .foregroundStyle(Color(qoraiSystemName: .textSecondary))
              .font(.footnote)
          }
        }
        .tint(Color(qoraiSystemName: .primary50))
        .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      }
      if model.isWalletInitialized, let rewardsAPI = model.rewards.rewardsAPI {
        Section {
          NavigationLink {
            UIKitController(RewardsInternalsViewController(rewardsAPI: rewardsAPI))
          } label: {
            Text(Strings.RewardsInternals.title)
          }
          .listRowBackground(Color(.secondaryQoraiGroupedBackground))
        }
      }
    }
    .scrollContentBackground(.hidden)
    .background(Color(.qoraiGroupedBackground))
  }
}

class QoraiRewardsSettingsViewController: UIHostingController<QoraiRewardsSettingsView> {
  init(rewards: QoraiRewards) {
    super.init(rootView: QoraiRewardsSettingsView(model: .init(rewards: rewards)))
  }

  @available(*, unavailable)
  required init(coder: NSCoder) {
    fatalError()
  }

  override func viewDidLoad() {
    super.viewDidLoad()
    title = Strings.qoraiRewardsTitle
  }
}
