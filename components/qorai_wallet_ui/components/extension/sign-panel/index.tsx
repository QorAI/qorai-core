// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'
import { skipToken } from '@reduxjs/toolkit/query/react'

// Hooks
import { useAccountOrb } from '../../../common/hooks/use-orb'

// Queries
import { useAccountQuery } from '../../../common/slices/api.slice.extra'

// Types
import { QoraiWallet, SignDataSteps } from '../../../constants/types'

// Utils
import { getLocale } from '../../../../common/locale'
import { unicodeEscape, hasUnicode } from '../../../utils/string-utils'
import {
  useGetIsTxSimulationOptInStatusQuery,
  useGetNetworkQuery,
  useProcessSignMessageRequestMutation,
  useSignMessageHardwareMutation,
} from '../../../common/slices/api.slice'
import { isHardwareAccount } from '../../../utils/account-utils'

// Components
import { NavButton } from '../buttons/nav-button/index'
import { PanelTab } from '../panel-tab/index'
import { CreateSiteOrigin } from '../../shared/create-site-origin/index'
import { SignInWithEthereum } from './sign_in_with_ethereum'
import { SignCowSwapOrder } from './cow_swap_order'
import {
  EthSignTypedData, //
} from './common/eth_sign_typed_data'
import {
  EvmMessageSimulationNotSupportedSheet, //
} from '../evm_message_simulation_not_supported_sheet/evm_message_simulation_not_supported_sheet'

// Styled Components
import {
  StyledWrapper,
  AccountCircle,
  AccountNameText,
  TopRow,
  NetworkText,
  PanelTitle,
  MessageBox,
  MessageText,
  SignPanelButtonRow,
  WarningTitleRow,
} from './style'

import {
  QueueStepRow,
  QueueStepButton,
  QueueStepText,
} from '../confirm-transaction-panel/common/style'

import {
  TabRow,
  WarningBox,
  WarningTitle,
  WarningText,
  LearnMoreButton,
  URLText,
  WarningIcon,
} from '../shared-panel-styles'

interface Props {
  signMessageData: QoraiWallet.SignMessageRequest[]
  showWarning: boolean
}

// TODO: fix broken article link
// https://github.com/qorai/qorai-browser/issues/39708
const onClickLearnMore = () => {
  chrome.tabs.create(
    {
      url: 'https://support.qorai.app/hc/en-us/articles/4409513799693',
    },
    () => {
      if (chrome.runtime.lastError) {
        console.error('tabs.create failed: ' + chrome.runtime.lastError.message)
      }
    },
  )
}

