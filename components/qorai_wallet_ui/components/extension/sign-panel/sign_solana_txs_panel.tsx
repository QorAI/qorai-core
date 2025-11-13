// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

// Types
import { QoraiWallet, SignDataSteps } from '../../../constants/types'

// Utils
import { getLocale } from '../../../../common/locale'
import {
  getSolanaTransactionInstructionParamsAndType as getTypedSolTxInstruction, //
} from '../../../utils/solana-instruction-utils'

// Hooks
import { useAccountOrb } from '../../../common/hooks/use-orb'
import {
  useProcessSignSolanaTransaction, //
} from '../../../common/hooks/use_sign_solana_tx_queue'

// Components
import NavButton from '../buttons/nav-button/index'
import PanelTab from '../panel-tab/index'
import CreateSiteOrigin from '../../shared/create-site-origin/index'
import SolanaTransactionInstruction from '../../shared/solana-transaction-instruction/solana-transaction-instruction'
import {
  TxWarningBanner, //
} from '../confirm-transaction-panel/common/tx_warnings'
import {
  TransactionSimulationNotSupportedSheet, //
} from '../transaction_simulation_not_supported_sheet/transaction_simulation_not_supported_sheet'
import { TransactionQueueSteps } from '../confirm-transaction-panel/common/queue'

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

import { DetailColumn } from '../transaction-box/style'
import { Tooltip } from '../../shared/tooltip/index'
import { Column } from '../../shared/style'

interface Props {
  selectedRequest: QoraiWallet.SignSolTransactionsRequest
  isSigningDisabled: boolean
  network: QoraiWallet.NetworkInfo
  queueNextSignTransaction: () => void
  signingAccount: QoraiWallet.AccountInfo
  queueLength: number
  queueNumber: number
  retrySimulation?: () => void
  showSimulationNotSupportedMessage?: boolean
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

export const SignSolanaTxsPanel = ({
  selectedRequest,
  isSigningDisabled,
  network,
  queueLength,
  queueNextSignTransaction,
  queueNumber,
  signingAccount,
  retrySimulation,
  showSimulationNotSupportedMessage,
}: Props) => {
  // custom hooks
  const orb = useAccountOrb(signingAccount)

  // state
  const [signStep, setSignStep] = React.useState<SignDataSteps>(
    SignDataSteps.SignRisk,
  )
  const [isSimulationWarningDismissed, setIsSimulationWarningDismissed] =
    React.useState(false)

  // methods
  const onAcceptSigningRisks = React.useCallback(() => {
    setSignStep(SignDataSteps.SignData)
  }, [])

  const { cancelSign: onCancelSign, sign: onSign } =
    useProcessSignSolanaTransaction({
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
              isSelected={true}
              text={getLocale('qoraiWalletDetails')}
            />
          </TabRow>
          <MessageBox>
            {selectedRequest.txDatas.map(({ instructions, txType }, i) => {
              return (
                <DetailColumn key={`${txType}-${i}`}>
                  {instructions?.map((instruction, index) => {
                    return (
                      <SolanaTransactionInstruction
                        key={index}
                        typedInstructionWithParams={getTypedSolTxInstruction(
                          instruction,
                        )}
                      />
                    )
                  })}
                </DetailColumn>
              )
            })}
          </MessageBox>
        </>
      )}
      <Column
        fullWidth
        gap={'8px'}
      >
        {retrySimulation && !isSimulationWarningDismissed && (
          <TxWarningBanner
            onDismiss={() => setIsSimulationWarningDismissed(true)}
            retrySimulation={retrySimulation}
          />
        )}
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
      {showSimulationNotSupportedMessage && (
        <TransactionSimulationNotSupportedSheet />
      )}
    </StyledWrapper>
  )
}

export default SignSolanaTxsPanel
