// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation

#if DEBUG

class MockAssetRatioService: QoraiWalletAssetRatioService {
  private let assets: [String: QoraiWallet.AssetPrice] = [
    "eth": .init(
      coin: .eth,
      chainId: QoraiWallet.MainnetChainId,
      address: "",
      price: "3059.99",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    ),
    "bat": .init(
      coin: .eth,
      chainId: QoraiWallet.MainnetChainId,
      address: "0x0d8775f648430679a709e98d2b0cb6250d2887ef",
      price: "0.627699",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-0.019865"
    ),
  ]

  func price(
    requests: [QoraiWallet.AssetPriceRequest],
    vsCurrency: String,
    completion: @escaping (Bool, [QoraiWallet.AssetPrice]) -> Void
  ) {
    let prices = requests.compactMap { request in
      // Find matching asset based on coin type, chain ID, and address
      return assets.first { (_, assetPrice) in
        assetPrice.coin == request.coin
          && assetPrice.chainId == request.chainId
          && assetPrice.address == request.address
      }?.value
    }
    completion(!prices.isEmpty, prices)
  }

  func estimatedTime(_ gasPrice: String, completion: @escaping (Bool, String) -> Void) {
    completion(false, "")
  }

  func tokenInfo(
    _ contractAddress: String,
    completion: @escaping (QoraiWallet.BlockchainToken?) -> Void
  ) {
    completion(nil)
  }

  func priceHistory(
    asset: String,
    vsAsset: String,
    timeframe: QoraiWallet.AssetPriceTimeframe,
    completion: @escaping (Bool, [QoraiWallet.AssetTimePrice]) -> Void
  ) {
    completion(false, [])
  }

  func buyUrlV1(
    provider: QoraiWallet.OnRampProvider,
    chainId: String,
    address: String,
    symbol: String,
    amount: String,
    currencyCode: String,
    completion: @escaping (String, String?) -> Void
  ) {
    completion("", nil)
  }

  func sellUrl(
    provider: QoraiWallet.OffRampProvider,
    chainId: String,
    symbol: String,
    amount: String,
    currencyCode: String,
    completion: @escaping (String, String?) -> Void
  ) {
    completion("", nil)
  }

  func coinMarkets(
    vsAsset: String,
    limit: UInt8,
    completion: @escaping (Bool, [QoraiWallet.CoinMarket]) -> Void
  ) {
    completion(false, [])
  }
}

#endif
