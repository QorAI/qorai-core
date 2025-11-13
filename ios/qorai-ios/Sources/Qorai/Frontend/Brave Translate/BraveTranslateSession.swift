// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation
import SwiftUI
import Translation
import os.log

// If FeatureList.kQoraiAppleTranslateEnabled is true, Apple Translate will be used
// If FeatureList.kQoraiAppleTranslateEnabled is false, Qorai Translate will be used
// Apple Translate is causing a lot of issues so it's disabled for now

class QoraiTranslateSession {
  struct RequestMessage: Codable {
    let method: String
    let url: URL
    let headers: [String: String]
    let body: String
  }

  static func isPhraseTranslationRequest(
    _ request: RequestMessage
  ) -> Bool {
    return request.url.path.starts(with: "/translate_a/")
  }

  class func isTranslationSupported(
    from source: Locale.Language,
    to target: Locale.Language
  ) async -> Bool {
    if #available(iOS 18.0, *), FeatureList.kQoraiAppleTranslateEnabled.enabled {
      #if !targetEnvironment(simulator)
      let availability = LanguageAvailability()
      let status = await availability.status(from: source, to: target)
      switch status {
      case .installed, .supported:
        return true
      case .unsupported:
        return false
      @unknown default:
        return false
      }
      #endif
    }

    let sourceLanguage = source.qoraiTranslateLanguageIdentifier
    let targetLanguage = target.qoraiTranslateLanguageIdentifier
    return sourceLanguage != targetLanguage
  }

  func translate(
    _ request: RequestMessage
  ) async throws -> (data: Data, response: URLResponse) {
    var urlRequest = URLRequest(url: request.url)
    urlRequest.httpMethod = request.method
    urlRequest.httpBody = request.body.data(using: .utf8)
    request.headers.forEach { (key, value) in
      urlRequest.setValue(value, forHTTPHeaderField: key)
    }

    let session = URLSession(configuration: .ephemeral)
    defer { session.finishTasksAndInvalidate() }
    return try await session.data(for: urlRequest)
  }
}

struct QoraiTranslateContainerView: View {

  var onTranslationSessionUpdated: ((QoraiTranslateSession?) async -> Void)?

  @ObservedObject
  var languageInfo: QoraiTranslateLanguageInfo

  var body: some View {
    Color.clear
      .osAvailabilityModifiers({ view in
        if #available(iOS 18.0, *), FeatureList.kQoraiAppleTranslateEnabled.enabled {
          #if !targetEnvironment(simulator)
          view
            .translationTask(
              .init(source: languageInfo.pageLanguage, target: languageInfo.currentLanguage),
              action: { session in
                do {
                  try await session.prepareTranslation()
                  await onTranslationSessionUpdated?(QoraiTranslateSessionApple(session: session))
                } catch {
                  Logger.module.error("Translate Session Unavailable: \(error)")
                  await onTranslationSessionUpdated?(QoraiTranslateSessionApple(session: session))
                }
              }
            )
          #else
          view.task {
            await onTranslationSessionUpdated?(QoraiTranslateSession())
          }
          #endif
        } else {
          view.task {
            await onTranslationSessionUpdated?(QoraiTranslateSession())
          }
        }
      })
  }
}

#if !targetEnvironment(simulator)
@available(iOS 18.0, *)
private class QoraiTranslateSessionApple: QoraiTranslateSession {
  private weak var session: TranslationSession?

  init(session: TranslationSession) {
    self.session = session
  }

  override func translate(
    _ request: RequestMessage
  ) async throws -> (data: Data, response: URLResponse) {
    // Do not attempt to translate requests to html and css from Qorai-Translate script
    guard Self.isPhraseTranslationRequest(request) else {
      return try await super.translate(request)
    }

    guard let session = session else {
      throw QoraiTranslateError.otherError
    }

    let components = URLComponents(string: "https://translate.qorai.com?\(request.body)")
    let phrases = components!.queryItems!.map({ "\($0.value ?? "")" })
    let results = try await session.translations(
      from: phrases.map({ .init(sourceText: $0) })
    ).map({ $0.targetText })

    let data = try JSONSerialization.data(withJSONObject: results, options: [])
    let response =
      HTTPURLResponse(
        url: request.url,
        statusCode: 200,
        httpVersion: "HTTP/1.1",
        headerFields: ["Content-Type": "text/html"]
      )
      ?? URLResponse(
        url: request.url,
        mimeType: "text/html",
        expectedContentLength: data.count,
        textEncodingName: "UTF-8"
      )
    return (data, response)
  }
}
#endif
