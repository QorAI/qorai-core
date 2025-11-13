// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiShields
import QoraiWallet
import Foundation

/// The list of action identifiers
///
/// Every action that is shown in the menu must have an identifier created here so that it may be
/// properly displayed and ordered in the new menu customization. The new menu should use every
/// identifier that is usable even if the the action cannot be made in the current context so that
/// user ordering & visibility is consistent.
///
/// **A note on rankings & visibility**:
/// The new menu relies on 2 things for default item display: default ranking & default visibility.
///
/// Default rankings & visibility are currently based on a list in Figma and shouldn't be altered to
/// ensure items don't move around on the user.
///
/// When a new menu item is added it should be given a new default ranking that isn't currently
/// used. Currently all rankings are incremented by 100 to allow for new items to be added in
/// between, so for example a new action identifier could be given a default rank of 175 if we
/// wanted it to be placed second in the list if no user customization has occured or third in the
/// list if it has (reordering sets overriden ranks based on the halfway point between items).
///
/// Default visibility controls whether or not the item appears on the menu without the user tapping
/// "Show All…" to display all actions or explicitly adding it to the menu themselves.
extension Action.Identifier {

  public static let vpn: Self = .init(
    id: "ToggleVPN",
    title: Strings.ActionTitles.vpn,
    qoraiSystemImage: "qora.product.vpn",
    defaultRank: 100,
    defaultVisibility: .visible
  )

  public static let bookmarks: Self = .init(
    id: "Bookmarks",
    title: Strings.bookmarksMenuItem,
    qoraiSystemImage: "qora.product.bookmarks",
    defaultRank: 1600,
    defaultVisibility: .hidden
  )

  public static let downloads: Self = .init(
    id: "Downloads",
    title: Strings.downloadsMenuItem,
    qoraiSystemImage: "qora.folder.download",
    defaultRank: 1700,
    defaultVisibility: .hidden
  )

  public static let history: Self = .init(
    id: "History",
    title: Strings.historyMenuItem,
    qoraiSystemImage: "qora.history",
    defaultRank: 300,
    defaultVisibility: .visible
  )

  public static let qoraiQora: Self = .init(
    id: "QoraiQora",
    title: Strings.ActionTitles.qoraAIChat,
    qoraiSystemImage: "qora.product.qorai-qora",
    defaultRank: 400,
    defaultVisibility: .visible
  )

  public static let qoraiNews: Self = .init(
    id: "QoraiNews",
    title: Strings.ActionTitles.qoraiNews,
    qoraiSystemImage: "qora.product.qorai-news",
    defaultRank: 2500,
    defaultVisibility: .hidden
  )

  public static let qoraiTalk: Self = .init(
    id: "QoraiTalk",
    title: Strings.ActionTitles.qoraiTalk,
    qoraiSystemImage: "qora.product.qorai-talk",
    defaultRank: 2400,
    defaultVisibility: .hidden
  )

  public static let qoraiWallet: Self = .init(
    id: "QoraiWallet",
    title: Strings.Wallet.wallet,
    qoraiSystemImage: "qora.product.qorai-wallet",
    defaultRank: 900,
    defaultVisibility: .visible
  )

  public static let playlist: Self = .init(
    id: "Playlist",
    title: Strings.ActionTitles.playlist,
    qoraiSystemImage: "qora.product.playlist",
    defaultRank: 500,
    defaultVisibility: .visible
  )

  public static let qoraiRewards: Self = .init(
    id: "QoraiRewards",
    title: Strings.ActionTitles.rewards,
    qoraiSystemImage: "qora.product.bat-outline",
    defaultRank: 800,
    defaultVisibility: .visible
  )

  // MARK: - Page Actions

  public static let share: Self = .init(
    id: "Share",
    title: Strings.ActionTitles.share,
    qoraiSystemImage: "qora.share.macos",
    defaultRank: 600,
    defaultVisibility: .visible
  )
  public static let addToPlaylist: Self = .init(
    id: "AddToPlaylist",
    title: Strings.PlayList.toastAddToPlaylistTitle,
    qoraiSystemImage: "qora.product.playlist-add",
    defaultRank: 1200,
    defaultVisibility: .hidden
  )
  public static let toggleNightMode: Self = .init(
    id: "ToggleNightMode",
    title: Strings.NightMode.settingsTitle,
    qoraiSystemImage: "qora.theme.dark",
    defaultRank: 2000,
    defaultVisibility: .hidden
  )
  public static let shredData: Self = .init(
    id: "ShredData",
    title: Strings.Shields.shredSiteData,
    qoraiSystemImage: "qora.shred.data",
    defaultRank: 1000,
    defaultVisibility: .visible
  )
  public static let print: Self = .init(
    id: "PrintPage",
    title: Strings.ActionTitles.print,
    qoraiSystemImage: "qora.print",
    defaultRank: 1800,
    defaultVisibility: .hidden
  )

