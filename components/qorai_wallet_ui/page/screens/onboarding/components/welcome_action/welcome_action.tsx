// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import * as qora from '@qorai/qora/tokens/css/variables'

// styles
import {
  Column,
  Row,
  VerticalSpace,
} from '../../../../../components/shared/style'
import {
  WelcomeActionWrapper,
  Title,
  Description,
  TitleIcon,
  IconWrapper,
  WalletIcon,
} from './welcome_action.style'

interface Props {
  iconName: string
  title: string
  description: string
  walletIcons?: Array<string | React.ReactNode>
  onSelect: () => void
}

export const WelcomeAction = ({
  iconName,
  title,
  description,
  walletIcons,
  onSelect,
}: Props) => {
  return (
    <WelcomeActionWrapper onClick={onSelect}>
      <Row
        width='100%'
        justifyContent='flex-start'
        alignItems='flex-start'
        gap={qora.spacing.xl}
      >
        <IconWrapper>
          <TitleIcon name={iconName} />
        </IconWrapper>
        <Column>
          <Title>{title}</Title>
          <VerticalSpace space={qora.spacing.m} />
          <Description>{description}</Description>
          <VerticalSpace space={qora.spacing.xl} />
          <Row
            justifyContent='flex-start'
            gap={qora.spacing.m}
            $wrap
          >
            {walletIcons?.map((icon, index) => (
              <React.Fragment key={index}>
                {typeof icon === 'string' ? (
                  <WalletIcon name={icon} />
                ) : (
                  <React.Fragment>{icon}</React.Fragment>
                )}
              </React.Fragment>
            ))}
          </Row>
        </Column>
      </Row>
    </WelcomeActionWrapper>
  )
}