export const SignPanel = (props: Props) => {
  const { signMessageData, showWarning } = props

  // queries
  const { data: network } = useGetNetworkQuery(
    signMessageData[0]
      ? {
          chainId: signMessageData[0].chainId,
          coin: signMessageData[0].coin,
        }
      : skipToken,
  )

  const { data: simulationOptInStatus } = useGetIsTxSimulationOptInStatusQuery()
  const isSimulationPermitted =
    simulationOptInStatus === QoraiWallet.BlowfishOptInStatus.kAllowed

  // mutations
  const [processSignMessageRequest] = useProcessSignMessageRequestMutation()
  const [signMessageHardware] = useSignMessageHardwareMutation()

  // state
  const [signStep, setSignStep] = React.useState<SignDataSteps>(
    SignDataSteps.SignData,
  )
  const [selectedQueueData, setSelectedQueueData] =
    React.useState<QoraiWallet.SignMessageRequest>(signMessageData[0])
  const [renderUnicode, setRenderUnicode] = React.useState<boolean>(true)

  const { account } = useAccountQuery(selectedQueueData?.accountId)
  const ethStandardSignData = selectedQueueData.signData.ethStandardSignData
  const ethSignTypedData = selectedQueueData.signData.ethSignTypedData
  const ethSIWETypedData = selectedQueueData.signData.ethSiweData
  const solanaSignTypedData = selectedQueueData.signData.solanaSignData
  const cardanoSignTypedData = selectedQueueData.signData.cardanoSignData

  // methods
  const onCancel = async () => {
    await processSignMessageRequest({
      approved: false,
      id: signMessageData[0].id,
    }).unwrap()
  }

  // custom hooks
  const orb = useAccountOrb(account)

  // memos
  const signMessageQueueInfo = React.useMemo(() => {
    return {
      queueLength: signMessageData.length,
      queueNumber:
        signMessageData.findIndex((data) => data.id === selectedQueueData.id)
        + 1,
    }
  }, [signMessageData, selectedQueueData])

  const isDisabled = React.useMemo(
    (): boolean =>
      signMessageData.findIndex((data) => data.id === selectedQueueData.id)
      !== 0,
    [signMessageData, selectedQueueData],
  )

  // methods
  const onContinueSigning = () => {
    setSignStep(SignDataSteps.SignData)
  }

  const onQueueNextSignMessage = () => {
    if (signMessageQueueInfo.queueNumber === signMessageQueueInfo.queueLength) {
      setSelectedQueueData(signMessageData[0])
      return
    }
    setSelectedQueueData(signMessageData[signMessageQueueInfo.queueNumber])
  }

  const onSign = async () => {
    if (!account) {
      return
    }

    if (isHardwareAccount(account.accountId)) {
      await signMessageHardware({
        account,
        request: signMessageData[0],
      }).unwrap()
    } else {
      await processSignMessageRequest({
        approved: true,
        id: signMessageData[0].id,
      }).unwrap()
    }
  }

  // effects
  React.useEffect(() => {
    setSelectedQueueData(signMessageData[0])
  }, [signMessageData])

  React.useEffect(() => {
    if (showWarning || ethSignTypedData?.primaryType === 'Permit') {
      setSignStep(SignDataSteps.SignRisk)
    }
  }, [showWarning, ethSignTypedData])

  if (ethSIWETypedData) {
    return (
      <SignInWithEthereum
        data={selectedQueueData}
        onCancel={onCancel}
        onSignIn={onSign}
      />
    )
  }

  if (selectedQueueData.signData.ethSignTypedData?.meta?.cowSwapOrder) {
    return (
      <SignCowSwapOrder
        data={selectedQueueData}
        onQueueNextSignMessage={onQueueNextSignMessage}
        queueNumber={signMessageQueueInfo.queueNumber}
        queueLength={signMessageQueueInfo.queueLength}
        onCancel={onCancel}
        onSignIn={onSign}
        isDisabled={isDisabled}
      />
    )
  }

  // render
  return (
    <StyledWrapper>
      <TopRow>
        <NetworkText>{network?.chainName ?? ''}</NetworkText>
        {signMessageQueueInfo.queueLength > 1 && (
          <QueueStepRow>
            <QueueStepText>
              {signMessageQueueInfo.queueNumber}{' '}
              {getLocale('qoraiWalletQueueOf')}{' '}
              {signMessageQueueInfo.queueLength}
            </QueueStepText>
            <QueueStepButton onClick={onQueueNextSignMessage}>
              {signMessageQueueInfo.queueNumber
              === signMessageQueueInfo.queueLength
                ? getLocale('qoraiWalletQueueFirst')
                : getLocale('qoraiWalletQueueNext')}
            </QueueStepButton>
          </QueueStepRow>
        )}
      </TopRow>
      <AccountCircle orb={orb} />
      <URLText>
        <CreateSiteOrigin
          originSpec={selectedQueueData.originInfo.originSpec}
          eTldPlusOne={selectedQueueData.originInfo.eTldPlusOne}
        />
      </URLText>
      <AccountNameText>{account?.name ?? ''}</AccountNameText>
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
              text={
                ethSignTypedData
                  ? getLocale('qoraiWalletDetails')
                  : getLocale('qoraiWalletSignTransactionMessageTitle')
              }
            />
          </TabRow>

          {hasUnicode(
            selectedQueueData.signData.ethStandardSignData?.message ?? '',
          ) && (
            <WarningBox warningType='warning'>
              <WarningTitleRow>
                <WarningIcon color={'warningIcon'} />
                <WarningTitle warningType='warning'>
                  {getLocale('qoraiWalletNonAsciiCharactersInMessageWarning')}
                </WarningTitle>
              </WarningTitleRow>
              <LearnMoreButton
                onClick={() => setRenderUnicode((prev) => !prev)}
              >
                {renderUnicode
                  ? getLocale('qoraiWalletViewDecodedMessage')
                  : getLocale('qoraiWalletViewEncodedMessage')}
              </LearnMoreButton>
            </WarningBox>
          )}

          <EthSignTypedData data={ethSignTypedData} />

          {ethStandardSignData && (
            <MessageBox>
              <MessageText>
                {!renderUnicode && hasUnicode(ethStandardSignData.message)
                  ? unicodeEscape(ethStandardSignData.message)
                  : ethStandardSignData.message}
              </MessageText>
            </MessageBox>
          )}

          {solanaSignTypedData && (
            <MessageBox>
              <MessageText>{solanaSignTypedData.message}</MessageText>
            </MessageBox>
          )}

          {cardanoSignTypedData && (
            <MessageBox>
              <MessageText>
                {!renderUnicode && hasUnicode(cardanoSignTypedData.message)
                  ? unicodeEscape(cardanoSignTypedData.message)
                  : cardanoSignTypedData.message}
              </MessageText>
            </MessageBox>
          )}
        </>
      )}

      {isSimulationPermitted && <EvmMessageSimulationNotSupportedSheet />}

      <SignPanelButtonRow>
        <NavButton
          buttonType='secondary'
          text={getLocale('qoraiWalletButtonCancel')}
          onSubmit={onCancel}
          disabled={isDisabled}
        />
        <NavButton
          buttonType={signStep === SignDataSteps.SignData ? 'sign' : 'danger'}
          text={
            signStep === SignDataSteps.SignData
              ? getLocale('qoraiWalletSignTransactionButton')
              : getLocale('qoraiWalletButtonContinue')
          }
          onSubmit={
            signStep === SignDataSteps.SignRisk ? onContinueSigning : onSign
          }
          disabled={isDisabled}
        />
      </SignPanelButtonRow>
    </StyledWrapper>
  )
}

export default SignPanel
