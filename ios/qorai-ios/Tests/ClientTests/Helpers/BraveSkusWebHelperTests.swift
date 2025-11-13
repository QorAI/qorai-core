// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import TestHelpers
import XCTest

@testable import Qorai

final class QoraiSkusWebHelperTests: XCTestCase {

  func testShouldInjectReceipt() throws {

    let goodURLs: [URL?] =
      [
        .init(string: "https://account.qorai.com/?intent=connect-receipt&product=vpn"),
        .init(string: "https://account.qorai.software/?intent=connect-receipt&product=vpn"),
        .init(string: "https://account.qoraisoftware.com?intent=connect-receipt&product=vpn"),
        // One extra query param
        .init(
          string:
            "https://account.qoraisoftware.com?intent=connect-receipt&product=vpn&extra_param=test"
        ),
        // Url path agnostic test
        .init(string: "https://account.qorai.com/extrapath?intent=connect-receipt&product=vpn"),
      ]
    let badURLs: [URL?] =
      [  // Wrong host, correct query params
        .init(string: "https://example.com/?intent=connect-receipt&product=vpn"),
        // Correct host, no query params
        .init(string: "https://account.qorai.com/"),
        // Correct host, single query param,
        .init(string: "https://account.qorai.com/?intent=connect-receipt"),
        .init(string: "https://account.qorai.com/?product=vpn"),
        // Correct host, incorrect query param values
        .init(string: "https://account.qorai.com/?intent=bad&product=not_vpn"),
        // Http connection
        .init(string: "http://account.qorai.com/?intent=connect-receipt&product=vpn"),
      ]

    try goodURLs.forEach {
      XCTAssertNotNil(
        QoraiSkusWebHelperMock(for: try XCTUnwrap($0)),
        "failed at: \($0?.absoluteString ?? "nil")"
      )
    }

    try badURLs.forEach {
      XCTAssertNil(
        QoraiSkusWebHelperMock(for: try XCTUnwrap($0)),
        "failed at: \($0?.absoluteString ?? "nil")"
      )
    }
  }

  func testReceiptJson() async throws {
    let url = try XCTUnwrap(
      URL(string: "https://account.qorai.com/?intent=connect-receipt&product=vpn")
    )

    let helper = try XCTUnwrap(QoraiSkusWebHelperMock(for: url))
    let receiptData = try await XCTUnwrapAsync(await helper.fetchReceiptData())
    XCTAssertEqual(receiptData.key, "qoraiVpn.receipt")
    let value = receiptData.value
    let decodedData = try XCTUnwrap(Data(base64Encoded: value))

    let json = try XCTUnwrap(JSONSerialization.jsonObject(with: decodedData) as? [String: String])
    let type = try XCTUnwrap(json["type"])
    let rawReceipt = try XCTUnwrap(json["raw_receipt"])
    let package = try XCTUnwrap(json["package"])
    let subscriptionId = try XCTUnwrap(json["subscription_id"])

    XCTAssertEqual(type, "ios")
    XCTAssertEqual(rawReceipt, QoraiSkusWebHelperMock.mockReceiptValue)
    XCTAssertEqual(package, try XCTUnwrap(Bundle.main.bundleIdentifier))
    XCTAssertEqual(subscriptionId, "qorai-firewall-vpn-premium")
  }

  func testMilisecondsOptionalDateFormatter() throws {
    XCTAssertNotNil(QoraiSkusWebHelper.milisecondsOptionalDate(from: "2022-08-01T00:21:21"))
    XCTAssertNotNil(QoraiSkusWebHelper.milisecondsOptionalDate(from: "2022-08-01T00:21:21.123456"))
    XCTAssertNotNil(QoraiSkusWebHelper.milisecondsOptionalDate(from: "2022-08-01T00:21:21.9"))
  }

  func testFetchVPNCredential() throws {
    let sampleCookieExpirationDate = "06 Aug 2022 00:00:00 GMT"

    // Sample token we receive from the server
    let sampleCookie =
      """
      __Secure-sku#qorai-firewall-vpn-premium=eyJ0eXBlIjoidGltZS1saW1pdGVkIiwidmVyc2lvbiI6MSwic2t1IjoiYnJhdmUtZmlyZXdhbGwtdnBuLXByZW1pdW0iLCJwcmVzZW50YXRpb24iOiJleUpsZUhCcGNtVnpRWFFpT2lJeU1ESXlMVEE0TFRBMklpd2lhWE56ZFdWa1FYUWlPaUl5TURJeUxUQTRMVEExSWl3aWRHOXJaVzRpT2lKV1ZUY3hNV1V5VTJoVkwzaEJNRFYzTnk5eVQyNTZVa3hvWkdsc1lqUkdSV2xvYUZkM1YzWmhkRGhIT0ZCSlIxbFpXVE42WkRZNFoxVjJiVUZrTHpKV0luMD0ifQ==;path=*;samesite=strict;expires=Sat, \(sampleCookieExpirationDate);secure
      """

    let manuallyExtractedCredential =
      """
      eyJ0eXBlIjoidGltZS1saW1pdGVkIiwidmVyc2lvbiI6MSwic2t1IjoiYnJhdmUtZmlyZXdhbGwtdnBuLXByZW1pdW0iLCJwcmVzZW50YXRpb24iOiJleUpsZUhCcGNtVnpRWFFpT2lJeU1ESXlMVEE0TFRBMklpd2lhWE56ZFdWa1FYUWlPaUl5TURJeUxUQTRMVEExSWl3aWRHOXJaVzRpT2lKV1ZUY3hNV1V5VTJoVkwzaEJNRFYzTnk5eVQyNTZVa3hvWkdsc1lqUkdSV2xvYUZkM1YzWmhkRGhIT0ZCSlIxbFpXVE42WkRZNFoxVjJiVUZrTHpKV0luMD0ifQ==
      """

    let developmentCred = QoraiSkusWebHelper.fetchVPNCredential(
      sampleCookie,
      domain: "account.qorai.software"
    )
    XCTAssertEqual(try XCTUnwrap(developmentCred?.guardianCredential), manuallyExtractedCredential)
    XCTAssertEqual("development", try XCTUnwrap(developmentCred?.environment))

    let stagingCred = QoraiSkusWebHelper.fetchVPNCredential(
      sampleCookie,
      domain: "account.qoraisoftware.com"
    )
    XCTAssertEqual(try XCTUnwrap(stagingCred?.guardianCredential), manuallyExtractedCredential)
    XCTAssertEqual("staging", try XCTUnwrap(stagingCred?.environment))

    let prodCred = QoraiSkusWebHelper.fetchVPNCredential(sampleCookie, domain: "account.qorai.com")
    XCTAssertEqual(try XCTUnwrap(prodCred?.guardianCredential), manuallyExtractedCredential)
    XCTAssertEqual("production", try XCTUnwrap(prodCred?.environment))

    let wrongDomainCred = QoraiSkusWebHelper.fetchVPNCredential(sampleCookie, domain: "example.com")
    XCTAssertNil(wrongDomainCred)

    let wrongCookie = QoraiSkusWebHelper.fetchVPNCredential(
      "wrong cookie",
      domain: "account.qorai.com"
    )
    XCTAssertNil(wrongCookie)

    let expirationDate = try XCTUnwrap(prodCred?.expirationDate)
    let dateFormatter = DateFormatter()
    dateFormatter.dateFormat = "dd MMM yyyy HH:mm:ss zzz"

    let dateFromTestCookie = try XCTUnwrap(dateFormatter.date(from: sampleCookieExpirationDate))

    XCTAssertEqual(expirationDate, dateFromTestCookie)
  }
}
