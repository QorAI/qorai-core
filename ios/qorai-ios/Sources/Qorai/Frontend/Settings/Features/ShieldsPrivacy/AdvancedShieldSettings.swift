// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiNews
import QoraiShared
import QoraiShields
import Combine
import Data
import Foundation
import Growth
import Preferences
import Web
import os

@MainActor class AdvancedShieldsSettings: ObservableObject {
  struct ClearableSetting: Identifiable {
    enum ClearableType: String {
      case history, cache, cookiesAndCache, passwords, downloads, qoraiNews, playlistCache,
        playlistData, recentSearches, qoraiAdsData
    }

    var id: ClearableType
    var clearable: Clearable
    var isEnabled: Bool
  }

  @Published var blockMobileAnnoyances: Bool {
    didSet {
      FilterListStorage.shared.ensureFilterList(
        for: AdblockFilterListCatalogEntry.mobileAnnoyancesComponentID,
        isEnabled: blockMobileAnnoyances
      )
    }
  }
  var isP3AManaged: Bool {
    p3aUtilities.isP3APreferenceManaged
  }
  var isStatsReportingManaged: Bool {
    qoraiStats.isStatsReportingManaged
  }
  @Published var isStatsReportingEnabled: Bool {
    didSet {
      qoraiStats.isStatsReportingEnabled = isStatsReportingEnabled
    }
  }
  @Published var isP3AEnabled: Bool {
    didSet {
      p3aUtilities.isP3AEnabled = isP3AEnabled
    }
  }
  @Published var isDeAmpEnabled: Bool {
    didSet {
      deAmpPrefs.isDeAmpEnabled = isDeAmpEnabled
    }
  }
  @Published var isDebounceEnabled: Bool {
    didSet {
      guard debounceService != nil else {
        isDebounceEnabled = false
        return
      }

      debounceService?.isEnabled = isDebounceEnabled
    }
  }
  @Published var adBlockAndTrackingPreventionLevel: ShieldLevel {
    didSet {
      guard oldValue != adBlockAndTrackingPreventionLevel else { return }
      if FeatureList.kQoraiShieldsContentSettings.enabled {
        qoraiShieldsSettings?.defaultAdBlockMode = adBlockAndTrackingPreventionLevel.adBlockMode
      }
      // Also assign to existing pref until deprecated so reverse migration is not required
      Preferences.Shields.blockAdsAndTrackingLevel = adBlockAndTrackingPreventionLevel
    }
  }
  @Published var isBlockScriptsEnabled: Bool {
    didSet {
      guard oldValue != isBlockScriptsEnabled else { return }
      if FeatureList.kQoraiShieldsContentSettings.enabled {
        qoraiShieldsSettings?.isBlockScriptsEnabledByDefault = isBlockScriptsEnabled
      }
      // Also assign to existing pref until deprecated so reverse migration is not required
      Preferences.Shields.blockScripts.value = isBlockScriptsEnabled
    }
  }
  @Published var isBlockFingerprintingEnabled: Bool {
    didSet {
      guard oldValue != isBlockFingerprintingEnabled else { return }
      if FeatureList.kQoraiShieldsContentSettings.enabled {
        qoraiShieldsSettings?.defaultFingerprintMode =
          isBlockFingerprintingEnabled ? .standardMode : .allowMode
      }
      // Also assign to existing pref until deprecated so reverse migration is not required
      Preferences.Shields.fingerprintingProtection.value = isBlockFingerprintingEnabled
    }
  }
  @Published var httpsUpgradeLevel: HTTPSUpgradeLevel {
    didSet {
      Preferences.Shields.httpsUpgradeLevel = httpsUpgradeLevel
      HttpsUpgradeServiceFactory.get(privateMode: false)?.clearAllowlist(
        fromStart: Date.distantPast,
        end: Date.distantFuture
      )
    }
  }
  @Published var shredLevel: SiteShredLevel {
    didSet {
      // TODO: Support AutoShred via content settings qorai-browser#47753
      Preferences.Shields.shredLevel = shredLevel
    }
  }
  @Published var shredHistoryItems: Bool {
    didSet {
      Preferences.Shields.shredHistoryItems.value = shredHistoryItems
    }
  }

  @Published var isSaveContactInfoEnabled: Bool = false {
    didSet {
      guard let webcompatReporterHandler else {
        isSaveContactInfoEnabled = false
        return
      }

      webcompatReporterHandler.setContactInfoSaveFlag(value: isSaveContactInfoEnabled)
    }
  }

  @Published var isSurveyPanelistEnabled: Bool = false {
    didSet {
      rewards?.ads.isSurveyPanelistEnabled = isSurveyPanelistEnabled
    }
  }

