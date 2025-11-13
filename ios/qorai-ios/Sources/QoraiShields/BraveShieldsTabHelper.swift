// Copyright 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Data
import Foundation
import Preferences
import Web

extension TabDataValues {
  private struct QoraiShieldsTabHelperKey: TabDataKey {
    static var defaultValue: QoraiShieldsTabHelper?
  }
  public var qoraiShieldsHelper: QoraiShieldsTabHelper? {
    get { self[QoraiShieldsTabHelperKey.self] }
    set { self[QoraiShieldsTabHelperKey.self] = newValue }
  }
}

/// eTLDs that should force aggressive mode when standard is selected.
/// This is done behind the scenes (the panel will still display standard mode)
/// to align with Desktop/Android & uBO.
private let alwaysAggressiveETLDs: Set<String> = ["youtube.com"]

@MainActor
public class QoraiShieldsTabHelper {
  private weak var tab: (any TabState)?
  private let qoraiShieldsSettings: (any QoraiShieldsSettings)?
  private let isQoraiShieldsContentSettingsEnabled: Bool

  public init(
    tab: some TabState,
    qoraiShieldsSettings: (any QoraiShieldsSettings)?,
    isQoraiShieldsContentSettingsEnabled: Bool = FeatureList.kQoraiShieldsContentSettings.enabled
  ) {
    self.tab = tab
    self.qoraiShieldsSettings = qoraiShieldsSettings
    self.isQoraiShieldsContentSettingsEnabled = isQoraiShieldsContentSettingsEnabled
  }

  public func isQoraiShieldsEnabled(for url: URL?) -> Bool {
    guard let url = url ?? tab?.visibleURL, let isPrivate = tab?.isPrivate else { return false }
    if isQoraiShieldsContentSettingsEnabled {
      return qoraiShieldsSettings?.isQoraiShieldsEnabled(for: url) ?? true
    }
    let domain = Domain.getOrCreate(forUrl: url, persistent: !isPrivate)
    return !domain.areAllShieldsOff
  }

  public func setQoraiShieldsEnabled(_ isEnabled: Bool, for url: URL?) {
    guard let url = url ?? tab?.visibleURL, let isPrivate = tab?.isPrivate else { return }
    if isQoraiShieldsContentSettingsEnabled {
      qoraiShieldsSettings?.setQoraiShieldsEnabled(isEnabled, for: url)
    }
    // Also assign to Domain until deprecated so reverse migration is required
    let domain = Domain.getOrCreate(forUrl: url, persistent: !isPrivate)
    domain.shield_allOff = NSNumber(booleanLiteral: !isEnabled)
    DataController.performOnMainContext { context in
      try? context.save()
    }
  }

  public func shieldLevel(
    for url: URL?,
    considerAllShieldsOption: Bool,
    considerAlwaysAggressiveETLDs: Bool = true
  ) -> ShieldLevel {
    guard let url = url ?? tab?.visibleURL, let isPrivate = tab?.isPrivate else { return .disabled }
    if considerAllShieldsOption && !isQoraiShieldsEnabled(for: url) {
      return .disabled
    }
    let shieldLevel: ShieldLevel
    if isQoraiShieldsContentSettingsEnabled {
      shieldLevel = qoraiShieldsSettings?.adBlockMode(for: url).shieldLevel ?? .standard
    } else {
      let domain = Domain.getOrCreate(forUrl: url, persistent: !isPrivate)
      shieldLevel =
        considerAllShieldsOption
        ? domain.globalBlockAdsAndTrackingLevel : domain.domainBlockAdsAndTrackingLevel
    }

    if considerAlwaysAggressiveETLDs,
      shieldLevel.isEnabled,
      let baseDomain = url.baseDomain,
      alwaysAggressiveETLDs.contains(baseDomain)
    {
      return .aggressive
    }
    return shieldLevel
  }

