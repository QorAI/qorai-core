// Copyright 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiUI
import Static
import SwiftUI
import UIKit

class QoraiVPNServerLocationCell: UITableViewCell, Cell {

  static let textAccessoryKey = "textAccessoryImageName"

  override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
    super.init(style: .default, reuseIdentifier: reuseIdentifier)
  }

  required init?(coder aDecoder: NSCoder) {
    fatalError("init(coder:) has not been implemented")
  }

  func configure(row: Row) {
    accessoryType = row.accessory.type

    var titleAccessory: UIImage?
    if let imageName = row.context?[QoraiVPNServerLocationCell.textAccessoryKey] as? String {
      titleAccessory = UIImage(qoraiSystemNamed: imageName)
    }

    self.contentConfiguration = UIHostingConfiguration {
      HStack {
        if let image = row.image {
          Image(uiImage: image)
        }
        QoraiVPNLabelView(
          title: row.text ?? "",
          titleAccessory: titleAccessory,
          subtitle: row.detailText
        )
        Spacer()
      }
    }
    .background {
      Color.clear
    }
  }
}
