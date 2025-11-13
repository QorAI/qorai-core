// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import Alert from '@qorai/qora/react/alert'
import * as qora from '@qorai/qora/tokens/css/variables'

// utils
import { getLocale } from '../../../../common/locale'

// components
import { BottomSheet } from '../../shared/bottom_sheet/bottom_sheet'

// styles
import { Column, QoraSquaredButton } from '../../shared/style'
import {
  AlertTextContainer,
  FullWidthChildrenColumn,
  CollapseTitle,
  TitleText,
  alertItemGap,
  CollapseTitleRow,
  CollapseIcon,
} from './evm_message_simulation_not_supported_sheet.styles'

export const EvmMessageSimulationNotSupportedSheet = () => {
  // state
  const [showSheet, setShowSheet] = React.useState(true)
  const [isMessageExpanded, setIsMessageExpanded] = React.useState(false)

  // render
  return (
    <BottomSheet isOpen={showSheet}>
      <TitleText>
        {getLocale('qoraiWalletEvmMessageScanningNotSupported')}
      </TitleText>
      <FullWidthChildrenColumn
        gap={'16px'}
        padding={'0px 16px 16px 16px'}
      >
        <Alert type='info'>
          <div slot='icon'></div>

          <Column
            justifyContent='center'
            alignItems='center'
            gap={alertItemGap}
          >
            <AlertTextContainer>
              {getLocale('qoraiWalletTransactionSimulationOptedInNotice')}
            </AlertTextContainer>

            <Column width='100%'>
              <CollapseTitleRow
                onClick={() => setIsMessageExpanded((prev) => !prev)}
              >
                <CollapseTitle>
                  {getLocale('qoraiWalletWhatIsMessageScanning')}
                  <CollapseIcon
                    name={isMessageExpanded ? 'carat-up' : 'carat-down'}
                  />
                </CollapseTitle>
              </CollapseTitleRow>

              {isMessageExpanded && (
                <Column gap={qora.spacing.m}>
                  <AlertTextContainer>
                    {getLocale(
                      'qoraiWalletEvmMessageScanningFeatureSafetyExplanation',
                    )}
                  </AlertTextContainer>
                  <AlertTextContainer>
                    {getLocale(
                      'qoraiWalletEvmMessageScanningFeatureAccuracyExplanation',
                    )}
                  </AlertTextContainer>
                </Column>
              )}
            </Column>
          </Column>
        </Alert>
        <QoraSquaredButton
          onClick={() => {
            setShowSheet(false)
          }}
        >
          {getLocale('qoraiWalletButtonClose')}
        </QoraSquaredButton>
      </FullWidthChildrenColumn>
    </BottomSheet>
  )
}

export default EvmMessageSimulationNotSupportedSheet
