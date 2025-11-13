import QoraiCore
import XCTest

@testable import QoraiWallet

class QoraiWalletExtensionsTests: XCTestCase {

  func testIsNativeAsset() {
    let ethCoin: QoraiWallet.BlockchainToken = .init(
      contractAddress: "",
      name: "Eth",
      logo: "",
      isCompressed: false,
      isErc20: false,
      isErc721: false,
      isErc1155: false,
      splTokenProgram: .unsupported,
      isNft: false,
      isSpam: false,
      symbol: "Eth",
      decimals: 18,
      visible: true,
      tokenId: "",
      coingeckoId: "",
      chainId: "",
      coin: .eth,
      isShielded: false
    )
    let ethToken: QoraiWallet.BlockchainToken = .init(
      contractAddress: "mock-eth-contract-address",
      name: "Eth Token",
      logo: "",
      isCompressed: false,
      isErc20: true,
      isErc721: false,
      isErc1155: false,
      splTokenProgram: .unsupported,
      isNft: false,
      isSpam: false,
      symbol: "ETHTOKEN",
      decimals: 18,
      visible: false,
      tokenId: "",
      coingeckoId: "",
      chainId: "",
      coin: .eth,
      isShielded: false
    )
    let ethNetwork = QoraiWallet.NetworkInfo.mockMainnet

    XCTAssertTrue(ethNetwork.isNativeAsset(ethCoin))
    XCTAssertFalse(ethNetwork.isNativeAsset(ethToken))

    let solCoin: QoraiWallet.BlockchainToken = .init(
      contractAddress: "",
      name: "Sol",
      logo: "",
      isCompressed: false,
      isErc20: false,
      isErc721: false,
      isErc1155: false,
      splTokenProgram: .unknown,
      isNft: false,
      isSpam: false,
      symbol: "SOL",
      decimals: 9,
      visible: true,
      tokenId: "",
      coingeckoId: "",
      chainId: "",
      coin: .sol,
      isShielded: false
    )
    let solToken: QoraiWallet.BlockchainToken = .init(
      contractAddress: "mock-sol-contract-address",
      name: "Sol Token",
      logo: "",
      isCompressed: false,
      isErc20: true,
      isErc721: false,
      isErc1155: false,
      splTokenProgram: .unknown,
      isNft: false,
      isSpam: false,
      symbol: "SOLTOKEN",
      decimals: 9,
      visible: false,
      tokenId: "",
      coingeckoId: "",
      chainId: "",
      coin: .sol,
      isShielded: false
    )
    let solNetwork = QoraiWallet.NetworkInfo.mockSolana

    XCTAssertTrue(solNetwork.isNativeAsset(solCoin))
    XCTAssertFalse(solNetwork.isNativeAsset(solToken))
  }
}
