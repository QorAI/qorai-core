// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'

import * as qora from '@qorai/qora/tokens/css/variables'

export const errorIconColor = qora.color.systemfeedback.errorIcon

export const IconContainer = styled.div<{
  iconColor?: string
}>`
  --qora-icon-size: 35px;
  --qora-icon-color: ${(p) => p.iconColor || 'unset'};
  width: 80px;
  height: 80px;
  padding: 14px;
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 120px;
  background-color: ${qora.color.container.highlight};
`

export const DashedHorizontalLine = styled.div`
  display: inline-block;
  width: 46px;
  color: ${qora.color.divider.strong};
  border: 1px ${qora.color.divider.strong} dashed;
`

export const CardContent = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: space-between;
  padding: 0px 16px;
  border-radius: 16px;
  margin: 8px;
  background: ${qora.color.container.background};
  box-shadow: 0px 1px 2px 0px rgba(0, 0, 0, 0.05);
`

export const Title = styled.p`
  margin: 0px;
  padding: 16px 16px;
  width: 100%;
  vertical-align: middle;
  min-height: 44px;
  color: ${qora.color.text.primary};
  text-align: center;
  font: ${qora.font.heading.h4};
  border-bottom: 1px solid ${qora.color.divider.subtle};
`

export const HeadingText = styled.p`
  padding: 0px;
  text-align: center;
  margin: 0;
  color: ${qora.color.text.primary};
  font: ${qora.font.heading.h3};
`

export const BulletPoints = styled.ul`
  text-align: left;
  padding-left: 38px;
  & li {
    color: ${qora.color.text.secondary};
    font: ${qora.font.default.regular};
  }
  & a {
    color: ${qora.color.text.secondary};
    font: ${qora.font.default.regular};
  }
`

export const TermsText = styled.p`
  display: flex;
  padding: ${qora.spacing.l};
  flex-direction: column;
  align-items: center;
  gap: 8px;
  align-self: stretch;
  border-radius: ${qora.radius.l};
  background: ${qora.color.page.background};
  color: ${qora.color.text.tertiary};
  text-align: center;
  font: ${qora.font.small.regular};

  & strong {
    font-weight: 600;
  }

  & a {
    color: ${qora.color.text.tertiary};
    font: ${qora.font.small.regular};
  }
`

export const OptionsRow = styled.div`
  display: flex;
  flex-direction: row;
  width: 100%;
  padding: 16px 0px;
  align-items: center;
  justify-content: center;
  gap: 8px;

  & > * {
    flex-basis: 50%;
  }
`
