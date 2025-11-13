// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { skipToken } from '@reduxjs/toolkit/query'
import ProgressRingReact from '@qorai/qora/react/progressRing'
import Input, { InputEventDetail } from '@qorai/qora/react/input'
import SegmentedControlItem from '@qorai/qora/react/segmentedControlItem'

// redux
import { useDispatch, useSelector } from 'react-redux'

// actions
import {
  AccountsTabState,
  AccountsTabActions,
} from '../../../../page/reducers/accounts-tab-reducer'

// selectors
import { useSafeWalletSelector } from '../../../../common/hooks/use-safe-selector'
import { WalletSelectors } from '../../../../common/selectors'

// utils
import { getLocale, formatLocale } from '$web-common/locale'
import getAPIProxy from '../../../../common/async/bridge'

// constants
import { FILECOIN_FORMAT_DESCRIPTION_URL } from '../../../../common/constants/urls'

// options
import { AccountButtonOptions } from '../../../../options/account-list-button-options'

// types
import {
  QoraiWallet,
  zcashAddressOptionType,
} from '../../../../constants/types'

// components
import { CopyTooltip } from '../../../shared/copy-tooltip/copy-tooltip'
import PopupModal from '../index'
import PasswordInput from '../../../shared/password-input/index'
import {
  CreateAccountIcon, //
} from '../../../shared/create-account-icon/create-account-icon'

// hooks
import { useIsMounted } from '../../../../common/hooks/useIsMounted'
import { usePasswordAttempts } from '../../../../common/hooks/use-password-attempts'
import {
  useGetQrCodeImageQuery,
  useGetZCashAccountInfoQuery,
  useUpdateAccountNameMutation, //
} from '../../../../common/slices/api.slice'
import {
  useReceiveAddressQuery, //
} from '../../../../common/slices/api.slice.extra'

// style
import {
  StyledWrapper,
  QRCodeWrapper,
  AddressButton,
  ButtonRow,
  CopyIcon,
  PrivateKeyWrapper,
  PrivateKeyBubble,
  ButtonWrapper,
  ErrorText,
  Line,
  QRCodeImage,
  EditWrapper,
  Alert,
  ControlsWrapper,
  SegmentedControl,
} from './account-settings-modal.style'
import {
  Column,
  QoraSquaredButton,
  Text,
  VerticalSpacer,
} from '../../../shared/style'
import { Skeleton } from '../../../shared/loading-skeleton/styles'

const zcashAddressOptions: zcashAddressOptionType[] = [
  {
    addressType: 'unified',
    label: 'qoraiWalletUnified',
  },
  {
    addressType: 'shielded',
    label: 'qoraiWalletShielded',
  },
  {
    addressType: 'transparent',
    label: 'qoraiWalletTransparent',
  },
]
interface DepositModalProps {
  selectedAccount: QoraiWallet.AccountInfo
}

const filPrivateKeyFormatDescription = formatLocale(
  'qoraiWalletFilExportPrivateKeyFormatDescription',
  {
    $1: (content) => (
      <a
        target='_blank'
        href={FILECOIN_FORMAT_DESCRIPTION_URL}
        rel='noopener noreferrer'
      >
        {content}
      </a>
    ),
  },
)

