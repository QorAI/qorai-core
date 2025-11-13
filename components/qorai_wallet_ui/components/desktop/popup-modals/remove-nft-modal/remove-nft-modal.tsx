// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'

// utils
import { getLocale } from '../../../../../common/locale'

// selectors
import { useSafeUISelector } from '../../../../common/hooks/use-safe-selector'
import { UISelectors } from '../../../../common/selectors'

// components
import { PopupModal } from '../index'

// styles
import {
  ButtonRow,
  Description,
  Header,
  StyledWrapper,
} from './remove-nft-modal.styles'
import { QoraSquaredButton } from '../../../shared/style'

interface Props {
  onConfirm: () => void
  onCancel: () => void
}

export const RemoveNftModal = ({ onConfirm, onCancel }: Props) => {
  const isPanel = useSafeUISelector(UISelectors.isPanel)

  return (
    <PopupModal
      title=''
      width='456px'
      hideHeader={isPanel}
      onClose={onCancel}
    >
      <StyledWrapper>
        <Header>{getLocale('qoraiWalletRemoveNftModalHeader')}</Header>
        <Description>
          {getLocale('qoraiWalletRemoveNftModalDescription')}
        </Description>
        <ButtonRow>
          <QoraSquaredButton
            onClick={onCancel}
            kind='outline'
          >
            {getLocale('qoraiWalletRemoveNftModalCancel')}
          </QoraSquaredButton>
          <QoraSquaredButton onClick={onConfirm}>
            {getLocale('qoraiWalletRemoveNftModalConfirm')}
          </QoraSquaredButton>
        </ButtonRow>
      </StyledWrapper>
    </PopupModal>
  )
}
