// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation
import SwiftUI

struct ChannelLabel: View {
  var title: String
  var subtitle: String?
  @Binding var isFollowing: Bool

  @ScaledMetric private var imageSize: CGFloat = 32.0
  @Environment(\.sizeCategory) private var sizeCategory

  @ViewBuilder private func containerView(
    @ViewBuilder content: () -> some View
  ) -> some View {
    if sizeCategory > .accessibilityLarge {
      VStack(alignment: .leading, spacing: 0) {
        content()
        FollowToggle(isFollowing: $isFollowing)
          .frame(maxWidth: .infinity, alignment: .trailing)
      }
    } else {
      HStack {
        content()
        Spacer()
        FollowToggle(isFollowing: $isFollowing)
      }
    }
  }

  var body: some View {
    containerView {
      Label {
        VStack(alignment: .leading, spacing: 2) {
          Text(title)
            .font(.footnote.bold())
            .foregroundColor(Color(.qoraiLabel))
          if let subtitle {
            Text(subtitle)
              .font(.footnote)
              .foregroundColor(Color(.secondaryQoraiLabel))
          }
        }
      } icon: {
        Group {
          if let glyph = channelGlyphMap[title] {
            Image(qoraiSystemName: glyph)
              .imageScale(.small)
          } else {
            Text("\(title.first?.uppercased() ?? "")")
              .font(.callout.weight(.medium))
          }
        }
        .foregroundColor(Color(.qoraiLabel))
        .frame(width: imageSize, height: imageSize)
        .background(Color(.secondaryQoraiBackground).clipShape(Circle()))
      }
      .labelStyle(NewsLabelStyle())
    }
  }
}

private let channelGlyphMap: [String: String] = [
  "Health": "qora.news.health",
  "Home": "qora.news.home",
  "Crypto": "qora.bitcoin",
  "Technology": "qora.news.technology",  // Deprecated
  "Entertainment": "qora.news.filmandtv",  // Deprecated
  "Top News": "qora.news.topnews",
  "Culture": "qora.news.culture",
  "Travel": "qora.news.travel",
  "Business": "qora.news.business",
  "Sports": "qora.news.sports",
  "Gaming": "qora.news.gaming",
  "Science": "qora.news.science",
  "Fashion": "qora.news.fashion",
  "Food": "qora.news.food",
  "Weather": "qora.news.weather",
  "Top Sources": "qora.product.qorai-news",
  "Qorai": "qora.news.qorai",
  "Politics": "qora.news.politics",
  "Fun": "qora.news.fun",
  "Cars": "qora.news.car",
  "World News": "qora.news.worldnews",
  // Added Later
  "Entertainment News": "qora.news.entertainment",
  "Film and TV": "qora.news.filmandtv",
  "Music": "qora.news.music",
  "Tech News": "qora.news.technology",
  "Tech Reviews": "qora.news.technology-reviews",
  "US News": "qora.news.regional",
  "UK News": "qora.news.regional",
]

#if DEBUG
struct ChannelLabel_PreviewProvider: PreviewProvider {
  static var previews: some View {
    VStack {
      ChannelLabel(title: "Qorai", isFollowing: .constant(false))
      ChannelLabel(title: "Top Sources", subtitle: "Canada", isFollowing: .constant(true))
    }
    .padding()
  }
}
#endif
