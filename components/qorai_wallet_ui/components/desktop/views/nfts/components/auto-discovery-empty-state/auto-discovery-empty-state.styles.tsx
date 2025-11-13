// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Ring from '@qorai/qora/react/progressRing'

import { WalletButton } from '../../../../../shared/style'

export const StyledWrapper = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  width: 100%;
  margin-top: 10px;
`

export const Heading = styled.h3`
  font-family: 'Poppins';
  font-style: normal;
  font-weight: 600;
  font-size: 14px;
  line-height: 24px;
  text-align: center;
  color: ${qora.color.text.secondary};
  margin: 0 0 8px 0;
  padding: 0;
`

export const Description = styled.span`
  font-family: 'Poppins';
  font-style: normal;
  font-weight: 400;
  font-size: 12px;
  line-height: 18px;
  color: ${qora.color.text.tertiary};
`

export const ActionButton = styled(WalletButton)`
  font-family: 'Poppins';
  font-style: normal;
  font-weight: 600;
  font-size: 12px;
  line-height: 18px;
  background: transparent;
  color: ${qora.color.button.background};
  border: none;
  cursor: pointer;
`

export const LoadingRing = styled(Ring)`
  --qora-progressring-size: 24px;
`

export const RefreshText = styled.div`
  color: ${qora.color.text.secondary};
  text-align: center;
  font-family: Poppins;
  font-size: 14px;
  font-style: normal;
  font-weight: 400;
  line-height: 24px;
`
