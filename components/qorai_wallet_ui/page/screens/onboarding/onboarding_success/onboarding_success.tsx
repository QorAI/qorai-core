// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { useHistory } from 'react-router'
import { useDispatch } from 'react-redux'
import useMediaQuery from '$web-common/useMediaQuery'

// images
import CompleteGraphicLight from './images/complete_light.svg'
import CompleteGraphicDark from './images/complete_dark.svg'

// utils
import { getLocale } from '../../../../../common/locale'
import { WalletPageActions } from '../../../actions'
import {
  useDiscoverAssetsMutation,
  useReportOnboardingActionMutation, //
} from '../../../../common/slices/api.slice'

// constants
import { QoraiWallet, WalletRoutes } from '../../../../constants/types'

// components
import {
  OnboardingContentLayout, //
} from '../components/onboarding_content_layout/content_layout'

// styles
import { Column, VerticalSpace } from '../../../../components/shared/style'
import { IntroImg, Title, SubTitle } from './onboarding_success.style'
import { ContinueButton } from '../onboarding.style'

export const OnboardingSuccess = () => {
  // routing
  const history = useHistory()

  // redux
  const dispatch = useDispatch()

  // mutations
  const [report] = useReportOnboardingActionMutation()
  const [discoverAssets] = useDiscoverAssetsMutation()

  // methods
  const onComplete = React.useCallback(() => {
    dispatch(WalletPageActions.walletSetupComplete(true))
    history.push(WalletRoutes.PortfolioAssets)
  }, [dispatch, history])

  // effects
  React.useEffect(() => {
    // now that the token registry is populated, discover assets
    discoverAssets()

    report(QoraiWallet.OnboardingAction.Complete)
  }, [report, discoverAssets])

  // hooks
  const isDarkMode = useMediaQuery('(prefers-color-scheme: dark)')

  // render
  return (
    <OnboardingContentLayout
      showBackButton={false}
      padding='0 0 100px 0'
    >
      <IntroImg src={isDarkMode ? CompleteGraphicDark : CompleteGraphicLight} />
      <Title>{getLocale('qoraiWalletOnboardingSuccessTitle')}</Title>
      <VerticalSpace space='16px' />
      <SubTitle>
        {getLocale('qoraiWalletOnboardingSuccessDescription')}
      </SubTitle>
      <VerticalSpace space='100px' />
      <Column>
        <ContinueButton onClick={onComplete}>
          {getLocale('qoraiWalletOnboardingSuccessGoToPortfolio')}
        </ContinueButton>
      </Column>
    </OnboardingContentLayout>
  )
}
