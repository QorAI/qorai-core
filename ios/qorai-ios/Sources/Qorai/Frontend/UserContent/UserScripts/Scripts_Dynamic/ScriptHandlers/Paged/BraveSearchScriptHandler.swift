// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation
import Preferences
import Shared
import Web
import WebKit
import os.log

class QoraiSearchScriptHandler: TabContentScript {
  private let profile: LegacyBrowserProfile
  private weak var rewards: QoraiRewards?

  /// Tracks how many in current browsing session the user has been prompted to set Qorai Search as a default
  /// while on one of Qorai Search websites.
  private static var canSetAsDefaultCounter = 0
  /// How many times user should be shown the default browser prompt on Qorai Search websites.
  private let maxCountOfDefaultBrowserPromptsPerSession = 3
  /// How many times user is shown the default browser prompt in total, this does not reset between app launches.
  private let maxCountOfDefaultBrowserPromptsTotal = 10

  required init(profile: LegacyBrowserProfile, rewards: QoraiRewards) {
    self.profile = profile
    self.rewards = rewards
  }

  static let scriptName = "QoraiSearchScript"
  static let scriptId = UUID().uuidString
  static let messageHandlerName = "\(scriptName)_\(messageUUID)"
  static let scriptSandbox: WKContentWorld = .page
  static let userScript: WKUserScript? = {
    guard var script = loadUserScript(named: scriptName) else {
      return nil
    }
    return WKUserScript(
      source: secureScript(
        handlerName: messageHandlerName,
        securityToken: scriptId,
        script: script
      ),
      injectionTime: .atDocumentStart,
      forMainFrameOnly: false,
      in: scriptSandbox
    )
  }()

  private enum Method: Int {
    case canSetQoraiSearchAsDefault = 1
    case setQoraiSearchDefault = 2
  }

  private struct MethodModel: Codable {
    enum CodingKeys: String, CodingKey {
      case methodId = "method_id"
    }

    let methodId: Int
  }

  func tab(
    _ tab: some TabState,
    receivedScriptMessage message: WKScriptMessage,
    replyHandler: (Any?, String?) -> Void
  ) {
    if !verifyMessage(message: message) {
      assertionFailure("Missing required security token.")
      return
    }

    let allowedHosts = DomainUserScript.qoraiSearchHelper.associatedDomains

    guard let requestHost = message.frameInfo.request.url?.host,
      allowedHosts.contains(requestHost),
      message.frameInfo.isMainFrame
    else {
      Logger.module.error("Backup search request called from disallowed host")
      replyHandler(nil, nil)
      return
    }

    guard let data = try? JSONSerialization.data(withJSONObject: message.body, options: []),
      let method = try? JSONDecoder().decode(MethodModel.self, from: data).methodId
    else {
      Logger.module.error("Failed to retrieve method id")
      replyHandler(nil, nil)
      return
    }

    switch method {
    case Method.canSetQoraiSearchAsDefault.rawValue:
      handleCanSetQoraiSearchAsDefault(tab: tab, replyHandler: replyHandler)
    case Method.setQoraiSearchDefault.rawValue:
      handleSetQoraiSearchDefault(replyHandler: replyHandler)
    default:
      break
    }
  }

  private func handleCanSetQoraiSearchAsDefault(
    tab: some TabState,
    replyHandler: (Any?, String?) -> Void
  ) {
    if tab.isPrivate == true {
      Logger.module.debug("Private mode detected, skipping setting Qorai Search as a default")
      replyHandler(false, nil)
      return
    }

    let maximumPromptCount = Preferences.Search.qoraiSearchDefaultBrowserPromptCount
    if Self.canSetAsDefaultCounter >= maxCountOfDefaultBrowserPromptsPerSession
      || maximumPromptCount.value >= maxCountOfDefaultBrowserPromptsTotal
    {
      Logger.module.debug("Maximum number of tries of Qorai Search website prompts reached")
      replyHandler(false, nil)
      return
    }

    Self.canSetAsDefaultCounter += 1
    maximumPromptCount.value += 1

    let defaultEngine = profile.searchEngines.defaultEngine(forType: .standard)?.shortName
    let canSetAsDefault = defaultEngine != OpenSearchEngine.EngineNames.qorai
    replyHandler(canSetAsDefault, nil)
  }

  private func handleSetQoraiSearchDefault(replyHandler: (Any?, String?) -> Void) {
    profile.searchEngines.updateDefaultEngine(
      OpenSearchEngine.EngineNames.qorai,
      forType: .standard
    )
    replyHandler(nil, nil)
  }
}