  typealias ClearDataCallback = @MainActor (Bool, Bool) -> Void
  @Published var clearableSettings: [ClearableSetting]

  private var subscriptions: [AnyCancellable] = []
  private let p3aUtilities: QoraiP3AUtils
  private let deAmpPrefs: DeAmpPrefs
  private let debounceService: (any DebounceService)?
  private let qoraiShieldsSettings: (any QoraiShieldsSettings)?
  private let rewards: QoraiRewards?
  private let clearDataCallback: ClearDataCallback
  private let qoraiStats: QoraiStats
  private let webcompatReporterHandler: WebcompatReporterWebcompatReporterHandler?
  let tabManager: TabManager

  init(
    profile: LegacyBrowserProfile,
    tabManager: TabManager,
    feedDataSource: FeedDataSource,
    debounceService: (any DebounceService)?,
    qoraiShieldsSettings: (any QoraiShieldsSettings)?,
    qoraiCore: QoraiProfileController,
    p3aUtils: QoraiP3AUtils,
    rewards: QoraiRewards?,
    qoraiStats: QoraiStats,
    webcompatReporterHandler: WebcompatReporterWebcompatReporterHandler?,
    clearDataCallback: @escaping ClearDataCallback
  ) {
    self.p3aUtilities = p3aUtils
    self.deAmpPrefs = qoraiCore.deAmpPrefs
    self.debounceService = debounceService
    self.qoraiShieldsSettings = qoraiShieldsSettings
    self.tabManager = tabManager
    self.isP3AEnabled = p3aUtilities.isP3AEnabled
    self.isStatsReportingEnabled = qoraiStats.isStatsReportingEnabled
    self.rewards = rewards
    self.clearDataCallback = clearDataCallback
    self.qoraiStats = qoraiStats
    if FeatureList.kQoraiShieldsContentSettings.enabled {
      self.adBlockAndTrackingPreventionLevel =
        qoraiShieldsSettings?.defaultAdBlockMode.shieldLevel ?? .standard
      self.isBlockScriptsEnabled = qoraiShieldsSettings?.isBlockScriptsEnabledByDefault ?? false
      self.isBlockFingerprintingEnabled =
        (qoraiShieldsSettings?.defaultFingerprintMode ?? .standardMode) == .standardMode
    } else {
      self.adBlockAndTrackingPreventionLevel = Preferences.Shields.blockAdsAndTrackingLevel
      self.isBlockScriptsEnabled = Preferences.Shields.blockScripts.value
      self.isBlockFingerprintingEnabled = Preferences.Shields.fingerprintingProtection.value
    }
    self.httpsUpgradeLevel = Preferences.Shields.httpsUpgradeLevel
    self.isDeAmpEnabled = deAmpPrefs.isDeAmpEnabled
    self.isDebounceEnabled = debounceService?.isEnabled ?? false
    // TODO: Support AutoShred via content settings qorai-browser#47753
    self.shredLevel = Preferences.Shields.shredLevel
    self.shredHistoryItems = Preferences.Shields.shredHistoryItems.value
    self.webcompatReporterHandler = webcompatReporterHandler
    self.isSurveyPanelistEnabled = rewards?.ads.isSurveyPanelistEnabled ?? false

    blockMobileAnnoyances = FilterListStorage.shared.isEnabled(
      for: AdblockFilterListCatalogEntry.mobileAnnoyancesComponentID
    )

    var clearableSettings = [
      ClearableSetting(
        id: .history,
        clearable: HistoryClearable(
          historyAPI: qoraiCore.historyAPI,
          httpsUpgradeService: HttpsUpgradeServiceFactory.get(privateMode: false)
        ),
        isEnabled: true
      ),
      ClearableSetting(id: .cache, clearable: CacheClearable(), isEnabled: true),
      ClearableSetting(
        id: .cookiesAndCache,
        clearable: CookiesAndCacheClearable(),
        isEnabled: true
      ),
      ClearableSetting(
        id: .passwords,
        clearable: PasswordsClearable(profile: profile),
        isEnabled: true
      ),
      ClearableSetting(id: .downloads, clearable: DownloadsClearable(), isEnabled: true),
    ]
    if qoraiCore.profile.prefs.isQoraiNewsAvailable {
      clearableSettings.append(
        ClearableSetting(
          id: .qoraiNews,
          clearable: QoraiNewsClearable(feedDataSource: feedDataSource),
          isEnabled: true
        )
      )
    }

    // Enable clearing of Qorai Ads data only if:
    // - Qorai Ads is running
    // - Qorai Rewards is disabled
    if let rewards, !rewards.isEnabled, rewards.ads.isServiceRunning() {
      clearableSettings.append(
        ClearableSetting(
          id: .qoraiAdsData,
          clearable: QoraiAdsDataClearable(rewards: rewards),
          isEnabled: false
        )
      )
    }

    if qoraiCore.profile.prefs.isPlaylistAvailable {
      clearableSettings += [
        ClearableSetting(id: .playlistCache, clearable: PlayListCacheClearable(), isEnabled: false),
        ClearableSetting(id: .playlistData, clearable: PlayListDataClearable(), isEnabled: false),
      ]
    }

    clearableSettings.append(
      ClearableSetting(id: .recentSearches, clearable: RecentSearchClearable(), isEnabled: true)
    )

    let savedToggles = Preferences.Privacy.clearPrivateDataToggles.value

    // Ensure if we ever add an option to the list of clearables we don't crash
    if savedToggles.count == clearableSettings.count {
      for index in 0..<clearableSettings.count {
        clearableSettings[index].isEnabled = savedToggles[index]
      }
    }

    self.clearableSettings = clearableSettings
    registerSubscriptions()
    Task { @MainActor in
      self.isSaveContactInfoEnabled = await webcompatReporterHandler?.browserParams().1 ?? false
    }
  }

