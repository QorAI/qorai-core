// Copyright 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Preferences
import TestHelpers
import Web
import XCTest

@testable import QoraiShields
@testable import Data

@MainActor
class QoraiShieldsTabHelperTests: CoreDataTestCase {

  let url = URL(string: "https://qorai.com")!

  override func setUp() {
    super.setUp()
    Preferences.Shields.blockScripts.reset()
    Preferences.Shields.fingerprintingProtection.reset()
    Preferences.Shields.blockAdsAndTrackingLevelRaw.reset()
    Preferences.Shields.shredLevelRaw.reset()
  }

  /// Test `isQoraiShieldsEnabled(for:)` with
  /// `isQoraiShieldsContentSettingsEnabled` flag disabled.
  func testIsQoraiShieldsEnabled() {
    let testQoraiShieldsSettings = TestQoraiShieldsSettings()
    testQoraiShieldsSettings._isQoraiShieldsEnabled = { _ in
      XCTFail("QoraiShieldsSettings should not be called when feature flag is disabled")
      return false
    }
    testQoraiShieldsSettings._setQoraiShieldsEnabled = { _, _ in
      XCTFail("QoraiShieldsSettings should not be called when feature flag is disabled")
    }
    let domain = Domain.getOrCreate(forUrl: url, persistent: true)
    let tabState = TabStateFactory.create(with: .init(qoraiCore: nil))
    // Test with `isQoraiShieldsContentSettingsEnabled` disabled
    let qoraiShieldsTabHelper = QoraiShieldsTabHelper(
      tab: tabState,
      qoraiShieldsSettings: testQoraiShieldsSettings,
      isQoraiShieldsContentSettingsEnabled: false
    )

    // Verify initial values
    XCTAssertTrue(qoraiShieldsTabHelper.isQoraiShieldsEnabled(for: url))
    XCTAssertTrue(!domain.areAllShieldsOff)
    // Update value
    backgroundSaveAndWaitForExpectation {
      qoraiShieldsTabHelper.setQoraiShieldsEnabled(false, for: url)
    }
    // Verify updated values
    XCTAssertFalse(qoraiShieldsTabHelper.isQoraiShieldsEnabled(for: url))
    XCTAssertFalse(!domain.areAllShieldsOff)
  }

  /// Test `isQoraiShieldsEnabled(for:)` with
  /// `isQoraiShieldsContentSettingsEnabled` flag enabled.
  func testIsQoraiShieldsEnabledContentSettings() {
    var isQoraiShieldsEnabled = true

    let testQoraiShieldsSettings = TestQoraiShieldsSettings()
    testQoraiShieldsSettings._isQoraiShieldsEnabled = { url in
      XCTAssertEqual(url, self.url)
      return isQoraiShieldsEnabled
    }
    testQoraiShieldsSettings._setQoraiShieldsEnabled = { enabled, url in
      XCTAssertEqual(url, self.url)
      XCTAssertFalse(enabled)
      isQoraiShieldsEnabled = enabled
    }

    let tabState = TabStateFactory.create(with: .init(qoraiCore: nil))
    // Test with `isQoraiShieldsContentSettingsEnabled` enabled
    let qoraiShieldsTabHelper = QoraiShieldsTabHelper(
      tab: tabState,
      qoraiShieldsSettings: testQoraiShieldsSettings,
      isQoraiShieldsContentSettingsEnabled: true
    )

    // Verify initial value
    XCTAssertTrue(qoraiShieldsTabHelper.isQoraiShieldsEnabled(for: url))
    // Update value
    qoraiShieldsTabHelper.setQoraiShieldsEnabled(false, for: url)
    // Verify updated value
    XCTAssertFalse(isQoraiShieldsEnabled)
    XCTAssertFalse(qoraiShieldsTabHelper.isQoraiShieldsEnabled(for: url))
  }

