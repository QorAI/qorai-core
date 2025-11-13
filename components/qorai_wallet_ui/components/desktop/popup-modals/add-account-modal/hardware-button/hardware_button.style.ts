// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import Icon from '@qorai/qora/react/icon'
import * as qora from '@qorai/qora/tokens/css/variables'

export const Container = styled.button`
  display: flex;
  justify-content: flex-start;
  align-items: flex-start;
  padding: 24px;
  width: 100%;
  outline: none;
  border: none;
  background-color: transparent;
  cursor: pointer;
`

export const Title = styled.p`
  color: ${qora.color.text.primary};
  font: ${qora.font.heading.h3};
  padding: 0;
  margin: 0;
`

export const Description = styled.p`
  width: 90%;
  color: ${qora.color.text.primary};
  font: ${qora.font.default.regular};
  padding: 0;
  margin: 0;
  text-align: left;
`

export const ArrowIcon = styled(Icon).attrs({ name: 'arrow-right' })`
  --qora-icon-size: 24px;
  color: ${qora.color.icon.interactive};
`

export const Divider = styled.div`
  width: 100%;
  height: 1px;
  background: ${qora.color.divider.subtle};
`
