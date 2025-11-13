// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import Icon from '@qorai/qora/react/icon'
import * as qora from '@qorai/qora/tokens/css/variables'
import Input from '@qorai/qora/react/input'

// Assets
import { LoaderIcon } from 'qorai-ui/components/icons'

// Shared Styles
import {
  Row,
  Column,
  Text,
  WalletButton,
} from '../../../../../components/shared/style'
import {
  layoutSmallWidth, //
} from '../../../../../components/desktop/wallet-page-wrapper/wallet-page-wrapper.style'

export const AccountSection = styled(Row)`
  border-bottom: 1px solid ${qora.color.divider.subtle};
`

export const Wrapper = styled(Column)`
  flex: 1;
  padding: 24px 0px;
  @media screen and (max-width: ${layoutSmallWidth}px) {
    padding: 0px 8px;
  }
`

export const SearchBoxContainer = styled(Column)`
  padding: 0px 40px;
  @media screen and (max-width: ${layoutSmallWidth}px) {
    padding: 0px 8px;
  }
`

export const ScrollContainer = styled(Column)`
  flex: 1;
  overflow-x: hidden;
  overflow-y: auto;
  padding: 0px 40px;
  @media screen and (max-width: ${layoutSmallWidth}px) {
    padding: 0px 8px;
  }
`

export const LabelText = styled(Text)`
  color: ${qora.color.text.primary};
  line-height: 20px;
`

export const InputSection = styled(Column)`
  padding: 0px 40px;
  @media screen and (max-width: ${layoutSmallWidth}px) {
    padding: 0px 16px;
  }
`

export const AddressInput = styled(Input)`
  width: 100%;
`

export const AddressButton = styled(WalletButton)`
  cursor: pointer;
  display: flex;
  outline: none;
  border: none;
  background-color: none;
  background: none;
  width: 100%;
  border-radius: 10px;
  padding: 8px;
  justify-content: flex-start;
  align-items: center;
  flex-direction: row;
  &:disabled {
    opacity: 0.4;
    cursor: not-allowed;
  }
  &:hover:not([disabled]) {
    box-shadow: ${qora.effect.elevation['01']};
  }
`

export const AddressButtonText = styled(Text)`
  line-height: 22px;
  white-space: pre-wrap;
  word-break: break-all;
`

export const WalletIcon = styled(Icon).attrs({
  name: 'product-qorai-wallet',
})`
  --qora-icon-size: 40px;
  color: ${qora.color.icon.default};
  margin-right: 8px;
`

export const DomainLoadIcon = styled(LoaderIcon)<{ position: number }>`
  color: ${qora.color.icon.default};
  height: 20px;
  width: 20px;
  margin-right: 10px;
`
