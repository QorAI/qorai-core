// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiShared
import Web
import WebKit
import os.log

class QoraiSearchResultAdScriptHandler: TabContentScript {
  private struct SearchResultAdResponse: Decodable {
    struct SearchResultAd: Decodable {
      let creativeInstanceId: String
      let placementId: String
      let creativeSetId: String
      let campaignId: String
      let advertiserId: String
      let landingPage: URL
      let headlineText: String
      let description: String
      let rewardsValue: String
      let conversionUrlPatternValue: String?
      let conversionAdvertiserPublicKeyValue: String?
      let conversionObservationWindowValue: Int?
    }

    let creatives: [SearchResultAd]
  }

  static let scriptName = "QoraiSearchResultAdScript"
  static let scriptId = UUID().uuidString
  static let messageHandlerName = "\(scriptName)_\(messageUUID)"
  static let scriptSandbox: WKContentWorld = .defaultClient
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
      injectionTime: .atDocumentEnd,
      forMainFrameOnly: true,
      in: scriptSandbox
    )
  }()

  func tab(
    _ tab: some TabState,
    receivedScriptMessage message: WKScriptMessage,
    replyHandler: (Any?, String?) -> Void
  ) {
    defer { replyHandler(nil, nil) }

    if !verifyMessage(message: message) {
      assertionFailure("Missing required security token.")
      return
    }

    guard let qoraiSearchResultAdManager = tab.qoraiSearchResultAdManager else {
      Logger.module.error("Failed to get qorai search result ad handler")
      return
    }

    guard JSONSerialization.isValidJSONObject(message.body),
      let messageData = try? JSONSerialization.data(withJSONObject: message.body, options: []),
      let searchResultAds = try? JSONDecoder().decode(
        SearchResultAdResponse.self,
        from: messageData
      )
    else {
      Logger.module.error("Failed to parse search result ads response")
      return
    }

    processSearchResultAds(searchResultAds, qoraiSearchResultAdManager: qoraiSearchResultAdManager)
  }

  private func processSearchResultAds(
    _ searchResultAds: SearchResultAdResponse,
    qoraiSearchResultAdManager: QoraiSearchResultAdManager
  ) {
    for ad in searchResultAds.creatives {
      guard let rewardsValue = Double(ad.rewardsValue)
      else {
        Logger.module.error("Failed to process search result ads JSON-LD")
        return
      }

      var conversion: QoraiAds.CreativeSetConversionInfo?
      if let conversionUrlPatternValue = ad.conversionUrlPatternValue,
        let conversionObservationWindowValue = ad.conversionObservationWindowValue
      {
        let timeInterval = TimeInterval(conversionObservationWindowValue) * 1.days
        conversion = .init(
          urlPattern: conversionUrlPatternValue,
          verifiableAdvertiserPublicKeyBase64: ad.conversionAdvertiserPublicKeyValue,
          observationWindow: Date(timeIntervalSince1970: timeInterval)
        )
      }

      let searchResultAd: QoraiAds.CreativeSearchResultAdInfo = .init(
        type: .searchResultAd,
        placementId: ad.placementId,
        creativeInstanceId: ad.creativeInstanceId,
        creativeSetId: ad.creativeSetId,
        campaignId: ad.campaignId,
        advertiserId: ad.advertiserId,
        targetUrl: ad.landingPage,
        headlineText: ad.headlineText,
        description: ad.description,
        value: rewardsValue,
        creativeSetConversion: conversion
      )

      qoraiSearchResultAdManager.triggerSearchResultAdViewedEvent(
        placementId: ad.placementId,
        searchResultAd: searchResultAd
      )
    }
  }
}