export const DepositModal = ({ selectedAccount }: DepositModalProps) => {
  // state
  const [selectedZCashAddressOption, setSelectedZCashAddressOption] =
    React.useState<string>('unified')

  // redux
  const isZCashShieldedTransactionsEnabled = useSafeWalletSelector(
    WalletSelectors.isZCashShieldedTransactionsEnabled,
  )

  // queries and memos
  const { receiveAddress } = useReceiveAddressQuery(selectedAccount.accountId)
  const { data: zcashAccountInfo } = useGetZCashAccountInfoQuery(
    isZCashShieldedTransactionsEnabled
      && selectedAccount.accountId.coin === QoraiWallet.CoinType.ZEC
      ? selectedAccount.accountId
      : skipToken,
  )

  const displayAddress = React.useMemo(() => {
    if (
      isZCashShieldedTransactionsEnabled
      && selectedAccount.accountId.coin === QoraiWallet.CoinType.ZEC
      && zcashAccountInfo?.accountShieldBirthday
    ) {
      return selectedZCashAddressOption === 'unified'
        ? zcashAccountInfo.unifiedAddress
        : selectedZCashAddressOption === 'shielded'
          ? zcashAccountInfo.orchardAddress
          : zcashAccountInfo.nextTransparentReceiveAddress.addressString
    }
    return receiveAddress
  }, [
    isZCashShieldedTransactionsEnabled,
    selectedAccount,
    receiveAddress,
    zcashAccountInfo,
    selectedZCashAddressOption,
  ])

  const { data: qrCode, isFetching: isLoadingQrCode } = useGetQrCodeImageQuery(
    displayAddress || skipToken,
  )

  // render
  return (
    <Column padding='0px 16px'>
      <Column
        gap='8px'
        margin='0px 0px 24px 0px'
      >
        <CreateAccountIcon
          account={selectedAccount}
          size='huge'
        />
        <Text
          textSize='14px'
          textColor='primary'
        >
          {selectedAccount.name}
        </Text>
      </Column>

      {zcashAccountInfo && zcashAccountInfo.accountShieldBirthday && (
        <ControlsWrapper width='unset'>
          <SegmentedControl
            value={selectedZCashAddressOption}
            onChange={({ value }) => {
              if (value) {
                setSelectedZCashAddressOption(value)
              }
            }}
          >
            {zcashAddressOptions.map((option) => (
              <SegmentedControlItem
                key={option.addressType}
                value={option.addressType}
              >
                {getLocale(option.label)}
              </SegmentedControlItem>
            ))}
          </SegmentedControl>
        </ControlsWrapper>
      )}

      <QRCodeWrapper>
        {isLoadingQrCode || !displayAddress ? (
          <ProgressRingReact mode='indeterminate' />
        ) : (
          <QRCodeImage src={qrCode} />
        )}
      </QRCodeWrapper>

      {displayAddress ? (
        <CopyTooltip text={displayAddress}>
          <AddressButton>
            {displayAddress}
            <CopyIcon />
          </AddressButton>
        </CopyTooltip>
      ) : (
        <Skeleton
          height={'20px'}
          width={'300px'}
        />
      )}
      <VerticalSpacer space={20} />
    </Column>
  )
}

