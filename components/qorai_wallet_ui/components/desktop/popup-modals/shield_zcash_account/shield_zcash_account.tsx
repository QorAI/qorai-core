// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'
import Icon from '@qorai/qora/react/icon'
import Input from '@qorai/qora/react/input'

// Slices
import {
  useGetChainTipStatusQuery,
  useMakeAccountShieldedMutation,
} from '../../../../common/slices/api.slice'

// Types
import { QoraiWallet } from '../../../../constants/types'

// Utils
import { getLocale } from '../../../../../common/locale'

// Components
import { PopupModal } from '../index'
import {
  CreateAccountIcon, //
} from '../../../shared/create-account-icon/create-account-icon'

// Styles
import {
  AccountRow,
  ShieldIconWrapper,
  ShieldIcon,
  AdvancedSettingsWrapper,
  AdvancedSettingsButton,
  CollapseIcon,
} from './shield_zcash_account.style'
import { Column, Text, Row, QoraSquaredButton } from '../../../shared/style'

const MIN_ACCOUNT_BIRTHDAY_BLOCK = 1687104

interface Props {
  account: QoraiWallet.AccountInfo
  onClose: () => void
}

export const ShieldZCashAccountModal = (props: Props) => {
  const { account, onClose } = props

  // State
  const [isShielding, setIsShielding] = React.useState<boolean>(false)
  const [showAdvanced, setShowAdvanced] = React.useState<boolean>(false)
  const [customBirthdayBlock, setCustomBirthdayBlock] =
    React.useState<string>('')

  // Queries
  const { data: chainTipStatus } = useGetChainTipStatusQuery(account.accountId)

  // Mutations
  const [shieldAccount] = useMakeAccountShieldedMutation()

  // Computed
  const accountBirthdayBlock =
    customBirthdayBlock !== '' ? Number(customBirthdayBlock) : 0
  const birthdayBlockIsToLow =
    customBirthdayBlock !== ''
    && accountBirthdayBlock < MIN_ACCOUNT_BIRTHDAY_BLOCK
  const birthdayBlockIsToHigh =
    customBirthdayBlock !== ''
    && chainTipStatus?.chainTip !== undefined
    && accountBirthdayBlock > chainTipStatus.chainTip
  const invalidBirthdayBlock = birthdayBlockIsToLow || birthdayBlockIsToHigh

  // Methods
  const onShieldAccount = React.useCallback(async () => {
    if (!account.accountId) {
      return
    }
    setIsShielding(true)
    await shieldAccount({
      accountId: account.accountId,
      accountBirthdayBlock: accountBirthdayBlock,
    })
    setIsShielding(false)
    onClose()
  }, [shieldAccount, account, onClose, accountBirthdayBlock])

  const onToggleShowAdvanced = () => {
    setShowAdvanced((prev) => !prev)
  }

  return (
    <PopupModal
      title={getLocale('qoraiWalletSwitchToShieldedAccount')}
      onClose={onClose}
      width='520px'
      headerPaddingHorizontal='32px'
      headerPaddingVertical='32px'
    >
      <Column
        gap='24px'
        padding='8px 32px'
      >
        <AccountRow
          width='unset'
          padding='8px 30px 8px 8px'
        >
          <ShieldIconWrapper>
            <ShieldIcon />
          </ShieldIconWrapper>
          <CreateAccountIcon
            account={account}
            size='huge'
            marginRight={16}
          />
          <Column alignItems='flex-start'>
            <Text
              textSize='14px'
              isBold={true}
              textColor='primary'
              textAlign='left'
            >
              {account.name}
            </Text>
            <Text
              textSize='12px'
              isBold={false}
              textColor='secondary'
              textAlign='left'
            >
              ZCash
            </Text>
          </Column>
        </AccountRow>
        <Text
          textSize='14px'
          isBold={false}
          textColor='primary'
          textAlign='left'
        >
          {getLocale('qoraiWalletAccountNotShieldedDescription')}
        </Text>
        <Text
          textSize='14px'
          isBold={true}
          textColor='primary'
          textAlign='left'
        >
          {getLocale('qoraiWalletAccountShieldedDescription')}
        </Text>
        <AdvancedSettingsWrapper fullWidth={true}>
          <AdvancedSettingsButton onClick={onToggleShowAdvanced}>
            <Row
              width='unset'
              gap='4px'
            >
              <Icon
                name='settings'
                slot='icon'
              />
              <Text
                textColor='primary'
                textSize='14px'
                isBold={true}
              >
                {getLocale('qoraiWalletAdvancedTransactionSettings')}
              </Text>
            </Row>
            <CollapseIcon
              isCollapsed={!showAdvanced}
              name='carat-down'
            />
          </AdvancedSettingsButton>
          {showAdvanced && (
            <Column fullWidth={true}>
              <Row
                padding='0px 8px 12px 28px'
                justifyContent='space-between'
              >
                <Text
                  textColor='primary'
                  textSize='14px'
                  isBold={false}
                >
                  {getLocale('qoraiWalletShieldedAccountBirthdayBlock')}
                </Text>
                <Input
                  size='small'
                  type='number'
                  value={customBirthdayBlock}
                  onInput={(e) => setCustomBirthdayBlock(e.value)}
                  showErrors={invalidBirthdayBlock}
                />
              </Row>
              {invalidBirthdayBlock && (
                <Row
                  padding='0px 8px 12px 28px'
                  justifyContent='flex-end'
                >
                  <Text
                    textColor='error'
                    textSize='12px'
                    isBold={false}
                  >
                    {birthdayBlockIsToLow
                      ? getLocale('qoraiWalletAccountBirthdayTooLow').replace(
                          '$1',
                          MIN_ACCOUNT_BIRTHDAY_BLOCK.toString(),
                        )
                      : getLocale('qoraiWalletAccountBirthdayTooHigh').replace(
                          '$1',
                          chainTipStatus?.chainTip.toString() ?? '',
                        )}
                  </Text>
                </Row>
              )}
            </Column>
          )}
        </AdvancedSettingsWrapper>
      </Column>
      <Row
        gap='16px'
        padding='32px'
      >
        <QoraSquaredButton
          onClick={onClose}
          kind='outline'
        >
          {getLocale('qoraiWalletButtonCancel')}
        </QoraSquaredButton>
        <QoraSquaredButton
          onClick={onShieldAccount}
          isDisabled={isShielding || invalidBirthdayBlock}
        >
          {getLocale('qoraiWalletShieldAccount')}
        </QoraSquaredButton>
      </Row>
    </PopupModal>
  )
}
