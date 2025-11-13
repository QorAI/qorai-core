// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation
import SwiftUI

extension QoraiWallet.AccountInfo: Identifiable {
  public var id: String {
    accountId.uniqueKey
  }
  public var isPrimary: Bool {
    // no hardware support on iOS
    accountId.kind != .imported
  }

  public var isImported: Bool {
    accountId.kind == .imported
  }

  public var coin: QoraiWallet.CoinType {
    accountId.coin
  }

  public var keyringId: QoraiWallet.KeyringId {
    accountId.keyringId
  }
}

extension QoraiWallet.TransactionInfo: Identifiable {
  // Already has `id` property
}

public enum AssetImageName: String {
  case ethereum = "eth-asset-icon"
  case solana = "sol-asset-icon"
  case filecoin = "filecoin-asset-icon"
  case bitcoin = "bitcoin-asset-icon"
  case zcash = "zcash-asset-icon"
  case polygon = "matic"
  case binance = "bnb-asset-icon"
  case celo = "celo"
  case avalanche = "avax"
  case fantom = "fantom"
  case aurora = "aurora"
  case optimism = "optimism"
  case base = "base"
  case neon = "neon"
}

extension QoraiWallet.NetworkInfo: Identifiable {
  public var id: String {
    "\(chainId)\(coin.rawValue)"
  }

  var shortChainName: String {
    chainName.split(separator: " ").first?.capitalized ?? chainName
  }

  var isKnownTestnet: Bool {
    WalletConstants.supportedTestNetworkChainIds.contains(chainId)
  }

  public var nativeToken: QoraiWallet.BlockchainToken {
    .init(
      contractAddress: "",
      name: symbolName,
      logo: nativeTokenLogoName ?? "",
      isCompressed: false,
      isErc20: false,
      isErc721: false,
      isErc1155: false,
      splTokenProgram: .unsupported,
      isNft: false,
      isSpam: false,
      symbol: symbol,
      decimals: decimals,
      visible: false,
      tokenId: "",
      coingeckoId: "",
      chainId: chainId,
      coin: coin,
      isShielded: false
    )
  }

  public var nativeTokenLogoName: String? {
    if let logoBySymbol = assetIconNameBySymbol(symbol) {
      return logoBySymbol
    } else if let logoByChainId = chainId.chainIconName {
      return logoByChainId
    } else {
      return iconUrls.first
    }
  }

  public var nativeTokenLogoImage: UIImage? {
    guard let logo = nativeTokenLogoName else { return nil }
    return UIImage(named: logo, in: .module, with: nil)
  }

  public var networkLogoName: String? {
    return chainId.chainIconName ?? iconUrls.first
  }

  public var networkLogoImage: UIImage? {
    guard let logo = networkLogoName else { return nil }
    return UIImage(named: logo, in: .module, with: nil)
  }

  private func assetIconNameBySymbol(_ symbol: String) -> String? {
    if symbol.caseInsensitiveCompare("ETH") == .orderedSame {
      return AssetImageName.ethereum.rawValue
    } else if symbol.caseInsensitiveCompare("SOL") == .orderedSame {
      return AssetImageName.solana.rawValue
    } else if symbol.caseInsensitiveCompare("FIL") == .orderedSame {
      return AssetImageName.filecoin.rawValue
    } else if symbol.caseInsensitiveCompare("BTC") == .orderedSame {
      return AssetImageName.bitcoin.rawValue
    } else if symbol.caseInsensitiveCompare("ZEC") == .orderedSame {
      return AssetImageName.zcash.rawValue
    }
    return nil
  }
}

extension QoraiWallet.BlockchainToken: Identifiable {
  public var id: String {
    contractAddress + chainId + symbol + tokenId
  }

  public func contractAddress(in network: QoraiWallet.NetworkInfo) -> String {
    switch network.coin {
    case .eth:
      // ETH special swap address
      // Only checking token.symbol with selected network.symbol is sufficient
      // since there is no swap support for custom networks.
      return symbol == network.symbol ? QoraiWallet.ethSwapAddress : contractAddress
    case .sol:
      // SOL special swap address
      // Only checking token.symbol with selected network.symbol is sufficient
      // since there is no swap support for custom networks.
      return symbol == network.symbol ? QoraiWallet.solSwapAddress : contractAddress
    default:
      return contractAddress
    }
  }
}

extension QoraiWallet {
  /// The address that is expected when you are swapping ETH via SwapService APIs
  public static let ethSwapAddress: String = "0xeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"

  /// The address that is expected when you are swapping SOL via Jupiter Swap APIs
  public static let solSwapAddress: String = "So11111111111111111111111111111111111111112"
}

extension QoraiWallet.CoinType: Identifiable {
  public var id: Int {
    rawValue
  }
}

extension QoraiWallet.OnRampProvider: Identifiable {
  public var id: Int {
    rawValue
  }
}

extension QoraiWallet.OnRampCurrency: Identifiable {
  public var id: String {
    currencyCode
  }

  var symbol: String {
    CurrencyCode.symbol(for: currencyCode)
  }
}

extension QoraiWallet.CoinMarket: Identifiable {
  var uniqueId: String {
    "\(symbol)\(marketCapRank)"
  }
}

extension QoraiWallet.MeldFiatCurrency: Identifiable {
  public var id: String {
    currencyCode
  }
}

extension QoraiWallet.MeldServiceProvider: Identifiable {
  public var id: String {
    serviceProvider
  }
}

extension QoraiWallet.MeldCryptoCurrency: Identifiable {
  public var id: String {
    currencyCode
  }
}
