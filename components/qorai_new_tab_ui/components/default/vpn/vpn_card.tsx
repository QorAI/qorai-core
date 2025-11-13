/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import { useDispatch } from 'react-redux'
import styled from 'styled-components'

import Toggle from '@qorai/qora/react/toggle'
import { getLocale } from '$web-common/locale'
import Button from '@qorai/qora/react/button'
import Icon from '@qorai/qora/react/icon'
import { color, font, gradient, spacing } from '@qorai/qora/tokens/css/variables'
import VPNShieldsConnecting from './vpn-shields-connecting'
import * as Actions from '../../../actions/qorai_vpn_actions'
import { ConnectionState, ManageURLType, Region } from '../../../api/qoraiVpn'
import guardianLogoUrl from '../vpn/assets/guardian-logo.svg'
import vpnShieldsConnectedUrl from '../vpn/assets/vpn-shields-connected.svg'
import vpnShieldsDisconnectedUrl from '../vpn/assets/vpn-shields-disconnected.svg'

const HeaderIcon = styled(Icon)`
  --qora-icon-size: 24px;
  --qora-icon-color: ${gradient.iconsActive};
`

const StyledTitle = styled.div`
  font: ${font.heading.h4};
  color: ${color.white};
  display: flex;
  align-items: center;
  gap: 8px;
`

const WidgetWrapper = styled.div.attrs({ 'data-theme': 'dark' })`
  display: flex;
  flex-direction: column;
  align-items: flex-start;
  align-self: stretch;
  color: ${color.white};
  gap: ${spacing['2Xl']};
`

const WidgetContent = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 16px;
  align-self: stretch;
`

const PoweredBy = styled.div`
  display: flex;
  align-items: center;
  opacity: 0.5;
  gap: 4px;

  span {
    color: ${color.white};
    font: ${font.xSmall.regular};
    text-align: center;
  }
`

const GuardianLogo = styled.span`
  width: 56px;
  height: 12px;
  background-image: url(${guardianLogoUrl});
`

const SellingPoints = styled.div`
  display: flex;
  flex-direction: column;
  align-items: flex-start;
  gap: ${spacing.s};
  padding-left: ${spacing.xs};
  align-self: stretch;
`

const SellingPoint = styled.div`
  display: flex;
  align-items: center;
  gap: ${spacing.m};
  align-self: stretch;
`

const SellingPointIcon = styled(Icon)`
  align-self: start;
  margin: 1px;
  --qora-icon-size: ${spacing.l};
  --qora-icon-color: ${color.icon.disabled};
`

const SellingPointLabel = styled.span`
  color: ${color.text.primary};
  font: ${font.xSmall.regular};
`

const ActionArea = styled.div`
  display: flex;
  padding: 0px;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  gap: ${spacing.m};
  align-self: stretch;
`

const ActionButton = styled(Button)`
  align-self: stretch;
`

const ActionLink = styled.a`
  color: #fff;
  opacity: 0.5;
  font: ${font.small.link};
  line-height: 18px;
  letter-spacing: 0px;
  text-decoration-line: underline;
  text-decoration-style: solid;
  text-decoration-skip-ink: none;
  text-decoration-thickness: auto;
  text-underline-offset: auto;

  &:focus-visible {
    outline: 1.5px solid ${color.primary[40]};
  }
`

const VPNShileldsIcon = styled.div<{ connectionState: ConnectionState }>`
  width: 64px;
  height: 64px;
  background-image: url(${(p) =>
    p.connectionState === ConnectionState.CONNECTED
      ? vpnShieldsConnectedUrl
      : vpnShieldsDisconnectedUrl});
`

const ActionBox = styled.div`
  display: flex;
  align-items: center;
  gap: 23px;
  align-self: stretch;
`

const ConnectionInfoBox = styled.div`
  display: flex;
  flex-direction: column;
  align-items: flex-start;
  gap: ${spacing.xs};
  flex: 1 0 0;
`

const ConnectionStateLabel = styled.span<{ connected: boolean }>`
  align-self: stretch;
  color: ${(p) => (p.connected ? color.green[60] : color.text.primary)};
  font: ${font.small.regular};
`

const RegionAction = styled.div`
  display: flex;
  align-items: center;
  gap: ${spacing.m};
