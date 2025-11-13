// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

// Types
import { QoraiWallet, SignDataSteps } from '../../../constants/types'

// Utils
import { getLocale } from '../../../../common/locale'

// Hooks
import { useAccountOrb } from '../../../common/hooks/use-orb'
import {
  useProcessSignCardanoTransaction, //
} from '../../../common/hooks/use_sign_cardano_tx_queue'

// Components
import NavButton from '../buttons/nav-button/index'
import PanelTab from '../panel-tab/index'
import CreateSiteOrigin from '../../shared/create-site-origin/index'
import { TransactionQueueSteps } from '../confirm-transaction-panel/common/queue'
import {
  DetailColumn,
  DetailText,
  LabelText,
} from '../pending_transaction_details/pending_transaction_details.styles'
import DividerLine from '../divider'

// Styled Components
import {
  StyledWrapper,
  AccountCircle,
  AccountNameText,
  TopRow,
  NetworkText,
  PanelTitle,
  MessageBox,
  SignPanelButtonRow,
  WarningTitleRow,
  MessageHeaderSection,
} from './style'

import {
  TabRow,
  WarningBox,
  WarningTitle,
  WarningText,
  LearnMoreButton,
  URLText,
  WarningIcon,
} from '../shared-panel-styles'

import { Tooltip } from '../../shared/tooltip/index'
import { Column, VerticalDivider } from '../../shared/style'

interface Props {
  selectedRequest: QoraiWallet.SignCardanoTransactionRequest
  isSigningDisabled: boolean
  network: QoraiWallet.NetworkInfo
  queueNextSignTransaction: () => void
  signingAccount: QoraiWallet.AccountInfo
  queueLength: number
  queueNumber: number
}

// TODO: broken article link
// https://github.com/qorai/qorai-browser/issues/39708
const onClickLearnMore = () => {
  window.open(
    'https://support.qorai.app/hc/en-us/articles/4409513799693',
    '_blank',
    'noreferrer',
  )
}

type TabName = 'rawTransaction' | 'details'

export const SignCardanoTxPanel = ({
  selectedRequest,
  isSigningDisabled,
  network,
  queueLength,
  queueNextSignTransaction,
  queueNumber,
  signingAccount,
}: Props) => {
  // custom hooks
  const orb = useAccountOrb(signingAccount)

  // state
  const [signStep, setSignStep] = React.useState<SignDataSteps>(
    SignDataSteps.SignRisk,
  )
  const [selectedTab, setSelectedTab] = React.useState<TabName>('details')

  // methods
  const onAcceptSigningRisks = React.useCallback(() => {
    setSignStep(SignDataSteps.SignData)
  }, [])

  const onSelectTab = React.useCallback(
    (tab: TabName) => () => setSelectedTab(tab),
    [],
  )

  const { cancelSign: onCancelSign, sign: onSign } =
    useProcessSignCardanoTransaction({
      request: selectedRequest,
    })

  // render
  return (
    <StyledWrapper>
      <TopRow>
        <NetworkText> {network.chainName} </NetworkText>
        <TransactionQueueSteps
          queueNextTransaction={queueNextSignTransaction}
          transactionQueueNumber={queueNumber}
          transactionsQueueLength={queueLength}
        />
      </TopRow>
      <AccountCircle orb={orb} />
      <URLText>
        <CreateSiteOrigin
          originSpec={selectedRequest.originInfo.originSpec}
          eTldPlusOne={selectedRequest.originInfo.eTldPlusOne}
        />
      </URLText>
      <Tooltip
        text={signingAccount.address || ''}
        isAddress
      >
        <AccountNameText>{signingAccount?.name ?? ''}</AccountNameText>
      </Tooltip>
      <PanelTitle>{getLocale('qoraiWalletSignTransactionTitle')}</PanelTitle>
      {signStep === SignDataSteps.SignRisk && (
        <WarningBox warningType='danger'>
          <WarningTitleRow>
            <WarningIcon />
            <WarningTitle warningType='danger'>
              {getLocale('qoraiWalletSignWarningTitle')}
            </WarningTitle>
          </WarningTitleRow>
          <WarningText>{getLocale('qoraiWalletSignWarning')}</WarningText>
          <LearnMoreButton onClick={onClickLearnMore}>
            {getLocale('qoraiWalletAllowAddNetworkLearnMoreButton')}
          </LearnMoreButton>
        </WarningBox>
      )}
      {signStep === SignDataSteps.SignData && (
        <>
          <TabRow>
            <PanelTab
              isSelected={selectedTab === 'details'}
              onSubmit={onSelectTab('details')}
              text='Details'
            />
            <PanelTab
              isSelected={selectedTab === 'rawTransaction'}
              onSubmit={onSelectTab('rawTransaction')}
              text='Transaction'
            />
          </TabRow>
          {selectedTab === 'rawTransaction' ? (
            <MessageBox width='100%'>
              <DetailText>{`${selectedRequest.rawTxData}`}</DetailText>
            </MessageBox>
          ) : (
            <MessageBox width='100%'>
              <MessageHeaderSection>
                {getLocale('qoraiWalletInputs')}
              </MessageHeaderSection>
              {selectedRequest.inputs?.map((input, index) => {
                return (
                  <DetailColumn
                    gap='4px'
                    key={'input' + index}
                  >
                    <LabelText>{getLocale('qoraiWalletInput')}:</LabelText>
                    <DetailText>{`${input.outpointTxid}:${input.outpointIndex}`}</DetailText>
                    <LabelText>{getLocale('qoraiWalletValue')}:</LabelText>
                    <DetailText>{`${input.value ? input.value : 'N/A'}`}</DetailText>
                    <LabelText>{getLocale('qoraiWalletAddress')}:</LabelText>
                    <DetailText>{`${input.address ? input.address : 'N/A'}`}</DetailText>
                    <DividerLine />
                  </DetailColumn>
                )
              })}
              <VerticalDivider></VerticalDivider>
              <MessageHeaderSection>
                {getLocale('qoraiWalletOutputs')}
              </MessageHeaderSection>
              {selectedRequest.outputs?.map((output, index) => {
                return (
                  <DetailColumn
                    gap='4px'
                    key={'output-external' + index}
                  >
                    <LabelText>{getLocale('qoraiWalletAddress')}:</LabelText>
                    <DetailText>{`${output.address}`}</DetailText>
                    <LabelText>{getLocale('qoraiWalletValue')}:</LabelText>
                    <DetailText>{`${output.value}`}</DetailText>
                  </DetailColumn>
                )
              })}
            </MessageBox>
          )}
        </>
      )}
      <Column
        fullWidth
        gap={'8px'}
      >
        <SignPanelButtonRow>
          <NavButton
            buttonType='secondary'
            text={getLocale('qoraiWalletButtonCancel')}
            onSubmit={onCancelSign}
            disabled={isSigningDisabled}
          />
          <NavButton
            buttonType={signStep === SignDataSteps.SignData ? 'sign' : 'danger'}
            text={
              signStep === SignDataSteps.SignData
                ? getLocale('qoraiWalletSignTransactionButton')
                : getLocale('qoraiWalletButtonContinue')
            }
            onSubmit={
              signStep === SignDataSteps.SignRisk
                ? onAcceptSigningRisks
                : onSign
            }
            disabled={isSigningDisabled}
          />
        </SignPanelButtonRow>
      </Column>
    </StyledWrapper>
  )
}

export default SignCardanoTxPanel
