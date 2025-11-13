// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { useHistory } from 'react-router'
import { useDispatch, useSelector } from 'react-redux'

// redux
import { WalletPageActions } from '../../../actions'
import { PageSelectors } from '../../../selectors'

// utils
import { getLocale } from '../../../../../common/locale'
import {
  useReportOnboardingActionMutation, //
} from '../../../../common/slices/api.slice'

// components
import { WelcomeAction } from '../components/welcome_action/welcome_action'

// routes
import { QoraiWallet, WalletRoutes } from '../../../../constants/types'

// styles
import * as qora from '@qorai/qora/tokens/css/variables'
import { Row, VerticalSpace } from '../../../../components/shared/style'
import {
  QoraiIcon,
  Content,
  WelcomePageBackground,
  WelcomePageWrapper,
  Title,
  Heading,
  ActionsContainer,
  Footer,
  SubHeading,
} from './onboarding-welcome.style'

const walletIcons = [
  'qorai-icon-release-color',
  'phantom-color',
  'metamask-color',
  'coinbase-color',
  'trezor-color',
  'wallet-ledger',
]

export const OnboardingWelcome = () => {
  // routing
  const history = useHistory()

  // redux
  const dispatch = useDispatch()
  const setupStillInProgress = useSelector(PageSelectors.setupStillInProgress)

  // mutations
  const [report] = useReportOnboardingActionMutation()

  // effects
  React.useEffect(() => {
    // start wallet setup
    if (!setupStillInProgress) {
      report(QoraiWallet.OnboardingAction.Shown)
      dispatch(WalletPageActions.walletSetupComplete(false))
    }
  }, [setupStillInProgress, report, dispatch])

  return (
    <>
      <WelcomePageBackground />
      <WelcomePageWrapper>
        <Content>
          <Row
            gap='10px'
            justifyContent='flex-start'
            marginBottom={qora.spacing['5Xl']}
          >
            <QoraiIcon />
            <Title>{getLocale('qoraiWalletTitle')}</Title>
          </Row>
          <Heading>{getLocale('qoraiWalletWelcomeTitle')}</Heading>
          <SubHeading>{getLocale('qoraiWalletWelcomeDescription')}</SubHeading>

          <ActionsContainer>
            <WelcomeAction
              title={getLocale('qoraiWalletWelcomeNewWalletTitle')}
              description={getLocale('qoraiWalletWelcomeNewWalletDescription')}
              iconName='plus-add'
              onSelect={() =>
                history.push(WalletRoutes.OnboardingNewWalletTerms)
              }
            />

            <WelcomeAction
              title={getLocale('qoraiWalletWelcomeImportWalletTitle')}
              description={getLocale(
                'qoraiWalletWelcomeImportWalletDescription',
              )}
              iconName='import-arrow'
              walletIcons={walletIcons}
              onSelect={() =>
                history.push(WalletRoutes.OnboardingImportSelectWalletType)
              }
            />
          </ActionsContainer>
          <VerticalSpace space='96px' />
          <Footer>{getLocale('qoraiWalletCopyright')}</Footer>
        </Content>
      </WelcomePageWrapper>
    </>
  )
}
