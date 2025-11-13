// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

// Types
import { QoraiWallet } from '../../../constants/types'

// Mocks
import {
  mockTransactionInfo, //
} from '../../../stories/mock-data/mock-transaction-info'
import { mockAccount } from '../../../common/constants/mocks'

// Components
import {
  WalletPanelStory, //
} from '../../../stories/wrappers/wallet-panel-story-wrapper'
import { LongWrapper } from '../../../stories/style'
import { PanelWrapper } from '../../../panel/style'
import { ConfirmSwapTransaction } from './swap'

// Utils
import {
  deserializeTransaction, //
} from '../../../utils/model-serialization-utils'

export const _ConfirmSwapTransaction = {
  render: () => {
    return (
      <WalletPanelStory
        walletStateOverride={{
          hasInitialized: true,
          isWalletCreated: true,
        }}
        uiStateOverride={{
          selectedPendingTransactionId: mockTransactionInfo.id,
        }}
        panelStateOverride={{
          hasInitialized: true,
        }}
        walletApiDataOverrides={{
          simulationOptInStatus: QoraiWallet.BlowfishOptInStatus.kAllowed,
          evmSimulationResponse: {
            error: {
              humanReadableError: 'Simulation failed',
              kind: QoraiWallet.BlowfishEVMErrorKind.kSimulationFailed,
            },
            expectedStateChanges: [],
            action: QoraiWallet.BlowfishSuggestedAction.kWarn,
            warnings: [],
          },
          transactionInfos: [
            deserializeTransaction({
              ...mockTransactionInfo,
              txStatus: QoraiWallet.TransactionStatus.Unapproved,
            }),
          ],
          accountInfos: [mockAccount],
        }}
      >
        <PanelWrapper isLonger={true}>
          <LongWrapper>
            <ConfirmSwapTransaction />
          </LongWrapper>
        </PanelWrapper>
      </WalletPanelStory>
    )
  },
}

export default {
  title: 'Wallet/Panel/Panels/Confirm Transaction',
  component: ConfirmSwapTransaction,
}
