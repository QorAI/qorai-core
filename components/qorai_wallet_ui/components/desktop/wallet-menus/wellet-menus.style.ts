// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'

// Types
import { AccountModalTypes } from '../../../constants/types'

// Shared Styles
import { WalletButton, Row } from '../../shared/style'
import {
  layoutPanelWidth,
  layoutSmallWidth,
} from '../wallet-page-wrapper/wallet-page-wrapper.style'

export const StyledWrapper = styled.div<{
  yPosition?: number
  right?: number
  left?: number
  padding?: string
}>`
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  padding: ${(p) => p.padding ?? '8px 8px 0px 8px'};
  background-color: ${qora.color.container.background};
  border-radius: 8px;
  border: 1px solid ${qora.color.divider.subtle};
  box-shadow: 0px 1px 4px rgba(0, 0, 0, 0.25);
  position: absolute;
  top: ${(p) => (p.yPosition !== undefined ? p.yPosition : 35)}px;
  right: ${(p) => {
    if (p.left !== undefined) {
      return 'unset'
    }
    if (p.right !== undefined) {
      return `${p.right}px`
    }
    return '0px'
  }};
  left: ${(p) => {
    if (p.right !== undefined) {
      return 'unset'
    }
    if (p.left !== undefined) {
      return `${p.left}px`
    }
    return 'unset'
  }};
  z-index: 20;
`

export const PopupButton = styled(WalletButton)<{
  minWidth?: number
}>`
  display: flex;
  align-items: center;
  justify-content: flex-start;
  text-align: left;
  cursor: pointer;
  min-width: ${(p) => (p.minWidth !== undefined ? p.minWidth : 220)}px;
  border-radius: 8px;
  outline: none;
  border: none;
  background: none;
  padding: 12px 8px;
  margin: 0px 0px 8px 0px;
  background-color: transparent;
  width: 100%;
  &:hover {
    background-color: ${qora.color.divider.subtle};
  }
`

export const PopupButtonText = styled.span`
  flex: 1;
  font-family: Poppins;
  font-style: normal;
  font-size: 14px;
  font-weight: 400;
  line-height: 24px;
  color: ${qora.color.text.primary};
`

export const ButtonIcon = styled(Icon)<{ id?: AccountModalTypes }>`
  --qora-icon-size: 18px;
  color: ${(p) =>
    p.id === 'shield'
      ? qora.color.systemfeedback.successIcon
      : qora.color.icon.default};
  margin-right: 16px;
`

export const ToggleRow = styled.label`
  display: flex;
  align-items: center;
  justify-content: space-between;
  cursor: pointer;
  width: 220px;
  padding: 12px 8px;
  margin: 0px 0px 8px 0px;
  background-color: transparent;
`

export const LineChartWrapper = styled(StyledWrapper)`
  padding: 4px;
  gap: 4px;
  @media screen and (max-width: ${layoutSmallWidth}px) {
    left: 0px;
    right: unset;
  }
  @media screen and (max-width: ${layoutPanelWidth}px) {
    left: unset;
    right: 0px;
  }
`

export const LineChartButton = styled(PopupButton)`
  margin: 0px;
  padding: 6px 16px;
  &:hover {
    background-color: ${qora.color.page.background};
  }
`

export const SectionLabel = styled(Row)`
  background-color: ${qora.color.page.background};
  padding: 4px 8px;
  font: ${qora.font.components.label};
  text-transform: capitalize;
  color: ${qora.color.text.tertiary};
`
