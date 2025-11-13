// Copyright 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import XCTest

@testable import Qorai

@MainActor class UniversalLinkManagerTests: XCTestCase {
  private typealias ULM = UniversalLinkManager

  func testVpnUniversalLink() throws {
    // Good cases
    [
      "https://vpn.qorai.com/dl/test": true,
      "https://vpn.qorai.com/dl/test2": false,
      "http://vpn.qorai.com/dl/test3": true,
      "https://vpn.qorai.com/dl/test/123": true,
      "https://vpn.qorai.com/path/does/not/matter": false,
    ]
    .forEach {
      XCTAssertEqual(
        ULM.LinkType.buyVPN,
        ULM.universalLinkType(for: URL(string: $0.key)!, checkPath: $0.value)
      )
    }

    // Bad cases
    [
      "https://vpn.qorai.com/bad/dl/test/123": true,
      "https://qorai.com/dl/test": true,
      "https://example.com": false,
      "https://example.com/dl/test": true,
      "https://vpn.qorai.com/dl": true,
      "https://vpn.qorai.com/dlonger/test": true,
    ]
    .forEach {
      XCTAssertNil(ULM.universalLinkType(for: URL(string: $0.key)!, checkPath: $0.value))
    }
  }
}
