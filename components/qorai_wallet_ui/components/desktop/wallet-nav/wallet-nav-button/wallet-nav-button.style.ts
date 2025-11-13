// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'
import { WalletButton, Text } from '../../../shared/style'
import { layoutSmallWidth } from '../../wallet-page-wrapper/wallet-page-wrapper.style'

export const StyledButton = styled(WalletButton)<{ isSelected?: boolean }>`
  --icon-color: ${(p) =>
    p.isSelected ? qora.color.icon.interactive : qora.color.neutral[30]};
  --text-color: ${(p) =>
    p.isSelected ? qora.color.text.interactive : qora.color.text.secondary};
  --indicator-color: ${(p) =>
    p.isSelected ? qora.color.icon.interactive : 'none'};
  &:hover {
    --icon-color: ${qora.color.icon.interactive};
    --text-color: ${qora.color.text.interactive};
  }
  display: flex;
  align-items: center;
  justify-content: flex-start;
  width: 100%;
  cursor: pointer;
  padding: 6px 0px;
  outline: none;
  border: none;
  background: none;
  margin-bottom: 12px;
  &:last-child {
    margin-bottom: 0px;
  }
  @media screen and (max-width: ${layoutSmallWidth}px) {
    border-radius: 6px;
    padding: 6px 0px 3px 0px;
    width: 100%;
    flex-direction: column;
    margin-bottom: 0px;
    margin-right: 8px;
    background-color: ${(p) =>
      p.isSelected ? qora.color.container.highlight : 'none'};
    &:hover {
      background-color: ${qora.color.container.highlight};
    }
    &:last-child {
      margin-right: 0px;
    }
  }
`

export const ButtonIcon = styled(Icon)`
  --qora-icon-size: 18px;
  color: var(--icon-color);
  margin-right: 16px;
  @media screen and (max-width: ${layoutSmallWidth}px) {
    color: ${qora.color.icon.default};
    --qora-icon-size: 24px;
    margin-right: 0px;
  }
`

export const ButtonText = styled(Text)`
  color: var(--text-color);
  font-family: 'Poppins';
  font-style: normal;
  font-weight: 600;
  font-size: 15px;
  line-height: 20px;
  @media screen and (max-width: ${layoutSmallWidth}px) {
    color: ${qora.color.icon.default};
    font-size: 12px;
    font-weight: 400;
    line-height: 18px;
  }
`

export const SelectedIndicator = styled.div`
  display: flex;
  width: 4px;
  height: 32px;
  margin-right: 20px;
  background-color: var(--indicator-color);
  border-radius: 0px 2px 2px 0px;
  @media screen and (max-width: ${layoutSmallWidth}px) {
    display: none;
  }
`
