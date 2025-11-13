// Copyright 202t The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore

/// Implementation of `QoraiShieldsSettings` used for unit testing
class TestQoraiShieldsSettings: QoraiShieldsSettings {

  var _isQoraiShieldsEnabled: ((URL) -> Bool)?
  var _setQoraiShieldsEnabled: ((Bool, URL) -> Void)?

  var _defaultAdBlockMode: (() -> QoraiShields.AdBlockMode)?
  var _setDefaultAdBlockMode: ((QoraiShields.AdBlockMode) -> Void)?
  var _adBlockMode: ((URL) -> QoraiShields.AdBlockMode)?
  var _setAdBlockMode: ((QoraiShields.AdBlockMode, URL) -> Void)?

  var _isBlockScriptsEnabledByDefault: (() -> Bool)?
  var _setBlockScriptsEnabledByDefault: ((Bool) -> Void)?
  var _isBlockScriptsEnabled: ((URL) -> Bool)?
  var _setBlockScriptsEnabled: ((Bool, URL) -> Void)?

  var _defaultFingerprintMode: (() -> QoraiShields.FingerprintMode)?
  var _setDefaultFingerprintMode: ((QoraiShields.FingerprintMode) -> Void)?
  var _fingerprintMode: ((URL) -> QoraiShields.FingerprintMode)?
  var _setFingerprintMode: ((QoraiShields.FingerprintMode, URL) -> Void)?

  var _defaultAutoShredMode: (() -> QoraiShields.AutoShredMode)?
  var _setDefaultAutoShredMode: ((QoraiShields.AutoShredMode) -> Void)?
  var _autoShredMode: ((URL) -> QoraiShields.AutoShredMode)?
  var _setAutoShredMode: ((QoraiShields.AutoShredMode, URL) -> Void)?

  // MARK: Qorai ShieldsEnabled

  func isQoraiShieldsEnabled(for url: URL) -> Bool {
    return _isQoraiShieldsEnabled?(url) ?? true
  }
  func setQoraiShieldsEnabled(_ isEnabled: Bool, for url: URL!) {
    _setQoraiShieldsEnabled?(isEnabled, url)
  }

  // MARK: AdBlockMode

  var defaultAdBlockMode: QoraiShields.AdBlockMode {
    get {
      _defaultAdBlockMode?() ?? .standard
    }
    set {
      _setDefaultAdBlockMode?(newValue)
    }
  }
  func adBlockMode(for url: URL) -> QoraiShields.AdBlockMode {
    return _adBlockMode?(url) ?? defaultAdBlockMode
  }
  func setAdBlockMode(_ adBlockMode: QoraiShields.AdBlockMode, for url: URL!) {
    _setAdBlockMode?(adBlockMode, url)
  }

  // MARK: Block Scripts

  var isBlockScriptsEnabledByDefault: Bool {
    get {
      _isBlockScriptsEnabledByDefault?() ?? false
    }
    set {
      _setBlockScriptsEnabledByDefault?(newValue)
    }
  }
  func isBlockScriptsEnabled(for url: URL) -> Bool {
    return _isBlockScriptsEnabled?(url) ?? false
  }
  func setBlockScriptsEnabled(_ isEnabled: Bool, for url: URL!) {
    _setBlockScriptsEnabled?(isEnabled, url)
  }

  // MARK: FingerprintMode

  var defaultFingerprintMode: QoraiShields.FingerprintMode {
    get {
      _defaultFingerprintMode?() ?? .standardMode
    }
    set {
      _setDefaultFingerprintMode?(newValue)
    }
  }
  func fingerprintMode(for url: URL) -> QoraiShields.FingerprintMode {
    return _fingerprintMode?(url) ?? defaultFingerprintMode
  }
  func setFingerprintMode(_ fingerprintMode: QoraiShields.FingerprintMode, for url: URL!) {
    _setFingerprintMode?(fingerprintMode, url)
  }

  // MARK: AutoShredMode

  var defaultAutoShredMode: QoraiShields.AutoShredMode {
    get {
      _defaultAutoShredMode?() ?? .never
    }
    set {
      _setDefaultAutoShredMode?(newValue)
    }
  }
  func autoShredMode(for url: URL) -> QoraiShields.AutoShredMode {
    return _autoShredMode?(url) ?? defaultAutoShredMode
  }
  func setAutoShredMode(_ fingerprintMode: QoraiShields.AutoShredMode, for url: URL!) {
    _setAutoShredMode?(fingerprintMode, url)
  }
}
