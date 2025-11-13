// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore

extension QoraiWebView {
  /// Get a `QoraiWebView` from a given `TabState`
  ///
  /// This should only be used to create helper types that can access Chromium-specific features
  /// that are currently tied to `QoraiWebView`/`CWVWebView` such as autofill and Qorai WebUI.
  ///
  /// - Returns: This method will return `nil` if the tab passed in is not a Chromium-powered tab or
  /// if the web view hasn't been created yet.
  ///
  /// - Warning: This can only power lazy helpers, because a Chromium Tab may not have a web view
  /// created when the tab helper is attached to the `TabState`
  @_spi(ChromiumWebViewAccess) public static func from(tab: some TabState) -> QoraiWebView? {
    guard let tab = tab as? ChromiumTabState else { return nil }
    return tab.webView
  }
}

extension TabState {
  /// Whether or not the tab is powered by Chromium web views
  ///
  /// This should only be used to create helper types that can access Chromium-specific features
  /// that are currently tied to `QoraiWebView`/`CWVWebView` such as autofill and Qorai WebUI.
  @_spi(ChromiumWebViewAccess) public var isChromiumTab: Bool {
    return self is ChromiumTabState
  }
}
