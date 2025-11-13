// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

// Utils
import { getLocale } from '../../../../common/locale'

// Components
import { FullPanelPopup } from '../full_panel_popup/full_panel_popup'

// Styles
import { Column, QoraSquaredButton } from '../../shared/style'
import {
  LargeWarningCircleIcon,
  FullWidthChildrenColumn,
  WarningButtonText,
  CriticalWarningTitle,
  CriticalWarningDescription,
} from './critical-warning-popup.styles'

interface Props {
  onProceed: () => void
  onCancel: (() => void) | (() => Promise<void>)
}

export const CriticalWarningPopup: React.FC<Props> = ({
  onProceed,
  onCancel,
}) => {
  return (
    <FullPanelPopup kind='danger'>
      <Column
        fullHeight
        fullWidth
        gap={'8px'}
        justifyContent='space-between'
      >
        <Column
          fullWidth
          fullHeight
          gap={'8px'}
          padding={'40px'}
          alignSelf='center'
        >
          <LargeWarningCircleIcon />

          <CriticalWarningTitle>
            {getLocale('qoraiWalletRiskOfLossAction')}
          </CriticalWarningTitle>

          <CriticalWarningDescription>
            {getLocale('qoraiWalletUntrustedRequestWarning')}
          </CriticalWarningDescription>
        </Column>

        <FullWidthChildrenColumn
          fullWidth
          padding={'16px'}
          gap={'16px'}
        >
          <QoraSquaredButton
            kind='outline'
            onClick={onProceed}
          >
            <WarningButtonText>
              {getLocale('qoraiWalletProceedButton')}
            </WarningButtonText>
          </QoraSquaredButton>
          <QoraSquaredButton
            kind='filled'
            onClick={onCancel}
          >
            {getLocale('qoraiWalletButtonCancel')}
          </QoraSquaredButton>
        </FullWidthChildrenColumn>
      </Column>
    </FullPanelPopup>
  )
}