  /// Test `shieldLevel(for:considerAllShieldsOption:)` with
  /// `isQoraiShieldsContentSettingsEnabled` flag disabled.
  func testShieldLevel() {
    let testQoraiShieldsSettings = TestQoraiShieldsSettings()
    testQoraiShieldsSettings._adBlockMode = { _ in
      XCTFail("QoraiShieldsSettings should not be called when feature flag is disabled")
      return .standard
    }
    testQoraiShieldsSettings._setAdBlockMode = { _, _ in
      XCTFail("QoraiShieldsSettings should not be called when feature flag is disabled")
    }
    let domain = Domain.getOrCreate(forUrl: url, persistent: true)
    let tabState = TabStateFactory.create(with: .init(qoraiCore: nil))
    // Test with `isQoraiShieldsContentSettingsEnabled` disabled
    let qoraiShieldsTabHelper = QoraiShieldsTabHelper(
      tab: tabState,
      qoraiShieldsSettings: testQoraiShieldsSettings,
      isQoraiShieldsContentSettingsEnabled: false
    )

    // Verify initial values
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(for: url, considerAllShieldsOption: false),
      .standard
    )
    XCTAssertNil(domain.shield_blockAdsAndTrackingLevel)
    // Update value
    backgroundSaveAndWaitForExpectation {
      qoraiShieldsTabHelper.setShieldLevel(.aggressive, for: url)
    }
    // Verify updated values
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(for: url, considerAllShieldsOption: false),
      .aggressive
    )
    XCTAssertEqual(domain.shield_blockAdsAndTrackingLevel, ShieldLevel.aggressive.rawValue)
    // Verify `considerAllShieldsOption`
    qoraiShieldsTabHelper.setQoraiShieldsEnabled(false, for: url)
    XCTAssertFalse(qoraiShieldsTabHelper.isQoraiShieldsEnabled(for: url))
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(for: url, considerAllShieldsOption: true),
      .disabled
    )

    // Verify `considerAlwaysAggressiveETLDs` is respected
    let alwaysAggressiveURL = URL(string: "https://m.youtube.com")!
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(
        for: alwaysAggressiveURL,
        considerAllShieldsOption: true,
        considerAlwaysAggressiveETLDs: false
      ),
      .standard
    )
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(
        for: alwaysAggressiveURL,
        considerAllShieldsOption: true,
        considerAlwaysAggressiveETLDs: true
      ),
      .aggressive
    )
    qoraiShieldsTabHelper.setShieldLevel(.disabled, for: alwaysAggressiveURL)
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(
        for: alwaysAggressiveURL,
        considerAllShieldsOption: true,
        considerAlwaysAggressiveETLDs: true
      ),
      .disabled
    )
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(
        for: alwaysAggressiveURL,
        considerAllShieldsOption: true,
        considerAlwaysAggressiveETLDs: false
      ),
      .disabled
    )
  }

  /// Test `shieldLevel(for:considerAllShieldsOption:)` with
  /// `isQoraiShieldsContentSettingsEnabled` flag enabled.
  func testShieldLevelContentSettings() {
    var adBlockMode: QoraiShields.AdBlockMode = .standard
    var isQoraiShieldsEnabled = true

    let testQoraiShieldsSettings = TestQoraiShieldsSettings()
    testQoraiShieldsSettings._adBlockMode = { url in
      return adBlockMode
    }
    testQoraiShieldsSettings._setAdBlockMode = { mode, url in
      XCTAssertEqual(mode, .aggressive)
      adBlockMode = mode
    }
    testQoraiShieldsSettings._isQoraiShieldsEnabled = { _ in
      return isQoraiShieldsEnabled
    }

    let tabState = TabStateFactory.create(with: .init(qoraiCore: nil))
    // Test with `isQoraiShieldsContentSettingsEnabled` enabled
    let qoraiShieldsTabHelper = QoraiShieldsTabHelper(
      tab: tabState,
      qoraiShieldsSettings: testQoraiShieldsSettings,
      isQoraiShieldsContentSettingsEnabled: true
    )

    // Verify initial value
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(for: url, considerAllShieldsOption: false),
      .standard
    )
    // Update value
    qoraiShieldsTabHelper.setShieldLevel(.aggressive, for: url)
    // Verify updated values
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(for: url, considerAllShieldsOption: false),
      .aggressive
    )
    // Verify `considerAllShieldsOption`
    isQoraiShieldsEnabled = false
    XCTAssertFalse(qoraiShieldsTabHelper.isQoraiShieldsEnabled(for: url))
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(for: url, considerAllShieldsOption: true),
      .disabled
    )

    // Verify `considerAlwaysAggressiveETLDs` is respected
    let alwaysAggressiveURL = URL(string: "https://m.youtube.com")!
    // reset TestQoraiShieldsSettings values
    isQoraiShieldsEnabled = true
    adBlockMode = .standard
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(
        for: alwaysAggressiveURL,
        considerAllShieldsOption: true,
        considerAlwaysAggressiveETLDs: false
      ),
      .standard
    )
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(
        for: alwaysAggressiveURL,
        considerAllShieldsOption: true,
        considerAlwaysAggressiveETLDs: true
      ),
      .aggressive
    )
    adBlockMode = .allow  // equivalent to ShieldLevel.disabled
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(
        for: alwaysAggressiveURL,
        considerAllShieldsOption: true,
        considerAlwaysAggressiveETLDs: true
      ),
      .disabled
    )
    XCTAssertEqual(
      qoraiShieldsTabHelper.shieldLevel(
        for: alwaysAggressiveURL,
        considerAllShieldsOption: true,
        considerAlwaysAggressiveETLDs: false
      ),
      .disabled
    )
  }

  /// Test `isShieldExpected(for:shield:considerAllShieldsOption:)` for Block
  /// Scripts with `isQoraiShieldsContentSettingsEnabled` flag disabled.
  func testBlockScriptsEnabled() {
    let testQoraiShieldsSettings = TestQoraiShieldsSettings()
    testQoraiShieldsSettings._isBlockScriptsEnabled = { _ in
      XCTFail("QoraiShieldsSettings should not be called when feature flag is disabled")
      return false
    }
    testQoraiShieldsSettings._setBlockScriptsEnabled = { _, _ in
      XCTFail("QoraiShieldsSettings should not be called when feature flag is disabled")
    }
    let domain = Domain.getOrCreate(forUrl: url, persistent: true)
    let tabState = TabStateFactory.create(with: .init(qoraiCore: nil))
    // Test with `isQoraiShieldsContentSettingsEnabled` disabled
    let qoraiShieldsTabHelper = QoraiShieldsTabHelper(
      tab: tabState,
      qoraiShieldsSettings: testQoraiShieldsSettings,
      isQoraiShieldsContentSettingsEnabled: false
    )

    // Verify initial values
    XCTAssertEqual(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .noScript,
        considerAllShieldsOption: false
      ),
      false
    )
    XCTAssertNil(domain.shield_noScript)
    // Update value
    backgroundSaveAndWaitForExpectation {
      qoraiShieldsTabHelper.setBlockScriptsEnabled(true, for: url)
    }
    // Verify updated values
    XCTAssertEqual(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .noScript,
        considerAllShieldsOption: false
      ),
      true
    )
    XCTAssertEqual(domain.shield_noScript, NSNumber(booleanLiteral: true))
    // Verify `considerAllShieldsOption`
    qoraiShieldsTabHelper.setQoraiShieldsEnabled(false, for: url)
    XCTAssertFalse(qoraiShieldsTabHelper.isQoraiShieldsEnabled(for: url))
    XCTAssertEqual(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .noScript,
        considerAllShieldsOption: true
      ),
      false
    )
  }

  /// Test `isShieldExpected(for:shield:considerAllShieldsOption:)` for Block
  /// Scripts with `isQoraiShieldsContentSettingsEnabled` flag enabled.
  func testBlockScriptsEnabledContentSettings() {
    var isBlockScriptsEnabled = false

    let testQoraiShieldsSettings = TestQoraiShieldsSettings()
    testQoraiShieldsSettings._isBlockScriptsEnabled = { url in
      XCTAssertEqual(url, self.url)
      return isBlockScriptsEnabled
    }
    testQoraiShieldsSettings._setBlockScriptsEnabled = { enabled, url in
      XCTAssertEqual(url, self.url)
      XCTAssertTrue(enabled)
      isBlockScriptsEnabled = enabled
    }
    testQoraiShieldsSettings._isQoraiShieldsEnabled = { _ in
      // disabled so we can test `considerAllShieldsOption: true`
      return false
    }

    let tabState = TabStateFactory.create(with: .init(qoraiCore: nil))
    // Test with `isQoraiShieldsContentSettingsEnabled` enabled
    let qoraiShieldsTabHelper = QoraiShieldsTabHelper(
      tab: tabState,
      qoraiShieldsSettings: testQoraiShieldsSettings,
      isQoraiShieldsContentSettingsEnabled: true
    )

    // Verify initial values
    XCTAssertEqual(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .noScript,
        considerAllShieldsOption: false
      ),
      false
    )
    // Update value
    qoraiShieldsTabHelper.setBlockScriptsEnabled(true, for: url)
    // Verify updated values
    XCTAssertEqual(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .noScript,
        considerAllShieldsOption: false
      ),
      true
    )
    // Verify `considerAllShieldsOption`
    qoraiShieldsTabHelper.setQoraiShieldsEnabled(false, for: url)
    XCTAssertFalse(qoraiShieldsTabHelper.isQoraiShieldsEnabled(for: url))
    XCTAssertEqual(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .noScript,
        considerAllShieldsOption: true
      ),
      false
    )
  }

  /// Test `isShieldExpected(for:shield:considerAllShieldsOption:)` for Block
  /// Fingerprinting with `isQoraiShieldsContentSettingsEnabled` flag disabled.
  func testBlockFingerprintingEnabled() {
    let testQoraiShieldsSettings = TestQoraiShieldsSettings()
    testQoraiShieldsSettings._fingerprintMode = { _ in
      XCTFail("QoraiShieldsSettings should not be called when feature flag is disabled")
      return .standardMode
    }
    testQoraiShieldsSettings._setFingerprintMode = { _, _ in
      XCTFail("QoraiShieldsSettings should not be called when feature flag is disabled")
    }
    let domain = Domain.getOrCreate(forUrl: url, persistent: true)
    let tabState = TabStateFactory.create(with: .init(qoraiCore: nil))
    // Test with `isQoraiShieldsContentSettingsEnabled` disabled
    let qoraiShieldsTabHelper = QoraiShieldsTabHelper(
      tab: tabState,
      qoraiShieldsSettings: testQoraiShieldsSettings,
      isQoraiShieldsContentSettingsEnabled: false
    )

    // Verify initial values
    XCTAssertTrue(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .fpProtection,
        considerAllShieldsOption: false
      )
    )
    XCTAssertNil(domain.shield_fpProtection)
    // Update value
    backgroundSaveAndWaitForExpectation {
      qoraiShieldsTabHelper.setBlockFingerprintingEnabled(false, for: url)
    }
    // Verify updated values
    XCTAssertFalse(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .fpProtection,
        considerAllShieldsOption: false
      )
    )
    XCTAssertEqual(domain.shield_fpProtection, NSNumber(booleanLiteral: false))

    // Reset back to enabled so we can test `considerAllShieldsOption`
    backgroundSaveAndWaitForExpectation {
      qoraiShieldsTabHelper.setBlockFingerprintingEnabled(true, for: url)
    }
    XCTAssertTrue(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .fpProtection,
        considerAllShieldsOption: false
      )
    )
    // Verify `considerAllShieldsOption`
    qoraiShieldsTabHelper.setQoraiShieldsEnabled(false, for: url)
    XCTAssertFalse(qoraiShieldsTabHelper.isQoraiShieldsEnabled(for: url))
    XCTAssertFalse(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .fpProtection,
        considerAllShieldsOption: true
      )
    )
  }

  /// Test `isShieldExpected(for:shield:considerAllShieldsOption:)` for Block
  /// Fingerprinting with `isQoraiShieldsContentSettingsEnabled` flag enabled.
  func testBlockFingerprintingEnabledContentSettings() {
    var fingerPrintMode: QoraiShields.FingerprintMode = .standardMode

    let testQoraiShieldsSettings = TestQoraiShieldsSettings()
    testQoraiShieldsSettings._fingerprintMode = { url in
      XCTAssertEqual(url, self.url)
      return fingerPrintMode
    }
    testQoraiShieldsSettings._setFingerprintMode = { mode, url in
      XCTAssertEqual(url, self.url)
      XCTAssertEqual(mode, .allowMode)
      fingerPrintMode = mode
    }
    testQoraiShieldsSettings._isQoraiShieldsEnabled = { _ in
      // disabled so we can test `considerAllShieldsOption: true`
      return false
    }

    let tabState = TabStateFactory.create(with: .init(qoraiCore: nil))
    // Test with `isQoraiShieldsContentSettingsEnabled` enabled
    let qoraiShieldsTabHelper = QoraiShieldsTabHelper(
      tab: tabState,
      qoraiShieldsSettings: testQoraiShieldsSettings,
      isQoraiShieldsContentSettingsEnabled: true
    )

    // Verify initial values
    XCTAssertTrue(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .fpProtection,
        considerAllShieldsOption: false
      )
    )
    // Update value
    qoraiShieldsTabHelper.setBlockFingerprintingEnabled(false, for: url)
    // Verify updated values
    XCTAssertFalse(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .fpProtection,
        considerAllShieldsOption: false
      )
    )
    // Verify `considerAllShieldsOption`
    qoraiShieldsTabHelper.setQoraiShieldsEnabled(false, for: url)
    XCTAssertFalse(qoraiShieldsTabHelper.isQoraiShieldsEnabled(for: url))
    XCTAssertFalse(
      qoraiShieldsTabHelper.isShieldExpected(
        for: url,
        shield: .fpProtection,
        considerAllShieldsOption: true
      )
    )
  }

  /// Test `shredLevel(for:)` with `isQoraiShieldsContentSettingsEnabled` flag disabled.
  func testShredLevel() {
    let testQoraiShieldsSettings = TestQoraiShieldsSettings()
    testQoraiShieldsSettings._fingerprintMode = { _ in
      XCTFail("QoraiShieldsSettings should not be called when feature flag is disabled")
      return .standardMode
    }
    testQoraiShieldsSettings._setFingerprintMode = { _, _ in
      XCTFail("QoraiShieldsSettings should not be called when feature flag is disabled")
    }
    let domain = Domain.getOrCreate(forUrl: url, persistent: true)
    let tabState = TabStateFactory.create(with: .init(qoraiCore: nil))
    // Test with `isQoraiShieldsContentSettingsEnabled` disabled
    let qoraiShieldsTabHelper = QoraiShieldsTabHelper(
      tab: tabState,
      qoraiShieldsSettings: testQoraiShieldsSettings,
      isQoraiShieldsContentSettingsEnabled: false
    )

    // Verify initial values
    XCTAssertEqual(qoraiShieldsTabHelper.shredLevel(for: url), .never)
    XCTAssertNil(domain.shield_shredLevel)
    // Update value
    backgroundSaveAndWaitForExpectation {
      qoraiShieldsTabHelper.setShredLevel(.appExit, for: url)
    }
    // Verify updated values
    XCTAssertEqual(qoraiShieldsTabHelper.shredLevel(for: url), .appExit)
    XCTAssertEqual(domain.shield_shredLevel, SiteShredLevel.appExit.rawValue)
  }

  // TODO: Test AutoShred via content settings qorai-browser#47753
}
