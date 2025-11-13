// swift-tools-version: 5.10
// The swift-tools-version declares the minimum version of Swift required to build this package.

import Foundation
import PackageDescription

// News, Playlist (+JS), Onboarding, Browser (Favicons, Bookmarks, History, Passwords, Reader Mode, Settings, Sync),
// VPN, Rewards, Shields (Privacy, De-Amp, Downloaders, Content Blockers, ...), NTP, Networking,

var package = Package(
  name: "Qorai",
  defaultLocalization: "en",
  platforms: [.iOS(.v17), .macOS(.v14)],
  products: [
    .library(name: "Qorai", targets: ["Qorai"]),
    .library(name: "Shared", targets: ["Shared"]),
    .library(
      name: "QoraiCore",
      targets: ["QoraiCore", "PartitionAllocSupport"]
    ),
    .library(name: "QoraiShared", targets: ["QoraiShared"]),
    .library(name: "QoraiShields", targets: ["QoraiShields"]),
    .library(name: "QoraiUI", targets: ["QoraiUI"]),
    .library(name: "DesignSystem", targets: ["DesignSystem", "NalaAssets"]),
    .library(name: "QoraiWallet", targets: ["QoraiWallet"]),
    .library(name: "Data", targets: ["Data"]),
    .library(name: "DataImporter", targets: ["DataImporter"]),
    .library(name: "Storage", targets: ["Storage"]),
    .library(name: "BrowserIntentsModels", targets: ["BrowserIntentsModels"]),
    .library(name: "QoraiWidgetsModels", targets: ["QoraiWidgetsModels"]),
    .library(name: "Strings", targets: ["Strings"]),
    .library(name: "QoraiStrings", targets: ["QoraiStrings"]),
    .library(name: "QoraiVPN", targets: ["QoraiVPN"]),
    .library(name: "QoraiNews", targets: ["QoraiNews"]),
    .library(name: "AIChat", targets: ["AIChat"]),
    .library(name: "QoraiStore", targets: ["QoraiStore"]),
    .library(name: "Favicon", targets: ["Favicon"]),
    .library(name: "FaviconModels", targets: ["FaviconModels"]),
    .library(name: "SpeechRecognition", targets: ["SpeechRecognition"]),
    .library(name: "Onboarding", targets: ["Onboarding"]),
    .library(name: "Growth", targets: ["Growth"]),
    .library(name: "RuntimeWarnings", targets: ["RuntimeWarnings"]),
    .library(name: "CodableHelpers", targets: ["CodableHelpers"]),
    .library(name: "GRDWireGuardKit", targets: ["GRDWireGuardKit"]),
    .library(name: "Preferences", targets: ["Preferences"]),
    .library(name: "PrivateCDN", targets: ["PrivateCDN"]),
    .library(name: "CertificateUtilities", targets: ["CertificateUtilities"]),
    .library(name: "Playlist", targets: ["Playlist"]),
    .library(name: "UserAgent", targets: ["UserAgent"]),
    .library(name: "CredentialProviderUI", targets: ["CredentialProviderUI"]),
    .library(name: "PlaylistUI", targets: ["PlaylistUI"]),
    .library(name: "BrowserMenu", targets: ["BrowserMenu"]),
    .library(name: "Web", targets: ["Web"]),
    .library(name: "QoraiTalk", targets: ["QoraiTalk"]),
    .library(name: "Origin", targets: ["Origin"]),
    .executable(name: "QoraAssetCatalogGenerator", targets: ["QoraAssetCatalogGenerator"]),
    .plugin(name: "IntentBuilderPlugin", targets: ["IntentBuilderPlugin"]),
    .plugin(name: "LoggerPlugin", targets: ["LoggerPlugin"]),
    .plugin(name: "QoraAssetsPlugin", targets: ["QoraAssetsPlugin"]),
  ],
  dependencies: [
    .package(url: "https://github.com/SnapKit/SnapKit", from: "5.0.1"),
    .package(url: "https://github.com/cezheng/Fuzi", from: "3.1.3"),
    .package(url: "https://github.com/airbnb/lottie-spm", from: "4.4.3"),
    .package(url: "https://github.com/SDWebImage/SDWebImage", exact: "5.10.3"),
    .package(url: "https://github.com/SDWebImage/SDWebImageSwiftUI", from: "2.2.0"),
    .package(url: "https://github.com/nmdias/FeedKit", from: "9.1.2"),
    .package(
      url: "https://github.com/qorai/PanModal",
      revision: "e67e9eff53c05f19b41bbb2ca7d27ff5859a586c"
    ),
    .package(url: "https://github.com/apple/swift-collections", from: "1.0.0"),
    .package(url: "https://github.com/siteline/SwiftUI-Introspect", from: "0.1.3"),
    .package(url: "https://github.com/apple/swift-algorithms", from: "1.0.0"),
    .package(url: "https://github.com/devxoul/Then", from: "2.7.0"),
    .package(url: "https://github.com/mkrd/Swift-BigInt", from: "2.3.0"),
    .package(url: "https://github.com/GuardianFirewall/GuardianConnect", exact: "2.1.1"),
    .package(url: "https://github.com/pointfreeco/swift-custom-dump", from: "0.6.0"),
    .package(
      url: "https://github.com/venmo/Static",
      revision: "622a6804d39515600ead16e6259cb5d5e50f40df"
    ),
    .package(name: "JitsiMeet", path: "../third_party/JitsiMeet"),
  ],
  targets: [
    .target(
      name: "Qorai",
      dependencies: [
        "QoraiShared",
        "Shared",
        "QoraiWallet",
        "QoraiCore",
        "PartitionAllocSupport",
        "QoraiUI",
        "DesignSystem",
        "Data",
        "DataImporter",
        "Storage",
        "Fuzi",
        "SnapKit",
        "Static",
        "SDWebImage",
        "Then",
        "BrowserIntentsModels",
        "QoraiWidgetsModels",
        "QoraiVPN",
        "QoraiNews",
        "AIChat",
        "QoraiStore",
        "Onboarding",
        "Growth",
        "SpeechRecognition",
        "CodableHelpers",
        "Preferences",
        "Favicon",
        "CertificateUtilities",
        "Playlist",
        "UserAgent",
        .product(name: "Lottie", package: "lottie-spm"),
        .product(name: "Collections", package: "swift-collections"),
        "PlaylistUI",
        "BrowserMenu",
        "Web",
        "QoraiShields",
        "QoraiTalk",
        "Origin",
      ],
      exclude: [
        "Frontend/UserContent/UserScripts/AllFrames",
        "Frontend/UserContent/UserScripts/MainFrame",
        "Frontend/UserContent/UserScripts/Sandboxed",
      ],
      resources: [
        .copy("Assets/About/Licenses.html"),
        .copy("Assets/About/AboutHome.html"),
        .copy("Assets/__firefox__.js"),
        .copy("Assets/AllFramesAtDocumentEnd.js"),
        .copy("Assets/AllFramesAtDocumentEndSandboxed.js"),
        .copy("Assets/AllFramesAtDocumentStart.js"),
        .copy("Assets/AllFramesAtDocumentStartSandboxed.js"),
        .copy("Assets/MainFrameAtDocumentEnd.js"),
        .copy("Assets/MainFrameAtDocumentEndSandboxed.js"),
        .copy("Assets/MainFrameAtDocumentStart.js"),
        .copy("Assets/MainFrameAtDocumentStartSandboxed.js"),
        .copy("Assets/Fonts/FiraSans-Bold.ttf"),
        .copy("Assets/Fonts/FiraSans-BoldItalic.ttf"),
        .copy("Assets/Fonts/FiraSans-Book.ttf"),
        .copy("Assets/Fonts/FiraSans-Italic.ttf"),
        .copy("Assets/Fonts/FiraSans-Light.ttf"),
        .copy("Assets/Fonts/FiraSans-Medium.ttf"),
        .copy("Assets/Fonts/FiraSans-Regular.ttf"),
        .copy("Assets/Fonts/FiraSans-SemiBold.ttf"),
        .copy("Assets/Fonts/FiraSans-UltraLight.ttf"),
        .copy("Assets/Fonts/NewYorkMedium-Bold.otf"),
        .copy("Assets/Fonts/NewYorkMedium-BoldItalic.otf"),
        .copy("Assets/Fonts/NewYorkMedium-Regular.otf"),
        .copy("Assets/Fonts/NewYorkMedium-RegularItalic.otf"),
        .copy("Assets/Interstitial Pages/Pages/BlockedDomain.html"),
        .copy("Assets/Interstitial Pages/Pages/HTTPBlocked.html"),
        .copy("Assets/Interstitial Pages/Pages/CertificateError.html"),
        .copy("Assets/Interstitial Pages/Pages/GenericError.html"),
        .copy("Assets/Interstitial Pages/Pages/NetworkError.html"),
        .copy("Assets/Interstitial Pages/Pages/Web3Domain.html"),
        .copy("Assets/Interstitial Pages/Images/Carret.png"),
        .copy("Assets/Interstitial Pages/Images/Clock.svg"),
        .copy("Assets/Interstitial Pages/Images/Cloud.svg"),
        .copy("Assets/Interstitial Pages/Images/DarkWarning.svg"),
        .copy("Assets/Interstitial Pages/Images/Generic.svg"),
        .copy("Assets/Interstitial Pages/Images/Globe.svg"),
        .copy("Assets/Interstitial Pages/Images/Info.svg"),
        .copy("Assets/Interstitial Pages/Images/Warning.svg"),
        .copy("Assets/Interstitial Pages/Images/warning-triangle-outline.svg"),
        .copy("Assets/Interstitial Pages/Styles/BlockedDomain.css"),
        .copy("Assets/Interstitial Pages/Styles/CertificateError.css"),
        .copy("Assets/Interstitial Pages/Styles/InterstitialStyles.css"),
        .copy("Assets/Interstitial Pages/Styles/NetworkError.css"),
        .copy("Assets/Interstitial Pages/Styles/Web3Domain.css"),
        .copy("Assets/Lottie/shred.json"),
        .copy("Assets/SearchPlugins"),
        .copy("Frontend/Reader/Reader.css"),
        .copy("Frontend/Reader/Reader.html"),
        .copy("Frontend/Reader/ReaderViewLoading.html"),
        .copy("Frontend/Browser/New Tab Page/Backgrounds/Assets/NTP_Images/corwin-prescott-3.jpg"),
        .copy("Frontend/Browser/Favorites/Data/top_sites_by_region.json"),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/DomainSpecific/Paged/QoraiSearchResultAdScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/DomainSpecific/Paged/QoraiSearchScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/DomainSpecific/Paged/QoraiSkusScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/DomainSpecific/Paged/PlaylistFolderSharingScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/DomainSpecific/Paged/FrameCheckWrapper.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/CookieControlScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/FarblingProtectionScript.js"
        ),
        .copy("Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/gpc.js"),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/MediaBackgroundingScript.js"
        ),
        .copy("Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/PlaylistScript.js"),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/PlaylistSwizzlerScript.js"
        ),
        .copy("Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/ReadyStateScript.js"),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/RequestBlockingScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/TrackingProtectionStats.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/WalletEthereumProviderScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/WalletSolanaProviderScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Paged/YoutubeQualityScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Sandboxed/QoraiQoraScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Sandboxed/DarkReaderScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Sandboxed/QoraiTranslateScript.js"
        ),
        .copy("Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Sandboxed/DeAmpScript.js"),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Sandboxed/FaviconScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Sandboxed/ResourceDownloaderScript.js"
        ),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/Sandboxed/SiteStateListenerScript.js"
        ),
        .copy("WebFilters/ContentBlocker/Lists/block-ads.json"),
        .copy("WebFilters/ContentBlocker/Lists/block-cookies.json"),
        .copy("WebFilters/ContentBlocker/Lists/block-trackers.json"),
        .copy("WebFilters/ContentBlocker/Lists/mixed-content-upgrade.json"),
        .copy("WebFilters/ShieldStats/Adblock/Resources/ABPFilterParserData.dat"),
        .copy(
          "Frontend/UserContent/UserScripts/Scripts_Dynamic/Scripts/DomainSpecific/Paged/QoraiTalkScript.js"
        ),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "Shared",
      dependencies: [
        "QoraiCore",
        "Strings",
      ],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "QoraiShared",
      dependencies: ["QoraiCore", "Shared", "Preferences"],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "CertificateUtilities",
      dependencies: ["Shared"],
      plugins: ["LoggerPlugin"]
    ),
    .testTarget(
      name: "CertificateUtilitiesTests",
      dependencies: [
        "CertificateUtilities", "QoraiShared", "QoraiCore",
        "PartitionAllocSupport",
      ],
      exclude: ["Certificates/self-signed.conf"],
      resources: [
        .copy("Certificates/certviewer/qorai.com.cer"),
        .copy("Certificates/certviewer/github.com.cer"),
      ]
    ),
    .target(name: "QoraiStrings", dependencies: ["Strings", "Preferences"]),
    .target(
      name: "Growth",
      dependencies: [
        "QoraiVPN", "Shared", "QoraiShared", "Strings", "SnapKit", "CertificateUtilities",
        .product(name: "OrderedCollections", package: "swift-collections"),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "SpeechRecognition",
      dependencies: ["QoraiUI", "Shared", "QoraiShared", "Preferences", "Data"],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "QoraiUI",
      dependencies: [
        "Strings",
        "DesignSystem",
        "PanModal",
        "SDWebImage",
        "SnapKit",
        .product(name: "Introspect", package: "SwiftUI-Introspect"),
        "Then",
        "Static",
        "Preferences",
        "Shared",
        .product(name: "Lottie", package: "lottie-spm"),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "QoraiShields",
      dependencies: ["Strings", "Preferences", "QoraiCore", "Web", "Data"],
      plugins: ["LoggerPlugin"]
    ),
    .testTarget(
      name: "QoraiShieldsTests",
      dependencies: ["QoraiShields", "Data", "Preferences", "TestHelpers", "Web"]
    ),
    .target(
      name: "DesignSystem",
      dependencies: ["Then", "NalaAssets"],
      plugins: ["QoraAssetsPlugin"]
    ),
    .binaryTarget(name: "NalaAssets", path: "../../../out/ios_current_link/NalaAssets.xcframework"),
    .binaryTarget(
      name: "PartitionAllocSupport",
      path: "../../../out/ios_current_link/PartitionAllocSupport.xcframework"
    ),
    .binaryTarget(name: "QoraiCore", path: "../../../out/ios_current_link/QoraiCore.xcframework"),
    .binaryTarget(
      name: "GRDWireGuardKit",
      path: "../third_party/GRDWireGuardKit/GRDWireGuardKit.xcframework"
    ),
    .target(
      name: "Storage",
      dependencies: ["Shared"],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "Data",
      dependencies: ["QoraiShared", "Storage", "Strings", "Preferences", "Shared"],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "DataImporter",
      dependencies: [
        "QoraiCore",
        "QoraiShared",
        "QoraiStrings",
        "QoraiUI",
        "DesignSystem",
        "Growth",
        "Strings",
        .product(name: "Collections", package: "swift-collections"),
        .product(name: "Introspect", package: "SwiftUI-Introspect"),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "QoraiWallet",
      dependencies: [
        "Data",
        "QoraiCore",
        "PartitionAllocSupport",
        "QoraiShared",
        "QoraiUI",
        "DesignSystem",
        "Favicon",
        "Strings",
        "PanModal",
        "SDWebImageSwiftUI",
        "SnapKit",
        "Then",
        "Shared",
        "QoraiStrings",
        .product(name: "BigNumber", package: "Swift-BigInt"),
        .product(name: "Algorithms", package: "swift-algorithms"),
        .product(name: "Collections", package: "swift-collections"),
        .product(name: "Introspect", package: "SwiftUI-Introspect"),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "BrowserIntentsModels",
      dependencies: ["Shared"],
      sources: ["BrowserIntents.intentdefinition", "CustomIntentHandler.swift"],
      plugins: ["IntentBuilderPlugin"]
    ),
    .target(
      name: "QoraiWidgetsModels",
      dependencies: ["FaviconModels"],
      sources: [
        "QoraiWidgets.intentdefinition", "LockScreenFavoriteIntentHandler.swift",
        "FavoritesWidgetData.swift",
      ],
      plugins: ["IntentBuilderPlugin", "LoggerPlugin"]
    ),
    .target(name: "TestHelpers", dependencies: ["Data", "QoraiShared"]),
    .target(
      name: "QoraiVPN",
      dependencies: [
        "QoraiStore",
        "QoraiStrings",
        "SnapKit",
        "Then",
        "Data",
        "GuardianConnect",
        "QoraiUI",
        .product(name: "Lottie", package: "lottie-spm"),
      ],
      resources: [.copy("Resources/vpncheckmark.json")],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "QoraiNews",
      dependencies: [
        "QoraiCore",
        "QoraiShared",
        "QoraiStrings",
        "QoraiUI",
        "CodableHelpers",
        "Data",
        "DesignSystem",
        "FeedKit",
        "Fuzi",
        "Growth",
        "Preferences",
        "Shared",
        "SnapKit",
        "Storage",
        "Strings",
        "Then",
        .product(name: "Collections", package: "swift-collections"),
        .product(name: "Introspect", package: "SwiftUI-Introspect"),
        .product(name: "Lottie", package: "lottie-spm"),
      ],
      resources: [
        .copy("Lottie Assets/qorai-today-welcome-graphic.json")
      ],
      plugins: ["LoggerPlugin"]
    ),
    .target(
      name: "AIChat",
      dependencies: [
        "QoraiCore",
        "QoraiShared",
        "QoraiStore",
        "QoraiStrings",
        "QoraiUI",
        "DesignSystem",
        "Favicon",
        "Fuzi",
        "Preferences",
        "Strings",
        "SpeechRecognition",
        .product(name: "Collections", package: "swift-collections"),
        .product(name: "Introspect", package: "SwiftUI-Introspect"),
        .product(name: "Lottie", package: "lottie-spm"),
      ],
      resources: [
        .copy("Components/Markdown/Code Highlight/Themes/atom-one-dark.min.css"),
        .copy("Components/Markdown/Code Highlight/Themes/atom-one-light.min.css"),
        .copy("Components/Markdown/Code Highlight/Scripts/highlight.min.js"),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .testTarget(
      name: "AIChatTests",
      dependencies: ["AIChat"],
      resources: [
        .copy("Components/Markdown/Code Highlight/Themes/atom-one-dark.min.css"),
        .copy("Components/Markdown/Code Highlight/Themes/atom-one-light.min.css"),
        .copy("Components/Markdown/Code Highlight/Scripts/highlight.min.js"),
      ]
    ),
    .target(
      name: "QoraiStore",
      dependencies: [
        "QoraiCore",
        "QoraiShared",
        "QoraiStrings",
        "QoraiUI",
        "DesignSystem",
        "Preferences",
        .product(name: "Collections", package: "swift-collections"),
        .product(name: "Introspect", package: "SwiftUI-Introspect"),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .target(name: "Preferences", dependencies: ["Shared"], plugins: ["LoggerPlugin"]),
    .target(
      name: "Onboarding",
      dependencies: [
        "QoraiCore",
        "QoraiShared",
        "QoraiStrings",
        "QoraiUI",
        "DesignSystem",
        "Growth",
        .product(name: "Lottie", package: "lottie-spm"),
        "Preferences",
        "Shared",
        "SnapKit",
        "Storage",
      ],
      resources: [
        .copy("LottieAssets/onboarding-rewards.json"),
        .copy("LottieAssets/playlist-confetti.json"),
        .copy("WelcomeFocus/Resources/LottieAssets"),
        .copy("WelcomeFocus/Resources/Videos"),
        .copy("WelcomeFocus/Resources/Fonts/Poppins-SemiBold.ttf"),
        .copy("WelcomeFocus/Resources/Fonts/Poppins-Medium.ttf"),
        .copy("WelcomeFocus/Resources/Fonts/Poppins-Regular.ttf"),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .testTarget(
      name: "QoraiNewsTests",
      dependencies: ["QoraiNews"],
      resources: [
        .copy("opml-test-files/subscriptionList.opml"),
        .copy("opml-test-files/states.opml"),
      ]
    ),
    .target(name: "CodableHelpers"),
    .target(name: "FaviconModels", dependencies: ["Shared"]),
    .target(
      name: "Favicon",
      dependencies: [
        "FaviconModels",
        "QoraiCore",
        "QoraiShared",
        "Shared",
        "SDWebImage",
      ],
      resources: [
        .copy("Assets/top_sites.json"),
        .copy("Assets/TopSites"),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .target(name: "UserAgent", dependencies: ["Preferences", "QoraiCore"]),
    .target(
      name: "CredentialProviderUI",
      dependencies: ["QoraiCore", "DesignSystem", "QoraiShared", "Strings", "QoraiUI"]
    ),
    .testTarget(name: "UserAgentTests", dependencies: ["UserAgent", "Qorai"]),
    .testTarget(name: "SharedTests", dependencies: ["Shared"]),
    .testTarget(
      name: "QoraiSharedTests",
      dependencies: ["QoraiShared", "Preferences"]
    ),
    .testTarget(
      name: "QoraiVPNTests",
      dependencies: ["QoraiVPN", "QoraiShared", "GuardianConnect"]
    ),
    .testTarget(
      name: "QoraiWalletTests",
      dependencies: [
        "QoraiWallet",
        "TestHelpers",
        .product(name: "CustomDump", package: "swift-custom-dump"),
      ]
    ),
    .testTarget(
      name: "StorageTests",
      dependencies: ["Storage", "TestHelpers"],
      resources: [.copy("fixtures/v33.db"), .copy("testcert1.pem"), .copy("testcert2.pem")]
    ),
    .testTarget(name: "DataTests", dependencies: ["Data", "TestHelpers", "QoraiShields"]),
    .testTarget(
      name: "ClientTests",
      dependencies: ["Qorai", "QoraiStrings", "TestHelpers"],
      resources: [
        .copy("Resources/debouncing.json"),
        .copy("Resources/content-blocking.json"),
        .copy("Resources/filter-lists.json"),
        .copy("Resources/google-search-plugin.xml"),
        .copy("Resources/duckduckgo-search-plugin.xml"),
        .copy("Resources/ad-block-resources/resources.json"),
        .copy("Resources/filter-rules/iodkpdagapdfkphljnddpjlldadblomo.txt"),
        .copy("Resources/html/index.html"),
        .copy("Resources/scripts/farbling-tests.js"),
        .copy("Resources/scripts/request-blocking-tests.js"),
        .copy("Resources/scripts/cosmetic-filter-tests.js"),
      ]
    ),
    .target(name: "Strings"),
    .target(name: "RuntimeWarnings"),
    .target(name: "PrivateCDN", dependencies: ["SDWebImage"]),
    .target(
      name: "Playlist",
      dependencies: [
        "Data", "QoraiShared", "Shared", "Storage", "Preferences", "Strings", "CodableHelpers",
        "UserAgent", "Then", "QoraiShields",
      ],
      plugins: ["LoggerPlugin"]
    ),
    .testTarget(name: "PrivateCDNTests", dependencies: ["PrivateCDN"]),
    .testTarget(
      name: "GrowthTests",
      dependencies: ["Growth", "Shared", "QoraiShared", "QoraiVPN"]
    ),
    .target(
      name: "PlaylistUI",
      dependencies: [
        "Favicon", "Data", "DesignSystem", "Playlist", "SDWebImage", "SnapKit", "Strings",
        "CodableHelpers", .product(name: "Algorithms", package: "swift-algorithms"), "QoraiStrings",
        .product(name: "OrderedCollections", package: "swift-collections"), "QoraiUI",
      ],
      resources: [.copy("Resources/oembed_providers.json")]
    ),
    .testTarget(
      name: "PlaylistUITests",
      dependencies: ["PlaylistUI", "Playlist", "Preferences", "Data", "TestHelpers"],
      resources: [.copy("Resources/Big_Buck_Bunny_360_10s_1MB.mp4")]
    ),
    .target(
      name: "BrowserMenu",
      dependencies: [
        "DesignSystem", "QoraiUI", "Preferences", "Strings", "QoraiStrings", "QoraiVPN",
        "GuardianConnect", "QoraiWallet", "QoraiShields",
      ]
    ),
    .target(
      name: "Web",
      dependencies: [
        "QoraiCore", "FaviconModels", "QoraiShared", "Shared", "CertificateUtilities", "Storage",
        "QoraiStrings", "Strings",
        .product(name: "OrderedCollections", package: "swift-collections"),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .testTarget(name: "BrowserMenuTests", dependencies: ["BrowserMenu"]),
    .plugin(name: "IntentBuilderPlugin", capability: .buildTool()),
    .plugin(name: "LoggerPlugin", capability: .buildTool()),
    .plugin(
      name: "QoraAssetsPlugin",
      capability: .buildTool()
    ),
    .executableTarget(name: "QoraAssetCatalogGenerator"),
    .target(
      name: "QoraiTalk",
      dependencies: [
        "Shared", "Preferences", "JitsiMeet", "QoraiCore",
        .product(name: "Collections", package: "swift-collections"),
      ],
      plugins: ["LoggerPlugin"]
    ),
    .testTarget(
      name: "QoraiTalkTests",
      dependencies: [
        "QoraiTalk", "Shared", "TestHelpers", "QoraiCore",
        .product(name: "Collections", package: "swift-collections"),
      ]
    ),
    .target(
      name: "Origin",
      dependencies: ["DesignSystem", "Strings"]
    ),
  ],
  cxxLanguageStandard: .cxx17
)

let iosRootDirectory = URL(string: #file)!.deletingLastPathComponent().absoluteString.dropLast()
let isStripAbsolutePathsFromDebugSymbolsEnabled = {
  do {
    let env = try String(contentsOfFile: "\(iosRootDirectory)/../../.env", encoding: .utf8)
      .split(separator: "\n")
      .map { $0.split(separator: "=").map { $0.trimmingCharacters(in: .whitespacesAndNewlines) } }
    return env.contains(where: { $0.first == "use_remoteexec" && $0.last == "true" })
  } catch {
    return false
  }
}()

if isStripAbsolutePathsFromDebugSymbolsEnabled {
  for target in package.targets where target.type == .regular || target.type == .test {
    var settings = target.swiftSettings ?? []
    settings.append(
      .unsafeFlags(
        [
          "-debug-prefix-map", "\(iosRootDirectory)=../../qorai/ios/qorai-ios",
        ],
        .when(configuration: .debug)
      )
    )
    target.swiftSettings = settings
  }
}
