/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import createWidget, { WidgetProps } from '../widget/index'
import { StyledCard, StyledTitleTab } from '../widgetCard'
import { VPNMainWidget, VPNPromoWidget, VPNWidgetTitle } from './vpn_card'
import { QoraiVPNState } from 'components/qorai_new_tab_ui/reducers/qorai_vpn'
import * as QoraiVPN from '../../../api/qoraiVpn'
import { useNewTabPref } from '../../../hooks/usePref'

export interface VPNProps {
  showContent: boolean
  onShowContent: () => void
  qoraiVPNState: QoraiVPNState
}

const VPNWidgetInternal = createWidget((props: VPNProps) => {
  if (!props.showContent) {
    return (
      <StyledTitleTab onClick={props.onShowContent}>
        <VPNWidgetTitle />
      </StyledTitleTab>
    )
  }

  return (
    <StyledCard>
      {props.qoraiVPNState.purchasedState ===
      QoraiVPN.PurchasedState.PURCHASED ? (
        <VPNMainWidget
          connectionState={props.qoraiVPNState.connectionState}
          selectedRegion={props.qoraiVPNState.selectedRegion}
        />
      ) : (
        <VPNPromoWidget />
      )}
    </StyledCard>
  )
})

export const VPNWidget = (props: WidgetProps & VPNProps) => {
  const [, saveShowQoraiVPN] = useNewTabPref('showQoraiVPN')

  return (
    <VPNWidgetInternal
      {...props}
      hideWidget={() => saveShowQoraiVPN(false)}
    />
  )
}
