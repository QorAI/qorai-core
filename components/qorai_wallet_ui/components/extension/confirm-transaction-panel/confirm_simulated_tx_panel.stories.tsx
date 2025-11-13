// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

// types
import { QoraiWallet } from '../../../constants/types'

// utils
import {
  deserializeTransaction, //
} from '../../../utils/model-serialization-utils'
import { findAccountByAccountId } from '../../../utils/account-utils'
import {
  accountInfoEntityAdaptor, //
} from '../../../common/slices/entities/account-info.entity'

// components
import {
  WalletPanelStory, //
} from '../../../stories/wrappers/wallet-panel-story-wrapper'
import { PanelWrapper } from '../../../panel/style'
import { LongWrapper } from '../../../stories/style'
import { ConfirmSimulatedTransactionPanel } from './confirm_simulated_tx_panel'

// mocks
import {
  mockERC721ApproveForAllSim,
  mockEvmSimulatedERC20Approval,
  mockEvmSimulatedResponse,
  mockReceiveSolSimulation,
  mockSendSolNftEvent,
  mockSimulatedBuyERC1155Token,
  mockSimulatedBuyNFTWithETH,
  mockSimulatedERC721Approve,
  mockSimulatedSwapETHForDAI,
  mockSolStakingChangeSimulation,
  mockSvmSimulationResult,
} from '../../../common/constants/mocks'
import {
  mockSolanaTransactionInfoAccount,
  mockSvmTxInfos,
  mockTransactionInfo, //
} from '../../../stories/mock-data/mock-transaction-info'

const _mockEvmAccountInfos: QoraiWallet.AccountInfo[] = [
  {
    accountId: mockTransactionInfo.fromAccountId,
    address: mockTransactionInfo.fromAccountId.address,
    hardware: undefined,
    name: 'EVM Account 1',
  },
]

const mockEvmTxInfos: QoraiWallet.TransactionInfo[] = [
  deserializeTransaction({
    ...mockTransactionInfo,
    fromAccountId: mockTransactionInfo.fromAccountId,
    txStatus: QoraiWallet.TransactionStatus.Unapproved,
  }),
  deserializeTransaction({
    ...mockTransactionInfo,
    fromAccountId: mockTransactionInfo.fromAccountId,
    txStatus: QoraiWallet.TransactionStatus.Unapproved,
  }),
]

const evmSimulationResponse: QoraiWallet.EVMSimulationResponse = {
  action: QoraiWallet.BlowfishSuggestedAction.kBlock,
  warnings: [
    {
      severity: QoraiWallet.BlowfishWarningSeverity.kCritical,
      kind: QoraiWallet.BlowfishWarningKind.kKnownMalicious,
      message: 'Unsafe to sign with high risk of losing funds.',
    },
    {
      severity: QoraiWallet.BlowfishWarningSeverity.kCritical,
      kind: QoraiWallet.BlowfishWarningKind.kKnownMalicious,
      message:
        'Gives permission for someone else to transfer'
        + ' many tokens on your behalf.',
    },
    {
      severity: QoraiWallet.BlowfishWarningSeverity.kCritical,
      kind: QoraiWallet.BlowfishWarningKind.kKnownMalicious,
      message: 'YOUR ACCOUNT WILL BE DRAINED!',
    },
    {
      severity: QoraiWallet.BlowfishWarningSeverity.kCritical,
      kind: QoraiWallet.BlowfishWarningKind.kKnownMalicious,
      message: 'A HORRIBLE EVENT WILL TAKE PLACE IF YOU SIGN THIS',
    },
    {
      severity: QoraiWallet.BlowfishWarningSeverity.kCritical,
      kind: QoraiWallet.BlowfishWarningKind.kKnownMalicious,
      message: 'ANOTHER HORRIBLE EVENT WILL TAKE PLACE IF YOU SIGN THIS',
    },
    {
      severity: QoraiWallet.BlowfishWarningSeverity.kCritical,
      kind: QoraiWallet.BlowfishWarningKind.kKnownMalicious,
      message: 'YET ANOTHER HORRIBLE EVENT WILL TAKE PLACE IF YOU SIGN THIS',
    },
    {
      severity: QoraiWallet.BlowfishWarningSeverity.kCritical,
      kind: QoraiWallet.BlowfishWarningKind.kKnownMalicious,
      message: 'VERY DANGEROUS',
    },
    {
      severity: QoraiWallet.BlowfishWarningSeverity.kCritical,
      kind: QoraiWallet.BlowfishWarningKind.kKnownMalicious,
      message: 'VERY DANGEROUS!!!',
    },
    {
      severity: QoraiWallet.BlowfishWarningSeverity.kCritical,
      kind: QoraiWallet.BlowfishWarningKind.kKnownMalicious,
      message: 'VERY DANGEROUS!!!!!!!!',
    },
  ],
  error: mockSimulatedSwapETHForDAI.error,
  expectedStateChanges: [
    ...mockSimulatedSwapETHForDAI.expectedStateChanges,
    ...mockSimulatedBuyERC1155Token.expectedStateChanges,
    ...mockSimulatedBuyNFTWithETH.expectedStateChanges,
    ...mockEvmSimulatedERC20Approval.expectedStateChanges,
    ...mockSimulatedERC721Approve.expectedStateChanges,
    ...mockERC721ApproveForAllSim.expectedStateChanges,
    ...mockERC721ApproveForAllSim.expectedStateChanges,
  ],
}