  // MARK: - Page Activities
  // This list is essentially the same as the ones defined in ShareExtensionHelper

  // A set of all of the page activities defined below.
  public static let allPageActivites: Set<Action.Identifier> = [
    .copyCleanLink,
    .sendURL,
    .toggleReaderMode,
    .translate,
    .findInPage,
    .pageZoom,
    .addFavourites,
    .requestDesktopSite,
    .addSourceNews,
    .createPDF,
    .addSearchEngine,
    .displaySecurityCertificate,
    .reportBrokenSite,
    // Ensure any additional Page activity ID's added below are added to this list since they are
    // not created during menu presentation manually and instead and explicit UIActivity types
    // passed into the share sheet so they will not all exist at all times when creating the menu
  ]

  public static let copyCleanLink: Self = .init(
    id: "CopyCleanLink",
    title: Strings.copyCleanLink,
    qoraiSystemImage: "qora.copy.clean",
    defaultRank: 1300,
    defaultVisibility: .hidden
  )
  public static let sendURL: Self = .init(
    id: "SendURL",
    title: Strings.OpenTabs.sendWebsiteShareActionTitle,
    qoraiSystemImage: "qora.smartphone.laptop",
    defaultRank: 2100,
    defaultVisibility: .hidden
  )
  public static let toggleReaderMode: Self = .init(
    id: "ToggleReaderMode",
    title: Strings.toggleReaderMode,
    qoraiSystemImage: "qora.product.speedreader",
    defaultRank: 1400,
    defaultVisibility: .hidden
  )
  public static let translate: Self = .init(
    id: "TranslatePage",
    title: Strings.ActionTitles.translate,
    qoraiSystemImage: "qora.product.translate",
    defaultRank: 1450,
    defaultVisibility: .hidden
  )
  public static let findInPage: Self = .init(
    id: "FindInPage",
    title: Strings.findInPage,
    qoraiSystemImage: "qora.search",
    defaultRank: 700,
    defaultVisibility: .visible
  )
  public static let pageZoom: Self = .init(
    id: "PageZoom",
    title: Strings.PageZoom.settingsTitle,
    qoraiSystemImage: "qora.font.size",
    defaultRank: 1500,
    defaultVisibility: .hidden
  )
  public static let addFavourites: Self = .init(
    id: "AddFavourites",
    title: Strings.addToFavorites,
    qoraiSystemImage: "qora.star.outline",
    defaultRank: 1100,
    defaultVisibility: .hidden
  )
  public static let addBookmark: Self = .init(
    id: "AddBookmark",
    title: Strings.addToMenuItem,
    qoraiSystemImage: "qora.browser.bookmark-add",
    defaultRank: 200,
    defaultVisibility: .visible
  )
  public static let requestDesktopSite: Self = .init(
    id: "ToggleUserAgent",
    title: Strings.appMenuViewDesktopSiteTitleString,
    qoraiSystemImage: "qora.monitor",
    defaultRank: 2200,
    defaultVisibility: .hidden
  )
  public static let addSourceNews: Self = .init(
    id: "AddSourceNews",
    title: Strings.QoraiNews.addSourceShareTitle,
    qoraiSystemImage: "qora.rss",
    defaultRank: 2600,
    defaultVisibility: .hidden
  )
  public static let createPDF: Self = .init(
    id: "CreatePDF",
    title: Strings.createPDF,
    qoraiSystemImage: "qora.file.new",
    defaultRank: 1900,
    defaultVisibility: .hidden
  )
  public static let addSearchEngine: Self = .init(
    id: "AddSearchEngine",
    title: Strings.CustomSearchEngine.customEngineNavigationTitle,
    qoraiSystemImage: "qora.internet.search",
    defaultRank: 2700,
    defaultVisibility: .hidden
  )
  public static let displaySecurityCertificate: Self = .init(
    id: "DisplaySecurityCertificate",
    title: Strings.displayCertificate,
    qoraiSystemImage: "qora.certificate.valid",
    defaultRank: 2800,
    defaultVisibility: .hidden
  )
  public static let reportBrokenSite: Self = .init(
    id: "ReportBrokenSite",
    title: Strings.Shields.reportABrokenSite,
    qoraiSystemImage: "qora.file.warning",
    defaultRank: 2300,
    defaultVisibility: .hidden
  )
}
