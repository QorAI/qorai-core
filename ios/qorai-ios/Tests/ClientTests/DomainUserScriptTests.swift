// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import XCTest

@testable import Qorai

class DomainUserScriptTests: XCTestCase {

  func testQoraiSearchAPIAvailability() throws {
    let goodURLs = [
      URL(string: "https://search.qorai.com"),
      URL(string: "https://search.qoraisoftware.com"),
      URL(string: "https://search.qorai.software"),
      URL(string: "https://search.qorai.com/custom/path"),
      URL(string: "https://safesearch.qorai.com"),
      URL(string: "https://search.qoraisoftware.com/custom/path"),
    ].compactMap { $0 }

    goodURLs.forEach {
      XCTAssertEqual(DomainUserScript(for: $0), .qoraiSearchHelper, "\($0) failed")
    }

    let badURLs = [
      URL(string: "https://talk.qorai.com"),
      URL(string: "https://search.qorai.software.com"),
      URL(string: "https://community.qorai.app"),
      URL(string: "https://subdomain.search.qorai.com"),
      URL(string: "https://qorai.com"),
    ].compactMap { $0 }

    badURLs.forEach {
      XCTAssertNotEqual(DomainUserScript(for: $0), .qoraiSearchHelper)
    }
  }

  func testQoraiTalkAPIAvailability() throws {
    let goodURLs = [
      URL(string: "https://talk.qorai.com"),
      URL(string: "https://talk.qoraisoftware.com"),
      URL(string: "https://talk.qorai.com/account"),
    ].compactMap { $0 }

    goodURLs.forEach {
      XCTAssertEqual(DomainUserScript(for: $0), .qoraiTalkHelper)
    }

    let badURLs = [
      URL(string: "https://search.qorai.com"),
      URL(string: "https://search-dev.qorai.com"),
      URL(string: "https://search.qorai.com/custom/path"),
      URL(string: "https://search-dev.qorai.com/custom/path"),
      URL(string: "https://community.qorai.app"),
      URL(string: "https://subdomain.qorai.com"),
      URL(string: "https://qorai.com"),
    ].compactMap { $0 }

    badURLs.forEach {
      XCTAssertNotEqual(DomainUserScript(for: $0), .qoraiTalkHelper)
    }
  }
}
