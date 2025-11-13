// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore

// A helper class to handle Qorai Search Result Ads.
class QoraiSearchResultAdManager: NSObject {
  private static let searchResultAdClickedUrlPath = "/a/redirect"

  private static let placementId = "placement_id"

  let rewards: QoraiRewards

  init?(url: URL, rewards: QoraiRewards, isPrivateBrowsing: Bool, isAggressiveAdsBlocking: Bool) {
    if !QoraiSearchResultAdManager.shouldTriggerSearchResultAd(
      url: url,
      isPrivateBrowsing: isPrivateBrowsing,
      isAggressiveAdsBlocking: isAggressiveAdsBlocking
    ) {
      return nil
    }

    self.rewards = rewards
  }

  func triggerSearchResultAdViewedEvent(
    placementId: String,
    searchResultAd: QoraiAds.CreativeSearchResultAdInfo
  ) {
    rewards.ads.triggerSearchResultAdViewedEvent(
      searchResultAd,
      completion: { _ in }
    )
  }

  static func maybeTriggerSearchResultAdClickedEvent(
    _ url: URL,
    rewards: QoraiRewards,
    completion: @escaping ((Bool) -> Void)
  ) {
    guard let placementId = getPlacementID(url) else {
      return
    }

    rewards.ads.triggerSearchResultAdClickedEvent(
      placementId,
      completion: completion
    )
  }

  static func shouldTriggerSearchResultAdClickedEvent(
    _ url: URL,
    isPrivateBrowsing: Bool,
    isAggressiveAdsBlocking: Bool
  ) -> Bool {
    return shouldTriggerSearchResultAd(
      url: url,
      isPrivateBrowsing: isPrivateBrowsing,
      isAggressiveAdsBlocking: isAggressiveAdsBlocking
    ) && getPlacementID(url) != nil
  }

  private static func getPlacementID(_ url: URL) -> String? {
    if !QoraiSearchManager.isValidURL(url) || url.path != searchResultAdClickedUrlPath {
      return nil
    }
    guard let queryItems = URLComponents(url: url, resolvingAgainstBaseURL: false)?.queryItems
    else {
      return nil
    }
    return queryItems.first(where: { $0.name == placementId })?.value
  }

  private static func shouldTriggerSearchResultAd(
    url: URL,
    isPrivateBrowsing: Bool,
    isAggressiveAdsBlocking: Bool
  ) -> Bool {
    return !isPrivateBrowsing && !isAggressiveAdsBlocking && QoraiSearchManager.isValidURL(url)
  }
}