  func clearPrivateData(_ clearables: [Clearable]) async {
    clearDataCallback(true, false)
    let isHistoryCleared = await clearPrivateDataInternal(clearables)
    clearDataCallback(false, isHistoryCleared)
  }

  private func clearPrivateDataInternal(_ clearables: [Clearable]) async -> Bool {
    @Sendable func _clear(_ clearables: [Clearable], secondAttempt: Bool = false) async {
      await withThrowingTaskGroup(of: Void.self) { group in
        for clearable in clearables {
          group.addTask {
            try await clearable.clear()
          }
        }
        do {
          for try await _ in group {}
        } catch {
          if !secondAttempt {
            Logger.module.error("Private data NOT cleared successfully")
            try? await Task.sleep(nanoseconds: NSEC_PER_MSEC * 500)
            await _clear(clearables, secondAttempt: true)
          } else {
            Logger.module.error("Private data NOT cleared after 2 attempts")
          }
        }
      }
    }

    let clearAffectsTabs = clearables.contains { item in
      return item is CacheClearable || item is CookiesAndCacheClearable
    }

    let historyCleared = clearables.contains { $0 is HistoryClearable }

    if clearAffectsTabs {
      DispatchQueue.main.async {
        self.tabManager.allTabs.forEach({ $0.reload() })
      }
    }

    @Sendable func _toggleFolderAccessForBlockCookies(locked: Bool) async {
      do {
        if Preferences.Privacy.blockAllCookies.value,
          try await AsyncFileManager.default.isWebDataLocked(atPath: .cookie) != locked
        {
          try await AsyncFileManager.default.setWebDataAccess(atPath: .cookie, lock: locked)
          try await AsyncFileManager.default.setWebDataAccess(atPath: .websiteData, lock: locked)
        }
      } catch {
        Logger.module.error("Failed to change web data access to \(locked)")
      }
    }

    try? await Task.sleep(nanoseconds: NSEC_PER_SEC * 1)

    // Reset Webkit configuration to remove data from memory
    if clearAffectsTabs {
      self.tabManager.reset()
      // This will recreate the webview for the selected tab.
      // Other tabs will have webviews re-created when they are selected
      self.tabManager.reloadSelectedTab()
      // Unlock the folders to allow clearing of data.
      await _toggleFolderAccessForBlockCookies(locked: false)
    }

    await _clear(clearables)
    if clearAffectsTabs {
      self.tabManager.allTabs.forEach({ $0.reload() })
    }

    if historyCleared {
      self.tabManager.clearTabHistory()

      // Clearing Tab History should clear Recently Closed
      RecentlyClosed.removeAll()
    }

    await _toggleFolderAccessForBlockCookies(locked: true)

    return historyCleared
  }

  private func registerSubscriptions() {
    FilterListStorage.shared.$filterLists
      .receive(on: DispatchQueue.main)
      .sink { filterLists in
        for filterList in filterLists {
          switch filterList.entry.componentId {
          case AdblockFilterListCatalogEntry.mobileAnnoyancesComponentID:
            if filterList.isEnabled != self.blockMobileAnnoyances {
              self.blockMobileAnnoyances = filterList.isEnabled
            }
          default:
            continue
          }
        }
      }
      .store(in: &subscriptions)
  }
}
