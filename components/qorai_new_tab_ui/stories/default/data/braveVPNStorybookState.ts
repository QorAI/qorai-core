// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { QoraiVPNState } from '../../../reducers/qorai_vpn'
import * as QoraiVPN from '../../../api/qoraiVpn'

export default function getQoraiVPNState (): QoraiVPNState {
  return {
    purchasedState: QoraiVPN.PurchasedState.NOT_PURCHASED,
    connectionState: QoraiVPN.ConnectionState.DISCONNECTED,
    selectedRegion: new QoraiVPN.Region()
  }
}
