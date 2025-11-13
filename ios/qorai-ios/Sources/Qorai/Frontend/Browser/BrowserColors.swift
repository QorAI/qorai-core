// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiUI
import DesignSystem
import Foundation
import UIKit

/// A set of browser theme colors found in the `🦁 Browser` Figma doc. There will be a separate set depending
/// on the browsing mode you're in (standard vs private)
protocol BrowserColors {
  // MARK: - Text
  var textPrimary: UIColor { get }
  var textSecondary: UIColor { get }
  var textTertiary: UIColor { get }
  var textDisabled: UIColor { get }
  var textInteractive: UIColor { get }

  // MARK: - Icon
  var iconDefault: UIColor { get }
  var iconDisabled: UIColor { get }
  var iconActive: UIColor { get }

  // MARK: - BrowserButton
  var browserButtonBackgroundHover: UIColor { get }
  var browserButtonBackgroundActive: UIColor { get }

  // MARK: - TabSwitcher
  var tabSwitcherForeground: UIColor { get }
  var tabSwitcherSelectedCellBorder: UIColor { get }
  var tabSwitcherCellBackground: UIColor { get }
  var tabSwitcherBackground: UIColor { get }

  // MARK: - Container
  var containerBackground: UIColor { get }
  var containerInteractive: UIColor { get }
  var containerScrim: UIColor { get }
  var containerFrostedGlass: UIColor { get }

  // MARK: - Chrome
  var chromeBackground: UIColor { get }

  // MARK: - Divider
  var dividerSubtle: UIColor { get }
  var dividerStrong: UIColor { get }

  // MARK: - TabBar
  var tabBarTabBackground: UIColor { get }
  var tabBarTabActiveBackground: UIColor { get }

  // MARK: - Favorites/Search View Controller
  var favoritesAndSearchScreenBackground: UIColor { get }
  var favoritesAndSearchScreenSectionBackground: UIColor { get }
  var favoritesAndSearchScreenSectionGroupBackground: UIColor { get }
}

extension BrowserColors where Self == StandardBrowserColors {
  /// The standard set of light & dark mode browser colors
  static var standard: StandardBrowserColors { .init() }
}

extension BrowserColors where Self == PrivateModeBrowserColors {
  /// The set of browser colors specific to private mode
  static var privateMode: PrivateModeBrowserColors { .init() }
}

/// The standard set of light & dark mode browser colors
struct StandardBrowserColors: BrowserColors {
  var textPrimary: UIColor {
    .init(light: .primitiveNeutral5, dark: .primitiveNeutral98)
  }

  var textSecondary: UIColor {
    .init(light: .primitiveNeutral25, dark: .primitiveNeutral80)
  }

  var textTertiary: UIColor {
    .init(light: .primitiveNeutral50, dark: .primitiveNeutral70)
  }

  var textDisabled: UIColor {
    .init(lightRGBA: 0x2124_2A80, darkRGBA: 0xEDEE_F180)
  }

  var textInteractive: UIColor {
    .init(light: .primitivePrimary40, dark: .primitivePrimary70)
  }

  var iconDefault: UIColor {
    .init(light: .primitiveNeutral50, dark: .primitiveNeutral70)
  }

  var iconDisabled: UIColor {
    .init(lightRGBA: 0x6874_8580, darkRGBA: 0xA1AB_BA80)
  }

  var iconActive: UIColor {
    .init(light: .primitivePrimary40, dark: .primitivePrimary70)
  }

  var browserButtonBackgroundHover: UIColor {
    .init(light: .primitiveNeutral95, dark: .primitiveNeutral20)
  }

  var browserButtonBackgroundActive: UIColor {
    .init(light: .primitiveNeutral90, dark: .primitiveNeutral5)
  }

  var tabSwitcherForeground: UIColor {
    .init(qoraiSystemName: .containerDisabled)
  }

  var tabSwitcherSelectedCellBorder: UIColor {
    .init(qoraiSystemName: .buttonBackground)
  }

  var tabSwitcherCellBackground: UIColor {
    .init(qoraiSystemName: .containerBackground)
  }

  var tabSwitcherBackground: UIColor {
    .init(qoraiSystemName: .iosBrowserBackgroundIos)
  }

  var containerBackground: UIColor {
    .init(lightColor: .white, darkColor: .init(qoraiSystemName: .primitiveNeutral10))
  }

  var containerInteractive: UIColor {
    .init(light: .primitivePrimary95, dark: .primitivePrimary20)
  }

  var containerScrim: UIColor {
    .init(lightRGBA: 0x0D0F_1459, darkRGBA: 0x0D0F_14B3)
  }

  var containerFrostedGlass: UIColor {
    .init(lightRGBA: 0xFFFF_FFF7, darkRGBA: 0x2124_2AEB)
  }

  var chromeBackground: UIColor {
    .init(light: .primitiveNeutral98, dark: .primitiveNeutral5)
  }

