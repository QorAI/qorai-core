// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'
import Icon from '@qorai/qora/react/icon'

// Types
import { QoraiWallet } from '../../../constants/types'

// Utils
import {
  reduceAccountDisplayName, //
} from '../../../utils/reduce-account-name'

// Options
import {
  AllAccountsOption, //
} from '../../../options/account-filter-options'

// Components
import {
  CreateAccountIcon, //
} from '../create-account-icon/create-account-icon'

// Styled Components
import { DropdownFilter, DropdownOption } from './shared_dropdown.styles'
import { Row } from '../style'

interface Props {
  accounts: QoraiWallet.AccountInfo[]
  selectedAccount: QoraiWallet.AccountInfo
  showAllAccountsOption?: boolean
  onSelectAccount: (uniqueKey: string) => void
  checkIsAccountOptionDisabled?: (account: QoraiWallet.AccountInfo) => boolean
}

export const AccountsDropdown = (props: Props) => {
  const {
    accounts,
    selectedAccount,
    showAllAccountsOption,
    onSelectAccount,
    checkIsAccountOptionDisabled,
  } = props

  return (
    <DropdownFilter
      onChange={(e) => onSelectAccount(e.value ?? '')}
      value={selectedAccount.accountId.uniqueKey}
    >
      <Row
        slot='value'
        justifyContent='flex-start'
      >
        {selectedAccount.accountId.uniqueKey
          !== AllAccountsOption.accountId.uniqueKey && (
          <CreateAccountIcon
            size='tiny'
            account={selectedAccount}
            marginRight={8}
          />
        )}
        {selectedAccount.accountId.uniqueKey
        === AllAccountsOption.accountId.uniqueKey
          ? selectedAccount.name
          : reduceAccountDisplayName(selectedAccount.name, 12)}
      </Row>
      {showAllAccountsOption && (
        <qora-option value={AllAccountsOption.accountId.uniqueKey}>
          <DropdownOption
            justifyContent='space-between'
            isDisabled={false}
          >
            {AllAccountsOption.name}
            {selectedAccount.accountId.uniqueKey
              === AllAccountsOption.accountId.uniqueKey && (
              <Icon name='check-normal' />
            )}
          </DropdownOption>
        </qora-option>
      )}
      {accounts.map((account) => (
        <qora-option
          value={account.accountId.uniqueKey}
          key={account.accountId.uniqueKey}
        >
          <DropdownOption
            justifyContent='space-between'
            isDisabled={
              checkIsAccountOptionDisabled
                ? checkIsAccountOptionDisabled(account)
                : false
            }
          >
            <Row width='unset'>
              {account.accountId.uniqueKey
                !== AllAccountsOption.accountId.uniqueKey && (
                <CreateAccountIcon
                  size='tiny'
                  account={account}
                  marginRight={8}
                />
              )}
              {account.name}
            </Row>
            {selectedAccount.accountId.uniqueKey
              === account.accountId.uniqueKey && <Icon name='check-normal' />}
          </DropdownOption>
        </qora-option>
      ))}
    </DropdownFilter>
  )
}
