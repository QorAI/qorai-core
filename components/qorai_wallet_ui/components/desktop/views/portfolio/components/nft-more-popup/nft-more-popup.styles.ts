// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'
import { WalletButton } from '../../../../../shared/style'

export const Popup = styled.div<{ isOpen: boolean }>`
  display: flex;
  position: absolute;
  bottom: 50px;
  right: 0;
  width: 100%;
  max-width: 226px;
  padding: ${qora.spacing.s};
  flex-direction: column;
  align-items: flex-start;
  gap: ${qora.spacing.s};
  border-radius: ${qora.spacing.m};
  border-radius: --qora-radius-m;
  border: 1px solid ${qora.color.divider.subtle};
  background-color: ${qora.color.container.background};
  box-shadow: 0px 4px 16px -2px rgba(0, 0, 0, 0.08);
  display: ${({ isOpen }) => (isOpen ? 'flex' : 'none')};
  transition:
    opacity 0.3s,
    transform 0.3s;
  opacity: ${({ isOpen }) => (isOpen ? 1 : 0)};
  transform: translateY(${({ isOpen }) => (isOpen ? '0' : '-10px')});
  z-index: 3;
`

export const PopupButton = styled(WalletButton)`
  display: flex;
  flex-direction: row;
  align-items: center;
  align-self: stretch;
  background-color: transparent;
  padding: 0px ${qora.spacing.m};
  height: 44px;
  gap: 16px;
  border: none;
  outline: transparent;
  cursor: pointer;
`

export const PopupButtonText = styled.span`
  color: ${qora.color.text.primary};
  font-family: Poppins;
  font-size: 14px;
  font-style: normal;
  font-weight: 400;
  line-height: 24px;
`

export const ButtonIcon = styled(Icon)`
  --qora-icon-size: 18px;
  color: ${qora.color.icon.default};
  margin-right: 8px;
`
