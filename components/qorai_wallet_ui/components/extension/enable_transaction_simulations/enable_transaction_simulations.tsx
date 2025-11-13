// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import Icon from '@qorai/qora/react/icon'

// types
import { QoraiWallet } from '../../../constants/types'

// utils
import { getLocale, formatLocale } from '$web-common/locale'
import { openTab } from '../../../utils/routes-utils'

// hooks
import {
  useSetIsTxSimulationOptInStatusMutation, //
} from '../../../common/slices/api.slice'

// components
import { LoadingPanel } from '../loading_panel/loading_panel'

// styles
import {
  Column,
  QoraSquaredButton,
  Row,
  VerticalDivider,
} from '../../shared/style'
import {
  BulletPoints,
  CardContent,
  DashedHorizontalLine,
  HeadingText,
  IconContainer,
  OptionsRow,
  TermsText,
  Title,
  errorIconColor,
} from './enable_transaction_simulations.styles'

const TX_SIMULATION_LEARN_MORE_LINK =
  'https://github.com/qorai/qorai-browser/wiki/Transaction-Simulation'
const BLOWFISH_PRIVACY_POLICY_URL = 'https://extension.blowfish.xyz/privacy'
const BLOWFISH_TERMS_URL = 'https://extension.blowfish.xyz/terms'

const openTxSimulationLearnMoreUrl = () =>
  openTab(TX_SIMULATION_LEARN_MORE_LINK)

export const EnableTransactionSimulations: React.FC = () => {
  // mutations
  const [optInOrOut] = useSetIsTxSimulationOptInStatusMutation()

  return (
    <>
      <Title>{getLocale('qoraiWalletEnableTransactionSimulation')}</Title>
      <CardContent>
        <Column>
          <Row
            width='100%'
            alignItems='center'
            justifyContent='center'
            gap={'4px'}
            padding={'55px 0px'}
          >
            <IconContainer>
              <Icon name={'product-qorai-wallet'} />
            </IconContainer>
            <DashedHorizontalLine />
            <IconContainer iconColor={errorIconColor}>
              <Icon name={'warning-triangle-outline'} />
            </IconContainer>
          </Row>

          <div>
            <HeadingText>
              {getLocale('qoraiWalletTransactionSimulationFeatureDescription')}
            </HeadingText>

            <BulletPoints>
              <li key={'estimate'}>
                {getLocale('qoraiWalletTransactionSimulationSeeEstimates')}
              </li>
              <li key={'detect'}>
                {getLocale('qoraiWalletTransactionSimulationDetectMalicious')}
              </li>
              <li key={'phishing'}>
                {getLocale('qoraiWalletTransactionSimulationDetectPhishing')}
                {
                  //
                  ' '
                }
                <a
                  href='#'
                  onClick={openTxSimulationLearnMoreUrl}
                >
                  {getLocale('qoraiWalletLearnMore')}
                </a>
              </li>
            </BulletPoints>

            <VerticalDivider margin='32px 0px' />

            <TermsText>
              <span>
                {formatLocale('qoraiWalletTransactionSimulationTerms', {
                  $1: (content) => <strong>{content}</strong>,
                  $2: (content) => (
                    <a
                      href='#'
                      onClick={() => openTab(BLOWFISH_TERMS_URL)}
                    >
                      {content}
                    </a>
                  ),
                  $3: (content) => (
                    <a
                      href='#'
                      onClick={() => openTab(BLOWFISH_PRIVACY_POLICY_URL)}
                    >
                      {content}
                    </a>
                  ),
                })}
              </span>
            </TermsText>
          </div>

          <OptionsRow>
            <QoraSquaredButton
              kind='outline'
              onClick={async () => {
                await optInOrOut(
                  QoraiWallet.BlowfishOptInStatus.kDenied,
                ).unwrap()
              }}
            >
              {getLocale('qoraiWalletButtonNoThanks')}
            </QoraSquaredButton>
            <QoraSquaredButton
              kind='filled'
              onClick={async () => {
                await optInOrOut(
                  QoraiWallet.BlowfishOptInStatus.kAllowed,
                ).unwrap()
              }}
            >
              {getLocale('qoraiWalletButtonEnable')}
            </QoraSquaredButton>
          </OptionsRow>
        </Column>
      </CardContent>
    </>
  )
}

export const LoadingSimulation: React.FC = () => {
  return <LoadingPanel message={getLocale('qoraiWalletScanningTransaction')} />
}