const mockAccountsRegistry = accountInfoEntityAdaptor.addMany(
  accountInfoEntityAdaptor.getInitialState(),
  _mockEvmAccountInfos.concat([mockSolanaTransactionInfoAccount]),
)

const svmSimulationResponse: QoraiWallet.SolanaSimulationResponse = {
  ...mockReceiveSolSimulation,
  action: QoraiWallet.BlowfishSuggestedAction.kBlock,
  warnings: [
    {
      severity: QoraiWallet.BlowfishWarningSeverity.kCritical,
      kind: QoraiWallet.BlowfishWarningKind.kKnownMalicious,
      message: 'Unsafe to sign with high risk of losing funds.',
    },
  ],
  error: mockReceiveSolSimulation.error,
  expectedStateChanges: mockReceiveSolSimulation.expectedStateChanges
    .concat(mockSendSolNftEvent)
    .concat(mockSolStakingChangeSimulation.expectedStateChanges[0]),
}
export const _ConfirmSimulatedEvmTransactionPanel = {
  render: () => {
    return (
      <WalletPanelStory
        walletStateOverride={{
          hasInitialized: true,
          isWalletCreated: true,
        }}
        panelStateOverride={{
          hasInitialized: true,
        }}
        uiStateOverride={{
          selectedPendingTransactionId: mockEvmTxInfos[0].id,
        }}
        walletApiDataOverrides={{
          accountInfos: _mockEvmAccountInfos,
          evmSimulationResponse: evmSimulationResponse,
          selectedAccountId: findAccountByAccountId(
            mockEvmTxInfos[0].fromAccountId,
            mockAccountsRegistry,
          )?.accountId,
          transactionInfos: mockEvmTxInfos,
        }}
      >
        <PanelWrapper isLonger>
          <LongWrapper padding='0px'>
            <ConfirmSimulatedTransactionPanel
              simulationType='EVM'
              txSimulation={mockEvmSimulatedResponse}
            />
          </LongWrapper>
        </PanelWrapper>
      </WalletPanelStory>
    )
  },
}

export const _ConfirmSimulatedSvmTransactionPanel = {
  render: () => {
    return (
      <WalletPanelStory
        walletStateOverride={{
          hasInitialized: true,
          isWalletCreated: true,
        }}
        panelStateOverride={{
          hasInitialized: true,
        }}
        uiStateOverride={{
          selectedPendingTransactionId: mockSvmTxInfos[0].id,
        }}
        walletApiDataOverrides={{
          accountInfos: [mockSolanaTransactionInfoAccount],
          svmSimulationResponse: svmSimulationResponse,
          selectedAccountId: findAccountByAccountId(
            mockSvmTxInfos[0].fromAccountId,
            mockAccountsRegistry,
          )?.accountId,
          transactionInfos: mockSvmTxInfos,
        }}
      >
        <ConfirmSimulatedTransactionPanel
          simulationType='SVM'
          txSimulation={mockSvmSimulationResult}
        />
      </WalletPanelStory>
    )
  },
}

export default {
  title: 'Wallet/Panel/Panels/Transaction Simulations',
}
