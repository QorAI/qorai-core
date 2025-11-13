// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import * as crypto from 'crypto'
import { assert, assertNotReached } from 'chrome://resources/js/assert.js'

// utils
import { getLocale } from '../../../../common/locale'
import { loadAccountsFromDevice } from '../../../common/async/hardware'

// components
import {
  AccountFromDeviceListItem,
  HardwareWalletAccountsList,
} from './accounts_list'
import {
  AuthorizeHardwareDeviceIFrame, //
} from '../../shared/authorize-hardware-device/authorize-hardware-device'
import {
  HardwareButton, //
} from '../popup-modals/add-account-modal/hardware-button/hardware_button'

// Styled Components
import {
  HardwareWalletGraphic,
  Instructions,
  Divider,
} from './hardware_wallet_connect.styles'
import { Column, VerticalSpace } from '../../shared/style'
import {
  ContinueButton, //
} from '../../../page/screens/onboarding/onboarding.style'

// Custom types
import {
  DerivationBatchSize,
  DerivationScheme,
  AllHardwareImportSchemes,
  HardwareImportScheme,
  DerivationSchemes,
  AccountFromDevice,
} from '../../../common/hardware/types'
import { QoraiWallet, CreateAccountOptionsType } from '../../../constants/types'
import { LedgerError } from '../../../common/hardware/ledgerjs/ledger-messages'

// hooks
import { useAccountsQuery } from '../../../common/slices/api.slice.extra'
import {
  useImportHardwareAccountsMutation, //
} from '../../../common/slices/api.slice'

export interface Props {
  selectedAccountType: CreateAccountOptionsType
  onSelectVendor?: (vendor: QoraiWallet.HardwareVendor) => void
  onSuccess: () => void
}

const vendorName = (vendor: QoraiWallet.HardwareVendor) => {
  switch (vendor) {
    case QoraiWallet.HardwareVendor.kLedger:
      return getLocale('qoraiWalletConnectHardwareLedger')
    case QoraiWallet.HardwareVendor.kTrezor:
      return getLocale('qoraiWalletConnectHardwareTrezor')
    default:
      assertNotReached(`Unknown vendor ${vendor}`)
  }
}

interface ErrorMessage {
  error: string
  userHint: string
}

const getErrorMessage = (
  error: undefined | string | LedgerError,
  accountTypeName: string,
): ErrorMessage => {
  if (typeof error === 'undefined') {
    return { error: getLocale('qoraiWalletUnknownInternalError'), userHint: '' }
  }

  if (typeof error === 'string') {
    return { error: error, userHint: '' }
  }

  // error must be of type LedgerError
  if (error.code && (error.code === 27404 || error.code === 21781)) {
    // Unknown Error
    return {
      error: getLocale('qoraiWalletConnectHardwareInfo2').replace(
        '$1',
        accountTypeName,
      ),
      userHint: '',
    }
  }

  const ledgerError: LedgerError = error

  if (!ledgerError.error) {
    return { error: getLocale('qoraiWalletUnknownInternalError'), userHint: '' }
  }

  if (
    ledgerError.code
    && (ledgerError.code === 27904 || ledgerError.code === 26368)
  ) {
    // INCORRECT_LENGTH or INS_NOT_SUPPORTED
    return {
      error: ledgerError.error,
      userHint: getLocale('qoraiWalletConnectHardwareWrongApplicationUserHint'),
    }
  }

  return { error: ledgerError.error, userHint: '' }
}

const defaultSchemeForCoinAndVendor = (
  type: CreateAccountOptionsType,
  vendor: QoraiWallet.HardwareVendor,
) => {
  const result = AllHardwareImportSchemes.find(
    (details) =>
      details.coin === type.coin
      && details.fixedNetwork === type.fixedNetwork
      && details.vendor === vendor,
  )

  assert(result, `Not supported ${type} and ${vendor}`)
  return result.derivationScheme
}

const getDefaultAccountName = (scheme: HardwareImportScheme, index: number) => {
  let schemeString
  switch (scheme.derivationScheme) {
    case DerivationSchemes.EthLedgerLegacy:
      schemeString = ' (Legacy)'
      break
    default:
      schemeString = ''
  }
  return index === 0
    ? `${vendorName(scheme.vendor)}${schemeString}`
    : `${vendorName(scheme.vendor)} ${index}${schemeString}`
}

const hardwareDeviceIdFromAddress = (address: string) => {
  return crypto.createHash('sha256').update(address).digest('hex')
}

const findHardwareImportScheme = (scheme: DerivationScheme) => {
  const result = AllHardwareImportSchemes.find(
    (d) => d.derivationScheme === scheme,
  )
  assert(result)
  return result
}

