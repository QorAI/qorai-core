// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'

// types
import { QoraiWallet } from '../../../../../../constants/types'

// utils
import { getLocale } from '../../../../../../../common/locale'

// components
import withPlaceholderIcon from '../../../../../shared/create-placeholder-icon'

// styles
import PopupModal from '../../../../popup-modals'
import {
  StyledWrapper,
  hideTokenModalWidth,
  TokenSymbol,
  Instructions,
  ButtonRow,
  OkButton,
  CancelButton,
  IconWrapper,
} from './hide-token-modal-styles'
import { AssetIcon } from '../../style'

interface Props {
  selectedAsset: QoraiWallet.BlockchainToken
  onClose: () => void
  onHideAsset: () => void
}

const AssetIconWithPlaceholder = withPlaceholderIcon(AssetIcon, { size: 'big' })

export const HideTokenModal = (props: Props) => {
  const { selectedAsset, onClose, onHideAsset } = props

  return (
    <PopupModal
      onClose={onClose}
      title={getLocale('qoraiWalletHideTokenModalTitle')}
      width={hideTokenModalWidth}
    >
      <StyledWrapper>
        <IconWrapper>
          <AssetIconWithPlaceholder asset={selectedAsset} />
        </IconWrapper>
        <TokenSymbol>{selectedAsset.symbol}</TokenSymbol>
        <Instructions>
          {getLocale('qoraiWalletMakeTokenVisibleInstructions')}
        </Instructions>
        <ButtonRow>
          <CancelButton onClick={onClose}>
            {getLocale('qoraiWalletCancelHidingToken')}
          </CancelButton>
          <OkButton onClick={onHideAsset}>
            {getLocale('qoraiWalletConfirmHidingToken')}
          </OkButton>
        </ButtonRow>
      </StyledWrapper>
    </PopupModal>
  )
}
