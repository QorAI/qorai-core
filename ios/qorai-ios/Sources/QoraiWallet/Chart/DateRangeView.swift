// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation
import Strings
import SwiftUI

struct DateRangeView: View {
  @Binding var selectedRange: QoraiWallet.AssetPriceTimeframe
  @Environment(\.sizeCategory) private var sizeCategory
  @Environment(\.horizontalSizeClass) private var horizontalSizeClass

  private var accessibilityRows: [[QoraiWallet.AssetPriceTimeframe]] {
    [
      [.live, .oneDay, .oneWeek],
      [.oneMonth, .threeMonths, .oneYear, .all],
    ]
  }

  @ViewBuilder private func button(for range: QoraiWallet.AssetPriceTimeframe) -> some View {
    Button {
      selectedRange = range
    } label: {
      Text(verbatim: range.displayString)
        .accessibility(label: Text(verbatim: range.accessibilityLabel))
    }
    .buttonStyle(OptionButtonStyle(isSelected: range == selectedRange))
  }

  var body: some View {
    Group {
      if sizeCategory.isAccessibilityCategory && horizontalSizeClass == .compact {
        // Split into 2 rows
        VStack {
          ForEach(accessibilityRows, id: \.self) { row in
            HStack(spacing: 0) {
              ForEach(row, id: \.rawValue) { range in
                button(for: range)
                if range != row.last {
                  Spacer()
                }
              }
            }
          }
        }
      } else {
        HStack(spacing: horizontalSizeClass == .regular ? 6 : 0) {
          ForEach(QoraiWallet.AssetPriceTimeframe.allCases, id: \.rawValue) { range in
            button(for: range)
            if range != QoraiWallet.AssetPriceTimeframe.allCases.last
              && horizontalSizeClass == .compact
            {
              Spacer()
            }
          }
        }
      }
    }
    .font(.caption.bold())
  }
}

extension QoraiWallet.AssetPriceTimeframe: CaseIterable {
  public static var allCases: [QoraiWallet.AssetPriceTimeframe] {
    [.live, .oneDay, .oneWeek, .oneMonth, .threeMonths, .oneYear, .all]
  }

  var accessibilityLabel: String {
    switch self {
    case .live: return Strings.Wallet.dateIntervalHourAccessibilityLabel
    case .oneDay: return Strings.Wallet.dateIntervalDayAccessibilityLabel
    case .oneWeek: return Strings.Wallet.dateIntervalWeekAccessibilityLabel
    case .oneMonth: return Strings.Wallet.dateIntervalMonthAccessibilityLabel
    case .threeMonths: return Strings.Wallet.dateIntervalThreeMonthsAccessibilityLabel
    case .oneYear: return Strings.Wallet.dateIntervalYearAccessibilityLabel
    case .all: return Strings.Wallet.dateIntervalAll
    @unknown default: return ""
    }
  }

  var displayString: String {
    switch self {
    case .live: return Strings.Wallet.dateIntervalHour
    case .oneDay: return Strings.Wallet.dateIntervalDay
    case .oneWeek: return Strings.Wallet.dateIntervalWeek
    case .oneMonth: return Strings.Wallet.dateIntervalMonth
    case .threeMonths: return Strings.Wallet.dateIntervalThreeMonths
    case .oneYear: return Strings.Wallet.dateIntervalYear
    case .all: return Strings.Wallet.dateIntervalAll.uppercased()
    @unknown default: return ""
    }
  }
}

private struct OptionButtonStyle: ButtonStyle {
  var isSelected: Bool

  @Environment(\.colorScheme) private var colorScheme

  private var backgroundShape: some View {
    RoundedRectangle(cornerRadius: 6, style: .continuous)
      .fill(Color(.secondaryQoraiLabel))
  }

  func makeBody(configuration: Configuration) -> some View {
    configuration.label
      .foregroundColor(.white)
      // To animate text color
      .colorMultiply(isSelected ? Color(.qoraiBackground) : Color(.secondaryQoraiLabel))
      .padding(.horizontal, 6)
      .padding(.vertical, 4)
      .background(
        backgroundShape
          .opacity(configuration.isPressed ? 0.1 : 0.0)
      )
      .background(
        backgroundShape
          .opacity(isSelected ? 1.0 : 0.0)
      )
      .animation(.linear(duration: 0.1), value: configuration.isPressed || isSelected)
      .accessibility(addTraits: isSelected ? .isSelected : [])
  }
}
