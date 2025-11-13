// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

import QoraiShields
import QoraiWidgetsModels
import Foundation
import Strings
import UIKit

struct StatData {
  var name: String
  var value: String
  var color: UIColor = .qoraiLabel
}

extension StatKind {
  var valueColor: UIColor {
    switch self {
    case .adsBlocked:
      return UIColor(rgb: 0xFB542B)
    case .dataSaved:
      return UIColor(rgb: 0xA0A5EB)
    case .timeSaved:
      return .qoraiLabel
    case .unknown:
      return .qoraiLabel
    @unknown default:
      assertionFailure()
      return .qoraiLabel
    }
  }

  var name: String {
    switch self {
    case .adsBlocked:
      return Strings.Shields.shieldsAdAndTrackerStats
    case .dataSaved:
      return Strings.Shields.dataSavedStat
    case .timeSaved:
      return Strings.Shields.shieldsTimeStats
    case .unknown:
      return ""
    @unknown default:
      assertionFailure()
      return ""
    }
  }

  var displayString: String {
    switch self {
    case .adsBlocked:
      return QoraiGlobalShieldStats.shared.adblock.kFormattedNumber
    case .dataSaved:
      return QoraiGlobalShieldStats.shared.dataSaved
    case .timeSaved:
      return QoraiGlobalShieldStats.shared.timeSaved
    case .unknown:
      return ""
    @unknown default:
      assertionFailure()
      return ""
    }
  }
}
