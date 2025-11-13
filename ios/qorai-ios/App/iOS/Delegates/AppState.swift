// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

import AIChat
import Qorai
import QoraiCore
import QoraiNews
import QoraiShared
import Data
import Foundation
import Growth
import Preferences
import RuntimeWarnings
import Shared
import Storage
import UIKit
import UserAgent
import os.log

private let adsRewardsLog = Logger(
  subsystem: Bundle.main.bundleIdentifier!,
  category: "ads-rewards"
)

/// Class that does startup initialization
/// Everything in this class can only be execute ONCE
/// IE: QoraiCore initialization, BuildChannel, Migrations, etc.
public class AppState {
  private let log = Logger(subsystem: Bundle.main.bundleIdentifier!, category: "app-state")

  public static let shared = AppState()

  public let qoraiCore: QoraiCoreMain
  public let migration: Migration
  public let localStateMigration: QoraiLocalStateMigration
  public let profile: LegacyBrowserProfile
  public let newsFeedDataSource: FeedDataSource
  public let uptimeMonitor = UptimeMonitor()
  private var didBecomeActive = false

  public var state: State = .launching(options: [:], active: false) {
    didSet {
      switch state {
      case .launching(_, let isActive):
        // Always initialize reachability
        _ = Reachability.shared

        if didBecomeActive {
          assertionFailure("Cannot set launching state twice!")
        }

        if isActive && !didBecomeActive {
          // We have to wait until pre 1.12 migration is done until we proceed with database
          // initialization. This is because Database container may change. See bugs #3416, #3377.
          didBecomeActive = true
          DataController.shared.initializeOnce()
          DataController.sharedInMemory.initializeOnce()
          Migration.migrateLostTabsActiveWindow()

          let useChromiumWebViews = FeatureList.kUseChromiumWebViews.enabled
          var purgeSessionData =
            useChromiumWebViews && !Preferences.Chromium.invalidatedRestorationOnUpgrade.value
          if let value = Preferences.Chromium.lastWebViewsFlagState.value,
            value != useChromiumWebViews
          {
            purgeSessionData = true
          }
          if purgeSessionData {
            Preferences.Chromium.invalidatedRestorationOnUpgrade.value = true
            SessionTab.purgeSessionData()
          }

          Preferences.Chromium.lastWebViewsFlagState.value = useChromiumWebViews
        }
        break
      case .active:
        break
      case .backgrounded:
        break
      case .terminating:
        break
      }
    }
  }

  private init() {
    // Setup Constants
    AppState.setupConstants()

    // Setup QoraiCore
    qoraiCore = AppState.setupQoraiCore().then {
      $0.scheduleLowPriorityStartupTasks()
    }

    // Setup Profile
    profile = LegacyBrowserProfile()

    // Setup Migrations
    migration = Migration()
    localStateMigration = QoraiLocalStateMigration(localState: qoraiCore.localState)

    // Perform Migrations
    migration.launchMigrations(keyPrefix: "profile")
    localStateMigration.launchMigrations()

    newsFeedDataSource = FeedDataSource()

    // Setup Custom URL scheme handlers
    setupCustomSchemeHandlers()
  }

  public enum State {
    case launching(options: [UIApplication.LaunchOptionsKey: Any], active: Bool)
    case active
    case backgrounded
    case terminating
  }

  private static func setupConstants() {
  }

  private static func setupQoraiCore() -> QoraiCoreMain {
    // QoraiCore Log Handler
    QoraiCoreMain.setLogHandler { severity, file, line, messageStartIndex, message in
      let message = String(message.dropFirst(messageStartIndex).dropLast())
        .trimmingCharacters(in: .whitespacesAndNewlines)
      if message.isEmpty {
        // Nothing to print
        return true
      }

      let isLoggingAccessible =
        !AppConstants.isOfficialBuild || Preferences.Debug.developerOptionsEnabled.value

      let level: OSLogType = {
        switch severity {
        case .fatal: return .fault
        case .error: return .error
        // No `.warning` level exists for OSLogType. os_Log.warning is an alias for `.error`.
        case .warning: return .error
        case .info: return .info
        // `debug` log level doesn't show up in Console.app when not building a Debug configuration
        default: return isLoggingAccessible ? .info : .debug
        }
      }()

      let qoraiCoreLogger = Logger(subsystem: Bundle.main.bundleIdentifier!, category: "qorai-core")
      if isLoggingAccessible {
        qoraiCoreLogger.log(level: level, "\(message, privacy: .public)")
      } else {
        qoraiCoreLogger.log(level: level, "\(message, privacy: .private)")
      }

      return true
    }

    // Initialize QoraiCore Switches
    var switches: [QoraiCoreSwitch] = []
    // Check prefs for additional switches
    let activeSwitches = Set(Preferences.QoraiCore.activeSwitches.value)
    let customSwitches = Set(Preferences.QoraiCore.customSwitches.value)
    let switchValues = Preferences.QoraiCore.switchValues.value

    // Add regular known switches
    for activeSwitch in activeSwitches {
      let key = QoraiCoreSwitchKey(rawValue: activeSwitch)
      if key.isValueless {
        switches.append(.init(key: key))
      } else if let value = switchValues[activeSwitch], !value.isEmpty {
        switches.append(.init(key: key, value: value))
      }
    }

    // Add custom user defined switches
    for customSwitch in customSwitches {
      let key = QoraiCoreSwitchKey(rawValue: customSwitch)
      if let value = switchValues[customSwitch] {
        if value.isEmpty {
          switches.append(.init(key: key))
        } else {
          switches.append(.init(key: key, value: value))
        }
      }
    }

    switches.append(.init(key: .rewardsFlags, value: QoraiRewards.Configuration.current().flags))

    // Initialize QoraiCore
    let qoraiCoreMain = QoraiCoreMain(additionalSwitches: switches)
    // `UserAgent.mobile` requires a feature flag, so it must be initialized after QoraiCore
    qoraiCoreMain.setUserAgent(UserAgent.mobile)
    return qoraiCoreMain
  }

  private func setupCustomSchemeHandlers() {
    let responders: [(String, InternalSchemeResponse)] = [
      (AboutHomeHandler.path, AboutHomeHandler()),
      (ErrorPageHandler.path, ErrorPageHandler()),
      (ReaderModeHandler.path, ReaderModeHandler()),
      (Web3DomainHandler.path, Web3DomainHandler()),
      (BlockedDomainHandler.path, BlockedDomainHandler()),
      (HTTPBlockedHandler.path, HTTPBlockedHandler()),
    ]

    responders.forEach { (path, responder) in
      InternalSchemeHandler.responders[path] = responder
    }
  }
}