export const AccountSettingsModal = () => {
  // custom hooks
  const isMounted = useIsMounted()

  // redux
  const dispatch = useDispatch()

  // accounts tab state
  const selectedAccount = useSelector(
    ({ accountsTab }: { accountsTab: AccountsTabState }) =>
      accountsTab.selectedAccount,
  )
  const accountModalType = useSelector(
    ({ accountsTab }: { accountsTab: AccountsTabState }) =>
      accountsTab.accountModalType,
  )

  // state
  const [fullLengthAccountName, setFullLengthAccountName] =
    React.useState<string>(selectedAccount?.name ?? '')
  const accountName = fullLengthAccountName.substring(0, 30)
  const [updateError, setUpdateError] = React.useState<boolean>(false)
  const [password, setPassword] = React.useState<string>('')
  const [privateKey, setPrivateKey] = React.useState<string>('')
  const [isCorrectPassword, setIsCorrectPassword] =
    React.useState<boolean>(true)

  // mutations
  const [updateAccountName] = useUpdateAccountNameMutation()

  // custom hooks
  const { attemptPasswordEntry } = usePasswordAttempts()

  // methods
  const onViewPrivateKey = React.useCallback(
    async (accountId: QoraiWallet.AccountId) => {
      const { privateKey } =
        await getAPIProxy().keyringService.encodePrivateKeyForExport(
          accountId,
          password,
        )
      if (isMounted) {
        return setPrivateKey(privateKey || '')
      }
    },
    [password, isMounted],
  )

  const onDoneViewingPrivateKey = React.useCallback(() => {
    setPrivateKey('')
  }, [])

  const handleAccountNameChanged = (detail: InputEventDetail) => {
    setFullLengthAccountName(detail.value)
    setUpdateError(false)
  }

  const onClose = React.useCallback(() => {
    dispatch(AccountsTabActions.setShowAccountModal(false))
    dispatch(AccountsTabActions.setAccountModalType('deposit'))
  }, [dispatch])

  const onSubmitUpdateName = React.useCallback(async () => {
    if (!selectedAccount || !accountName) {
      return
    }

    try {
      await updateAccountName({
        accountId: selectedAccount.accountId,
        name: accountName,
      }).unwrap()
      onClose()
    } catch (error) {
      setUpdateError(true)
    }
  }, [selectedAccount, accountName, updateAccountName, onClose])

  const onShowPrivateKey = async () => {
    if (!password || !selectedAccount) {
      // require password to view key
      return
    }

    // entered password must be correct
    const isPasswordValid = await attemptPasswordEntry(password)

    if (!isPasswordValid) {
      setIsCorrectPassword(isPasswordValid) // set or clear error
      return // need valid password to continue
    }

    // clear entered password & error
    setPassword('')
    setIsCorrectPassword(true)

    onViewPrivateKey(selectedAccount.accountId)
  }

  const onHidePrivateKey = () => {
    onDoneViewingPrivateKey()
    setPrivateKey('')
  }

  const onClickClose = () => {
    onHidePrivateKey()
    setUpdateError(false)
    onClose()
  }

  const handleKeyDown = (detail: InputEventDetail) => {
    if ((detail.innerEvent as unknown as KeyboardEvent).key === 'Enter') {
      onSubmitUpdateName()
    }
  }

  const onPasswordChange = (value: string): void => {
    setIsCorrectPassword(true) // clear error
    setPassword(value)
  }

  const handlePasswordKeyDown = (
    event: React.KeyboardEvent<HTMLInputElement>,
  ) => {
    if (event.key === 'Enter') {
      onShowPrivateKey()
    }
  }

  // memos
  const modalTitle = React.useMemo((): string => {
    if (accountModalType) {
      return (
        AccountButtonOptions.find((option) => option.id === accountModalType)
          ?.name ?? ''
      )
    }
    return ''
  }, [accountModalType])

  // computed
  const showNameInputErrors = accountName === ''

  // render
  return (
    <PopupModal
      title={getLocale(modalTitle)}
      onClose={onClickClose}
    >
      <Line />
      <StyledWrapper>
        {selectedAccount && accountModalType === 'deposit' && (
          <DepositModal selectedAccount={selectedAccount} />
        )}
        {accountModalType === 'edit' && (
          <EditWrapper>
            <Input
              value={accountName}
              placeholder={getLocale('qoraiWalletAddAccountPlaceholder')}
              onInput={handleAccountNameChanged}
              onKeyDown={handleKeyDown}
              showErrors={showNameInputErrors}
              size='large'
              maxlength={QoraiWallet.ACCOUNT_NAME_MAX_CHARACTER_LENGTH}
            >
              {
                // Label
                getLocale('qoraiWalletAddAccountPlaceholder')
              }
            </Input>

            {updateError && (
              <ErrorText>
                {getLocale('qoraiWalletAccountSettingsUpdateError')}
              </ErrorText>
            )}

            <ButtonRow>
              <QoraSquaredButton
                onClick={onSubmitUpdateName}
                isDisabled={showNameInputErrors}
                kind='filled'
              >
                {getLocale('qoraiWalletAccountSettingsSave')}
              </QoraSquaredButton>
            </ButtonRow>
          </EditWrapper>
        )}
        {accountModalType === 'privateKey' && (
          <PrivateKeyWrapper>
            <Alert type='warning'>
              {getLocale('qoraiWalletAccountSettingsDisclaimer')}
            </Alert>
            {privateKey ? (
              <>
                {selectedAccount?.accountId.coin
                  === QoraiWallet.CoinType.FIL && (
                  <Alert type='warning'>{filPrivateKeyFormatDescription}</Alert>
                )}
                <CopyTooltip
                  text={privateKey}
                  isConfidential={true}
                >
                  <PrivateKeyBubble>{privateKey}</PrivateKeyBubble>
                </CopyTooltip>
              </>
            ) : (
              <PasswordInput
                placeholder={getLocale(
                  'qoraiWalletEnterYourQoraiWalletPassword',
                )}
                onChange={onPasswordChange}
                hasError={!!password && !isCorrectPassword}
                error={getLocale('qoraiWalletLockScreenError')}
                autoFocus={false}
                value={password}
                onKeyDown={handlePasswordKeyDown}
              />
            )}
            <ButtonWrapper>
              <QoraSquaredButton
                onClick={!privateKey ? onShowPrivateKey : onHidePrivateKey}
                kind='filled'
                isDisabled={
                  privateKey ? false : password ? !isCorrectPassword : true
                }
              >
                {getLocale(
                  !privateKey
                    ? 'qoraiWalletAccountSettingsShowKey'
                    : 'qoraiWalletAccountSettingsHideKey',
                )}
              </QoraSquaredButton>
            </ButtonWrapper>
          </PrivateKeyWrapper>
        )}
      </StyledWrapper>
    </PopupModal>
  )
}

export default AccountSettingsModal
