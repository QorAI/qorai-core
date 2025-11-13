// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { createReducer } from 'redux-act'
import * as Actions from '../../actions/qorai_vpn_actions'
import * as QoraiVPN from '../../api/qoraiVpn'

// Set true to initialzied when final purchased state is received once.
// Before that, vpn card is not rendered.
export type QoraiVPNState = {
  purchasedState: QoraiVPN.PurchasedState
  connectionState: QoraiVPN.ConnectionState
  selectedRegion: QoraiVPN.Region
}

const defaultState: QoraiVPNState = {
  purchasedState: QoraiVPN.PurchasedState.NOT_PURCHASED,
  connectionState: QoraiVPN.ConnectionState.DISCONNECTED,
  selectedRegion: new QoraiVPN.Region()
}

const reducer = createReducer<QoraiVPNState>({}, defaultState)

reducer.on(Actions.connectionStateChanged, (state, payload): QoraiVPNState => {
  return {
    ...state,
    connectionState: payload
  }
})

reducer.on(Actions.purchasedStateChanged, (state, payload): QoraiVPNState => {
  // Don't update if it's in-progress to prevent unnecessary vpn card page chanage.
  const isLoading = payload === QoraiVPN.PurchasedState.LOADING

  return {
    ...state,
    purchasedState:
      isLoading
        ? state.purchasedState
        : payload
  }
})

reducer.on(Actions.selectedRegionChanged, (state, payload): QoraiVPNState => {
  return {
    ...state,
    selectedRegion: payload
  }
})

export default reducer
