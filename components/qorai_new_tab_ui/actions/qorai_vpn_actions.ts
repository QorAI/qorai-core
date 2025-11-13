// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { createAction } from 'redux-act'
import * as QoraiVPN from '../api/qoraiVpn'

export const initialize = createAction<QoraiVPN.PurchasedState>('initialize')
export const toggleConnection = createAction('toggleConnection')
export const launchVPNPanel = createAction('launchVPNPanel')
export const openVPNAccountPage =
  createAction<QoraiVPN.ManageURLType>('openVPNAccountPage')
export const purchasedStateChanged = createAction<QoraiVPN.PurchasedState>(
  'purchasedStateChanged'
)
export const connectionStateChanged = createAction<QoraiVPN.ConnectionState>(
  'connectionStateChanged'
)
export const selectedRegionChanged = createAction<QoraiVPN.Region>(
  'connectionStateChanged'
)