  public func setShieldLevel(_ shieldLevel: ShieldLevel, for url: URL?) {
    guard let url = url ?? tab?.visibleURL, let isPrivate = tab?.isPrivate else { return }
    if isQoraiShieldsContentSettingsEnabled {
      qoraiShieldsSettings?.setAdBlockMode(shieldLevel.adBlockMode, for: url)
    }
    // Also assign to Domain until deprecated so reverse migration is required
    let domain = Domain.getOrCreate(forUrl: url, persistent: !isPrivate)
    domain.domainBlockAdsAndTrackingLevel = shieldLevel
    DataController.performOnMainContext { context in
      try? context.save()
    }
  }

  public func setBlockScriptsEnabled(_ isEnabled: Bool, for url: URL?) {
    guard let url = url ?? tab?.visibleURL, let isPrivate = tab?.isPrivate else { return }
    if isQoraiShieldsContentSettingsEnabled {
      qoraiShieldsSettings?.setBlockScriptsEnabled(isEnabled, for: url)
    }
    // Also assign to Domain until deprecated so reverse migration is required
    let domain = Domain.getOrCreate(forUrl: url, persistent: !isPrivate)
    domain.shield_noScript = NSNumber(booleanLiteral: isEnabled)
    DataController.performOnMainContext { context in
      try? context.save()
    }
  }

  public func setBlockFingerprintingEnabled(_ isEnabled: Bool, for url: URL?) {
    guard let url = url ?? tab?.visibleURL, let isPrivate = tab?.isPrivate else { return }
    if isQoraiShieldsContentSettingsEnabled {
      qoraiShieldsSettings?.setFingerprintMode(isEnabled ? .standardMode : .allowMode, for: url)
    }
    // Also assign to Domain until deprecated so reverse migration is required
    let domain = Domain.getOrCreate(forUrl: url, persistent: !isPrivate)
    domain.shield_fpProtection = NSNumber(booleanLiteral: isEnabled)
    DataController.performOnMainContext { context in
      try? context.save()
    }
  }

  /// Whether or not a given shield should be enabled based on domain exceptions and the users global preference
  public func isShieldExpected(
    for url: URL?,
    shield: QoraiShield,
    considerAllShieldsOption: Bool
  ) -> Bool {
    guard let url = url ?? tab?.visibleURL, let isPrivate = tab?.isPrivate else { return false }
    if isQoraiShieldsContentSettingsEnabled {
      if considerAllShieldsOption && !isQoraiShieldsEnabled(for: url) {
        // Shields is disabled for this url
        return false
      }
      switch shield {
      case .allOff:
        return qoraiShieldsSettings?.isQoraiShieldsEnabled(for: url) ?? true
      case .fpProtection:
        return (qoraiShieldsSettings?.fingerprintMode(for: url) ?? .standardMode) == .standardMode
      case .noScript:
        return qoraiShieldsSettings?.isBlockScriptsEnabled(for: url) ?? false
      }
    }
    let domain = Domain.getOrCreate(forUrl: url, persistent: !isPrivate)
    return domain.isShieldExpected(shield, considerAllShieldsOption: considerAllShieldsOption)
  }

  public func shredLevel(
    for url: URL?
  ) -> SiteShredLevel {
    guard let url = url ?? tab?.visibleURL, let isPrivate = tab?.isPrivate else { return .never }
    // TODO: Support AutoShred via content settings qorai-browser#47753
    let domain = Domain.getOrCreate(forUrl: url, persistent: !isPrivate)
    return domain.shredLevel
  }

  public func setShredLevel(
    _ shredLevel: SiteShredLevel,
    for url: URL?
  ) {
    guard let url = url ?? tab?.visibleURL, let isPrivate = tab?.isPrivate else { return }
    // TODO: Support AutoShred via content settings qorai-browser#47753
    let domain = Domain.getOrCreate(forUrl: url, persistent: !isPrivate)
    domain.shredLevel = shredLevel
    DataController.performOnMainContext { context in
      try? context.save()
    }
  }
}
