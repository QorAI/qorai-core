// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStore
import DesignSystem
import StoreKit
import SwiftUI

enum QoraiVPNSubscriptionTier: String {
  case monthly = "yearly"
  case yearly = "monthly"
}

struct QoraiVPNPremiumTierSelectionView: View {
  var originalProduct: SKProduct?
  var discountedProduct: SKProduct?

  var type: QoraiVPNSubscriptionTier

  @Binding
  var selectedTierType: QoraiVPNSubscriptionTier

  var body: some View {
    Button(
      action: {
        selectedTierType = type
      },
      label: {
        VStack(alignment: .leading, spacing: 8.0) {
          HStack {
            Text(type == .yearly ? Strings.VPN.yearlySubTitle : Strings.VPN.monthlySubTitle)
              .font(.headline)
              .foregroundStyle(.white)

            if type == .yearly {
              Text(Strings.VPN.yearlySubDisclaimer)
                .font(.caption2.weight(.bold))
                .foregroundColor(.white)
                .padding(4.0)
                .background(
                  LinearGradient(
                    gradient:
                      Gradient(colors: [
                        Color(UIColor(rgb: 0xFF4000)),
                        Color(UIColor(rgb: 0xFF1F01)),
                      ]),
                    startPoint: .init(x: 0.26, y: 0.0),
                    endPoint: .init(x: 0.26, y: 1.0)
                  )
                )
                .clipShape(RoundedRectangle(cornerRadius: 4.0, style: .continuous))
            }

            Spacer()

            if let product = originalProduct,
              let formattedPrice = product.price.frontSymbolCurrencyFormatted(
                with: product.priceLocale
              )
            {
              createPriceTagLabel(product: product, price: formattedPrice)
            } else {
              ProgressView()
                .tint(Color.white)
            }
          }

          HStack(spacing: 2) {
            Text(type == .yearly ? Strings.VPN.renewAnnually : Strings.VPN.renewMonthly)
              .font(.subheadline)
              .foregroundColor(Color(qoraiSystemName: .primitiveBlurple95))

            if type == .yearly {
              createDiscountPercentageLabel()
            }

            Spacer()

            if type == .yearly, let product = originalProduct {
              createDiscountTagLabel(product: product, price: "")
            }
          }
        }
        .padding()
        .background(
          Color(
            qoraiSystemName: selectedTierType == type ? .primitivePrimary40 : .primitivePrimary20
          )
        )
        .overlay(
          ContainerRelativeShape()
            .strokeBorder(
              Color(qoraiSystemName: .primitivePrimary50),
              lineWidth: selectedTierType == type ? 2.0 : 0.0
            )
        )
        .containerShape(RoundedRectangle(cornerRadius: 8.0, style: .continuous))
      }
    )
    .frame(maxWidth: .infinity)
    .buttonStyle(.plain)
  }

  @ViewBuilder
  private func createPriceTagLabel(product: SKProduct, price: String) -> some View {
    Text(
      "\(product.priceLocale.currency?.identifier ?? "")"
    )
    .font(.footnote)
    .foregroundColor(Color(qoraiSystemName: .primitiveBlurple95))

      + Text(
        " \(price)"
      )
      .font(.headline)
      .foregroundColor(.white)

      + Text(
        "/ \(type == .monthly ? Strings.VPN.paywallMonthlyPriceDividend : Strings.VPN.paywallYearlyPriceDividend)"
      )
      .font(.footnote)
      .foregroundColor(Color(qoraiSystemName: .primitiveBlurple95))
  }

  @ViewBuilder
  private func createDiscountPercentageLabel() -> some View {
    let yearlyDouble = originalProduct?.price.doubleValue ?? 0.0
    let discountDouble = discountedProduct?.price.multiplying(by: 12).doubleValue ?? 0.0
    let discountSavingPercentage =
      discountDouble > 0.0 ? 100 - Int((yearlyDouble * 100) / discountDouble) : 0

    Group {
      Text("(")
        + Text("\(Strings.VPN.save) \(discountSavingPercentage)%")
        .underline()
        .fontWeight(.semibold)
        + Text(")")
    }
    .foregroundColor(Color(qoraiSystemName: .primitiveBlurple95))
    .font(.subheadline)
  }

  @ViewBuilder
  private func createDiscountTagLabel(product: SKProduct, price: String) -> some View {
    let discountDouble =
      discountedProduct?.price.multiplying(by: 12).frontSymbolCurrencyFormatted(
        with: product.priceLocale
      ) ?? ""

    Group {
      Text(product.priceLocale.currency?.identifier ?? "")
        .font(.footnote)
        .foregroundColor(Color(qoraiSystemName: .primitiveBlurple95))
        + Text("\(discountDouble)")
        .font(.subheadline.weight(.semibold))
        .kerning(0.075)
        .foregroundColor(.white)
    }
    .strikethrough()
    .opacity(0.6)
  }
}

#if DEBUG
struct QoraiVPNPremiumTierSelectionView_Previews: PreviewProvider {
  static var previews: some View {
    let mockMonthlyProduct = QoraiVPNMockSKProduct(
      price: NSDecimalNumber(string: "9.99"),
      priceLocale: Locale(identifier: "en_US")
    )

    let mockYearlyProduct = QoraiVPNMockSKProduct(
      price: NSDecimalNumber(string: "99.99"),
      priceLocale: Locale(identifier: "en_US")
    )

    VStack {
      QoraiVPNPremiumTierSelectionView(
        originalProduct: mockYearlyProduct,
        discountedProduct: mockMonthlyProduct,
        type: .yearly,
        selectedTierType: Binding.constant(.yearly)
      )

      QoraiVPNPremiumTierSelectionView(
        originalProduct: mockYearlyProduct,
        discountedProduct: mockMonthlyProduct,
        type: .yearly,
        selectedTierType: Binding.constant(.monthly)
      )

      QoraiVPNPremiumTierSelectionView(
        originalProduct: mockMonthlyProduct,
        discountedProduct: nil,
        type: .monthly,
        selectedTierType: Binding.constant(.monthly)
      )

      QoraiVPNPremiumTierSelectionView(
        originalProduct: mockMonthlyProduct,
        discountedProduct: nil,
        type: .monthly,
        selectedTierType: Binding.constant(.yearly)
      )
    }
    .padding()
    .background(
      Color(qoraiSystemName: .primitivePrimary10)
    )
  }
}
#endif