export const HardwareWalletConnect = ({
  selectedAccountType,
  onSuccess,
  onSelectVendor,
}: Props) => {
  // queries
  const { accounts: savedAccounts } = useAccountsQuery()

  // mutations
  const [importHardwareAccounts] = useImportHardwareAccountsMutation()

  // state
  const [selectedHardwareVendor, setSelectedHardwareVendor] =
    React.useState<QoraiWallet.HardwareVendor>()
  const [isLoadingAccounts, setIsLoadingAccounts] =
    React.useState<boolean>(false)
  const [accounts, setAccounts] = React.useState<AccountFromDeviceListItem[]>(
    [],
  )
  const [connectionError, setConnectionError] = React.useState<
    ErrorMessage | undefined
  >(undefined)
  const [currentDerivationScheme, setCurrentDerivationScheme] =
    React.useState<DerivationScheme>(DerivationSchemes.EthLedgerLive)
  const [showAccountsList, setShowAccountsList] = React.useState<boolean>(false)
  const [showAuthorizeDevice, setShowAuthorizeDevice] =
    React.useState<boolean>(false)
  const hideAuthorizeDevice = () => setShowAuthorizeDevice(false)
  const [totalNumberOfAccounts, setTotalNumberOfAccounts] = React.useState(0)

  const currentHardwareImportScheme: HardwareImportScheme =
    findHardwareImportScheme(currentDerivationScheme)

  const setHardwareImportScheme = React.useCallback(
    (scheme: DerivationScheme) => {
      if (currentDerivationScheme === scheme) {
        return
      }
      setAccounts([])
      if (findHardwareImportScheme(scheme).singleAccount) {
        setTotalNumberOfAccounts(1)
      } else {
        setTotalNumberOfAccounts(DerivationBatchSize)
      }
      setCurrentDerivationScheme(scheme)
    },
    [currentDerivationScheme],
  )

  const onAccountChecked = React.useCallback(
    (path: string, checked: boolean) => {
      setAccounts((prevAccounts) =>
        prevAccounts.map((acc) => {
          if (acc.derivationPath === path) {
            return { ...acc, shouldAddToWallet: checked }
          }
          return acc
        }),
      )
    },
    [],
  )

  const supportedSchemes = React.useMemo(() => {
    return AllHardwareImportSchemes.filter((scheme) => {
      return (
        scheme.coin === selectedAccountType.coin
        && scheme.fixedNetwork === selectedAccountType.fixedNetwork
        && scheme.vendor === selectedHardwareVendor
      )
    })
  }, [selectedHardwareVendor, selectedAccountType])

  const makeAccountListItems = React.useCallback(
    (accounts: AccountFromDevice[]): AccountFromDeviceListItem[] => {
      return accounts.map((acc) => {
        const alreadyInWallet = !!savedAccounts.find((a) => {
          return (
            a.accountId.kind === QoraiWallet.AccountKind.kHardware
            && a.address === acc.address
          )
        })
        return { ...acc, alreadyInWallet, shouldAddToWallet: false }
      })
    },
    [savedAccounts],
  )

  React.useEffect(() => {
    // Just return if there is nothing to load.
    const numberOfAccountsToLoad = totalNumberOfAccounts - accounts.length
    if (numberOfAccountsToLoad <= 0) {
      return
    }

    setIsLoadingAccounts(true)
    let ignore = false
    loadAccountsFromDevice({
      startIndex: accounts.length,
      count: numberOfAccountsToLoad,
      scheme: currentHardwareImportScheme,
      onAuthorized: hideAuthorizeDevice,
    }).then((result) => {
      if (ignore) {
        return
      }
      setIsLoadingAccounts(false)
      setShowAccountsList(result.success)

      if (result.success) {
        setAccounts((prev) =>
          prev.concat(makeAccountListItems(result.accounts ?? [])),
        )
        return
      }

      if (result.error === 'unauthorized') {
        setShowAuthorizeDevice(true)
      } else {
        setConnectionError(
          getErrorMessage(result.error, selectedAccountType.name),
        )
      }
    })
    return () => {
      ignore = true
    }
  }, [
    currentHardwareImportScheme,
    totalNumberOfAccounts,
    accounts.length,
    selectedAccountType.name,
    makeAccountListItems,
  ])

  const onAddAccounts = React.useCallback(async () => {
    if (accounts.length === 0) {
      return
    }
    const deviceId = hardwareDeviceIdFromAddress(accounts[0].address)
    const hwAccounts: QoraiWallet.HardwareWalletAccount[] = accounts
      .filter((account) => account.shouldAddToWallet)
      .map((account, index) => ({
        address: account.address,
        derivationPath: account.derivationPath,
        name: getDefaultAccountName(currentHardwareImportScheme, index),
        hardwareVendor: currentHardwareImportScheme.vendor,
        deviceId: deviceId,
        keyringId: currentHardwareImportScheme.keyringId,
      }))

    try {
      await importHardwareAccounts({
        coin: currentHardwareImportScheme.coin,
        accounts: hwAccounts,
      }).unwrap()
      onSuccess()
    } catch (error) {
      console.log(error)
    }
  }, [currentHardwareImportScheme, accounts, onSuccess, importHardwareAccounts])

  const selectVendor = React.useCallback(
    (vendor: QoraiWallet.HardwareVendor) => {
      setCurrentDerivationScheme(
        defaultSchemeForCoinAndVendor(selectedAccountType, vendor),
      )
      setSelectedHardwareVendor(vendor)
      onSelectVendor?.(vendor)
    },
    [onSelectVendor, selectedAccountType],
  )

  const onSelectLedger = React.useCallback(() => {
    if (selectedHardwareVendor !== QoraiWallet.HardwareVendor.kLedger) {
      setConnectionError(undefined)
    }

    selectVendor(QoraiWallet.HardwareVendor.kLedger)
  }, [selectedHardwareVendor, selectVendor])

  const onSelectTrezor = React.useCallback(() => {
    if (selectedHardwareVendor !== QoraiWallet.HardwareVendor.kTrezor) {
      setConnectionError(undefined)
    }

    selectVendor(QoraiWallet.HardwareVendor.kTrezor)
  }, [selectedHardwareVendor, selectVendor])

  const increaseNumberOfAccounts = React.useCallback(() => {
    if (isLoadingAccounts) {
      return
    }
    if (currentHardwareImportScheme.singleAccount) {
      setTotalNumberOfAccounts(1)
      return
    }
    setTotalNumberOfAccounts((curState) => curState + DerivationBatchSize)
  }, [currentHardwareImportScheme.singleAccount, isLoadingAccounts])

  const trezorEnabled = [QoraiWallet.CoinType.ETH].includes(
    selectedAccountType.coin,
  )

  // render
  if (!selectedHardwareVendor) {
    return (
      <>
        <HardwareButton
          title={getLocale('qoraiWalletConnectHardwareLedger')}
          description={getLocale(
            'qoraiWalletConnectHardwareDeviceDescription',
          ).replace('$1', getLocale('qoraiWalletConnectHardwareLedger'))}
          onClick={onSelectLedger}
        />
        {trezorEnabled && (
          <>
            <Divider />
            <HardwareButton
              title={getLocale('qoraiWalletConnectHardwareTrezor')}
              description={getLocale(
                'qoraiWalletConnectHardwareDeviceDescription',
              ).replace('$1', getLocale('qoraiWalletConnectHardwareTrezor'))}
              onClick={onSelectTrezor}
            />
          </>
        )}
      </>
    )
  }

  if (showAccountsList) {
    return (
      <HardwareWalletAccountsList
        currentHardwareImportScheme={currentHardwareImportScheme}
        supportedSchemes={supportedSchemes}
        setHardwareImportScheme={setHardwareImportScheme}
        accounts={accounts}
        onLoadMore={increaseNumberOfAccounts}
        onAccountChecked={onAccountChecked}
        onAddAccounts={onAddAccounts}
      />
    )
  }

  return (
    <Column>
      <HardwareWalletGraphic hardwareVendor={selectedHardwareVendor} />
      <VerticalSpace space='32px' />
      <Instructions mode={connectionError ? 'error' : 'info'}>
        {connectionError
          ? `${connectionError.error} ${connectionError?.userHint}`
          : getLocale('qoraiWalletConnectHardwareAuthorizationNeeded').replace(
              '$1',
              vendorName(selectedHardwareVendor),
            )}
      </Instructions>
      <VerticalSpace space='100px' />
      {showAuthorizeDevice ? (
        <AuthorizeHardwareDeviceIFrame coinType={selectedAccountType.coin} />
      ) : (
        <ContinueButton
          onClick={increaseNumberOfAccounts}
          isLoading={isLoadingAccounts}
        >
          <div slot='loading'>
            {getLocale('qoraiWalletConnectingHardwareWallet')}
          </div>
          {!isLoadingAccounts && getLocale('qoraiWalletAddAccountConnect')}
        </ContinueButton>
      )}
    </Column>
  )
}

export default HardwareWalletConnect