  var dividerSubtle: UIColor {
    .init(lightRGBA: 0xA1AB_BA66, darkRGBA: 0x6874_8566)
  }

  var dividerStrong: UIColor {
    .init(lightRGBA: 0x6874_8566, darkRGBA: 0xA1AB_BA66)
  }

  var tabBarTabBackground: UIColor {
    .init(light: .primitiveNeutral95, dark: .primitiveNeutral5)
  }

  var tabBarTabActiveBackground: UIColor {
    .init(light: .primitiveNeutral98, dark: .primitiveNeutral10)
  }

  var favoritesAndSearchScreenBackground: UIColor {
    .init(light: .primitiveNeutral95, dark: .primitiveNeutral0)
  }

  var favoritesAndSearchScreenSectionBackground: UIColor {
    .init(qoraiSystemName: .materialThin)
  }

  var favoritesAndSearchScreenSectionGroupBackground: UIColor {
    self.containerBackground
  }
}

/// The set of browser colors specific to private mode
struct PrivateModeBrowserColors: BrowserColors {
  var textPrimary: UIColor {
    .init(qoraiSystemName: .primitivePrivateWindow98)
  }

  var textSecondary: UIColor {
    .init(qoraiSystemName: .primitivePrivateWindow80)
  }

  var textTertiary: UIColor {
    .init(qoraiSystemName: .primitivePrivateWindow70)
  }

  var textDisabled: UIColor {
    .init(rgba: 0xEEEB_FF80)
  }

  var textInteractive: UIColor {
    .init(qoraiSystemName: .primitivePrimary70)
  }

  var iconDefault: UIColor {
    .init(qoraiSystemName: .primitivePrivateWindow70)
  }

  var iconDisabled: UIColor {
    .init(rgba: 0xA380_FF80)
  }

  var iconActive: UIColor {
    .init(qoraiSystemName: .primitivePrimary70)
  }

  var browserButtonBackgroundHover: UIColor {
    .init(qoraiSystemName: .primitivePrivateWindow20)
  }

  var browserButtonBackgroundActive: UIColor {
    .init(qoraiSystemName: .primitivePrivateWindow5)
  }

  var tabSwitcherForeground: UIColor {
    .init(qoraiSystemName: .privateWindow20)
  }

  var tabSwitcherCellBackground: UIColor {
    .init(qoraiSystemName: .privateWindow20)
  }

  var tabSwitcherSelectedCellBorder: UIColor {
    .init(qoraiSystemName: .buttonBackground)
  }

  var tabSwitcherBackground: UIColor {
    .init(qoraiSystemName: .privateWindow5)
  }

  var containerBackground: UIColor {
    .init(qoraiSystemName: .primitivePrivateWindow10)
  }

  var containerInteractive: UIColor {
    .init(qoraiSystemName: .primitivePrimary10)
  }

  var containerScrim: UIColor {
    .init(rgba: 0x1305_2AB3)
  }

  var containerFrostedGlass: UIColor {
    .init(rgba: 0x2A0D_58EB)
  }

  var chromeBackground: UIColor {
    .init(qoraiSystemName: .primitivePrivateWindow5)
  }

  var dividerSubtle: UIColor {
    .init(rgba: 0x7B63_BF66)
  }

  var dividerStrong: UIColor {
    .init(rgba: 0xA380_FF66)
  }

  var tabBarTabBackground: UIColor {
    .init(qoraiSystemName: .primitivePrivateWindow5)
  }

  var tabBarTabActiveBackground: UIColor {
    .init(qoraiSystemName: .primitivePrivateWindow10)
  }

  var favoritesAndSearchScreenBackground: UIColor {
    .init(light: .primitivePrivateWindow25, dark: .primitivePrivateWindow5)
  }

  var favoritesAndSearchScreenSectionBackground: UIColor {
    .init(light: .primitivePrivateWindow40, dark: .primitivePrivateWindow15)
  }

  var favoritesAndSearchScreenSectionGroupBackground: UIColor {
    .init(light: .primitivePrivateWindow50, dark: .primitivePrivateWindow25)
  }
}

extension UIColor {
  fileprivate convenience init(light: FigmaColorResource, dark: FigmaColorResource) {
    self.init(dynamicProvider: { traitCollection in
      if traitCollection.userInterfaceStyle == .dark {
        return .init(qoraiSystemName: dark)
      }
      return .init(qoraiSystemName: light)
    })
  }

  fileprivate convenience init(lightColor: UIColor, darkColor: UIColor) {
    self.init(dynamicProvider: { traitCollection in
      if traitCollection.userInterfaceStyle == .dark {
        return darkColor
      }
      return lightColor
    })
  }

  fileprivate convenience init(lightRGBA: UInt32, darkRGBA: UInt32) {
    self.init(dynamicProvider: { traitCollection in
      if traitCollection.userInterfaceStyle == .dark {
        return .init(rgba: darkRGBA)
      }
      return .init(rgba: lightRGBA)
    })
  }
}
