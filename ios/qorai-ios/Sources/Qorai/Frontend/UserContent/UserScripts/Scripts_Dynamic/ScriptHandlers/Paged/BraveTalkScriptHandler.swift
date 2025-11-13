// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiShared
import QoraiTalk
import Foundation
import Shared
import Web
import WebKit
import os.log

class QoraiTalkScriptHandler: TabContentScript {
  private weak var rewards: QoraiRewards?
  private var rewardsEnabledReplyHandler: ((Any?, String?) -> Void)?
  private let launchNativeQoraiTalk:
    (_ tab: (any TabState)?, _ room: String, _ token: String) -> Void

  required init(
    rewards: QoraiRewards,
    launchNativeQoraiTalk: @escaping (_ tab: (any TabState)?, _ room: String, _ token: String) ->
      Void
  ) {
    self.rewards = rewards
    self.launchNativeQoraiTalk = launchNativeQoraiTalk
  }

  static let scriptName = "QoraiTalkScript"
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

  private struct Payload: Decodable {
    enum Kind: Decodable {
      case qoraiRequestAdsEnabled
      case launchNativeQoraiTalk(String)
    }
    var kind: Kind
    var securityToken: String

    enum CodingKeys: String, CodingKey {
      case kind
      case url
      case securityToken = "securityToken"
    }

    init(from decoder: Decoder) throws {
      enum RawKindKey: String, Decodable {
        case qoraiRequestAdsEnabled
        case launchNativeQoraiTalk
      }
      let container = try decoder.container(keyedBy: CodingKeys.self)
      let kind = try container.decode(RawKindKey.self, forKey: .kind)
      self.securityToken = try container.decode(String.self, forKey: .securityToken)
      switch kind {
      case .launchNativeQoraiTalk:
        let url = try container.decode(String.self, forKey: .url)
        self.kind = .launchNativeQoraiTalk(url)
      case .qoraiRequestAdsEnabled:
        self.kind = .qoraiRequestAdsEnabled
      }
    }
  }

  func tab(
    _ tab: some TabState,
    receivedScriptMessage message: WKScriptMessage,
    replyHandler: @escaping (Any?, String?) -> Void
  ) {
    if !verifyMessage(message: message) {
      assertionFailure("Missing required security token.")
      return
    }

    let allowedHosts = DomainUserScript.qoraiTalkHelper.associatedDomains

    guard let requestHost = message.frameInfo.request.url?.host,
      allowedHosts.contains(requestHost),
      message.frameInfo.isMainFrame
    else {
      Logger.module.error("Backup search request called from disallowed host")
      replyHandler(nil, nil)
      return
    }

    guard let json = try? JSONSerialization.data(withJSONObject: message.body, options: []),
      let payload = try? JSONDecoder().decode(Payload.self, from: json)
    else {
      return
    }

    switch payload.kind {
    case .qoraiRequestAdsEnabled:
      handleQoraiRequestAdsEnabled(tab: tab, replyHandler)
    case .launchNativeQoraiTalk(let url):
      guard let components = URLComponents(string: url),
        case let room = String(components.path.dropFirst(1)),
        let jwt = components.queryItems?.first(where: { $0.name == "jwt" })?.value
      else {
        return
      }
      launchNativeQoraiTalk(tab, room, jwt)
      replyHandler(nil, nil)
    }
  }

  private func handleQoraiRequestAdsEnabled(
    tab: some TabState,
    _ replyHandler: @escaping (Any?, String?) -> Void
  ) {
    guard let rewards = rewards, tab.isPrivate != true else {
      replyHandler(false, nil)
      return
    }

    if rewards.isEnabled {
      replyHandler(true, nil)
      return
    }

    // If rewards are disabled we show a Rewards panel,
    // The `rewardsEnabledReplyHandler` will be called from other place.
    rewardsEnabledReplyHandler = replyHandler
    tab.rewardsEnabledCallback = { [weak self] success in
      self?.rewardsEnabledReplyHandler?(success, nil)
    }
    tab.miscDelegate?.showRequestRewardsPanel(tab)
  }
}