`

const RegionCountryLabel = styled.span`
  color: ${color.text.primary};
  font: ${font.large.semibold};
  height: 24px;
`

const RegionChangeLink = styled.a`
  color: ${color.text.primary};
  font: ${font.xSmall.link};
  text-decoration-line: underline;
  cursor: pointer;
`

const RegionCityLabel = styled.span`
  color: ${color.text.tertiary};
  font: ${font.xSmall.regular};
`

export const VPNWidgetTitle = () => {
  return (
    <>
      <HeaderIcon name='product-vpn' />
      {getLocale('qoraiVpnWidgetTitle')}
    </>
  )
}

const VPNWidgetHeader = () => {
  return (
    <StyledTitle>
      <VPNWidgetTitle />
    </StyledTitle>
  )
}

const FeatureList = () => (
  <SellingPoints>
    {[
      getLocale('qoraiVpnFeature1'),
      getLocale('qoraiVpnFeature2'),
      getLocale('qoraiVpnWidgetFeature3')
    ].map((entry) => (
      <SellingPoint key={entry}>
        <SellingPointIcon name='shield-done' />
        <SellingPointLabel>{entry}</SellingPointLabel>
      </SellingPoint>
    ))}
  </SellingPoints>
)

export const VPNPromoWidget = () => {
  const dispatch = useDispatch()

  return (
    <WidgetWrapper>
      <VPNWidgetHeader />
      <WidgetContent>
        <PoweredBy>
          <span>{getLocale('qoraiVpnPoweredBy')}</span>
          <GuardianLogo />
        </PoweredBy>
        <FeatureList />
        <ActionArea>
          <ActionButton
            onClick={() =>
              dispatch(Actions.openVPNAccountPage(ManageURLType.CHECKOUT))
            }
          >
            {getLocale('qoraiVpnCTA')}
          </ActionButton>
          <ActionLink
            href='#'
            onClick={() =>
              dispatch(Actions.openVPNAccountPage(ManageURLType.RECOVER))
            }
          >
            {getLocale('qoraiVpnPurchased')}
          </ActionLink>
        </ActionArea>
      </WidgetContent>
    </WidgetWrapper>
  )
}

function GetConnectionStateLabel(connectionState: ConnectionState) {
  switch (connectionState) {
    case ConnectionState.CONNECTED:
      return getLocale('qoraiVpnConnected')
    case ConnectionState.CONNECTING:
      return getLocale('qoraiVpnConnecting')
    case ConnectionState.DISCONNECTING:
      return getLocale('qoraiVpnDisconnecting')
    default:
      break
  }

  return getLocale('qoraiVpnDisconnected')
}

interface MainWidgetProps {
  connectionState: ConnectionState
  selectedRegion: Region
}

export const VPNMainWidget = (props: MainWidgetProps) => {
  const dispatch = useDispatch()
  const connected = props.connectionState === ConnectionState.CONNECTED

  return (
    <WidgetWrapper>
      <VPNWidgetHeader />
      <WidgetContent>
        {props.connectionState === ConnectionState.CONNECTING ? (
          <VPNShieldsConnecting />
        ) : (
          <VPNShileldsIcon connectionState={props.connectionState} />
        )}
        <ActionBox>
          <ConnectionInfoBox>
            <ConnectionStateLabel connected={connected}>
              {GetConnectionStateLabel(props.connectionState)}
            </ConnectionStateLabel>
            <RegionAction>
              <RegionCountryLabel>
                {props.selectedRegion.country}
              </RegionCountryLabel>
              <RegionChangeLink
                onClick={() => dispatch(Actions.launchVPNPanel())}
              >
                {getLocale('qoraiVpnChangeRegion')}
              </RegionChangeLink>
            </RegionAction>
            <RegionCityLabel>
              {props.selectedRegion.namePretty === props.selectedRegion.country
                ? getLocale('qoraiVpnOptimal')
                : props.selectedRegion.namePretty}
            </RegionCityLabel>
          </ConnectionInfoBox>
          <Toggle
            checked={
              props.connectionState === ConnectionState.CONNECTED ||
              props.connectionState === ConnectionState.CONNECTING
            }
            onChange={() => dispatch(Actions.toggleConnection())}
          />
        </ActionBox>
      </WidgetContent>
    </WidgetWrapper>
  )
}
