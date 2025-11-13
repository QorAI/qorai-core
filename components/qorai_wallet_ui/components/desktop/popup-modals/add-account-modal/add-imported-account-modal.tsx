// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { assert, assertNotReached } from 'chrome://resources/js/assert.js'
import * as React from 'react'
import { useDispatch } from 'react-redux'
import { useHistory, useParams } from 'react-router'
import Input, { InputEventDetail } from '@qorai/qora/react/input'
import Dropdown from '@qorai/qora/react/dropdown'
import {
  SelectItemEventDetail, //
} from '@qorai/qora/types/src/components/menu/menu.svelte'

// utils
import { FILECOIN_FORMAT_DESCRIPTION_URL } from '../../../../common/constants/urls'
import { getLocale, formatLocale } from '$web-common/locale'
import { copyToClipboard } from '../../../../utils/copy-to-clipboard'

// options
import { CreateAccountOptions } from '../../../../options/create-account-options'

// types
import {
  QoraiWallet,
  CreateAccountOptionsType,
  WalletRoutes,
  DAppSupportedCoinTypes,
} from '../../../../constants/types'

// actions
import { PanelActions } from '../../../../panel/actions'

// components
import { DividerLine } from '../../../extension/divider/index'
import { PopupModal } from '../index'
import { SelectAccountType } from './select-account-type/select-account-type'

// style
import { QoraSquaredButton } from '../../../shared/style'
import {
  CreateAccountStyledWrapper,
  DisclaimerText,
  ErrorText,
  ImportButton,
  ImportRow,
  StyledWrapper,
  Alert,
} from './style'

// selectors
import { UISelectors, WalletSelectors } from '../../../../common/selectors'

// hooks
import {
  useSafeUISelector,
  useSafeWalletSelector,
} from '../../../../common/hooks/use-safe-selector'
import {
  useGetVisibleNetworksQuery,
  useImportEthAccountFromJsonMutation,
  useImportEthAccountMutation,
  useImportBtcAccountMutation,
  useImportFilAccountMutation,
  useImportSolAccountMutation,
} from '../../../../common/slices/api.slice'

interface Params {
  accountTypeName: string
}

const reduceFileName = (address: string) => {
  const firstHalf = address.slice(0, 4)
  const secondHalf = address.slice(-4)
  const reduced = firstHalf.concat('......', secondHalf)
  return reduced
}

const filPrivateKeyFormatDescription = formatLocale(
  'qoraiWalletFilImportPrivateKeyFormatDescription',
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

export const ImportAccountModal = () => {
  // refs
  const passwordInputRef = React.useRef<HTMLInputElement>(null)

  // routing
  const history = useHistory()
  const { accountTypeName } = useParams<Params>()

  // redux
  const dispatch = useDispatch()
  const isBitcoinImportEnabled = useSafeWalletSelector(
    WalletSelectors.isBitcoinImportEnabled,
  )

  // queries
  const { data: visibleNetworks = [] } = useGetVisibleNetworksQuery()

  // mutations
  const [importEthAccount] = useImportEthAccountMutation()
  const [importSolAccount] = useImportSolAccountMutation()
  const [importFilAccount] = useImportFilAccountMutation()
  const [importBtcAccount] = useImportBtcAccountMutation()
  const [importEthAccountFromJson] = useImportEthAccountFromJsonMutation()

  // memos
  const createAccountOptions = React.useMemo(() => {
    return CreateAccountOptions({
      visibleNetworks,
      isBitcoinEnabled: isBitcoinImportEnabled,
      isZCashEnabled: false, // No zcash imported accounts by now.
      isCardanoEnabled: false, // No cardano imported accounts by now.
      isPolkadotEnabled: false, // No polkadot imported accounts by now.
    })
  }, [visibleNetworks, isBitcoinImportEnabled])

  const selectedAccountType = React.useMemo(() => {
    return createAccountOptions.find((option) => {
      return option.name.toLowerCase() === accountTypeName?.toLowerCase()
    })
  }, [accountTypeName, createAccountOptions])

  const isPanel = useSafeUISelector(UISelectors.isPanel)

  // state
  const [hasImportError, setHasImportError] = React.useState(false)
  const [fullLengthAccountName, setFullLengthAccountName] =
    React.useState<string>('')
  const accountName = fullLengthAccountName.substring(0, 30)
  const [importOption, setImportOption] = React.useState<string>('key')
  const [privateKey, setPrivateKey] = React.useState<string>('')
  const [file, setFile] = React.useState<HTMLInputElement['files']>()
  const [password, setPassword] = React.useState<string>('')

  // computed
  const hasAccountNameError = accountName === ''
  const hasImportTypeError = importOption === 'key' ? !privateKey : !file
  const isDisabled = hasAccountNameError || hasImportTypeError
  const modalTitle = selectedAccountType
    ? getLocale('qoraiWalletCreateAccountImportAccount').replace(
        '$1',
        selectedAccountType.name,
      )
    : getLocale('qoraiWalletAddAccountImport')

  // methods
  const onClickClose = React.useCallback(() => {
    setHasImportError(false)
    history.push(WalletRoutes.Accounts)
  }, [history])

  const handleAccountNameChanged = React.useCallback(
    (detail: InputEventDetail) => {
      setFullLengthAccountName(detail.value)
      setHasImportError(false)
    },
    [],
  )

  const onChangeImportOption = React.useCallback(
    (detail: SelectItemEventDetail) => {
      setImportOption(detail.value!)
    },
    [],
  )

  const clearClipboard = React.useCallback(() => {
    copyToClipboard('')
  }, [])

  const handlePrivateKeyChanged = React.useCallback(
    (detail: InputEventDetail) => {
      clearClipboard()
      setPrivateKey(detail.value)
      setHasImportError(false)
    },
    [clearClipboard],
  )

  const onClickFileUpload = () => {
    // To prevent panel from being closed when file chooser is open
    if (isPanel) {
      dispatch(PanelActions.setCloseOnDeactivate(false))
      // For resume close on deactive when file chooser is close(select/cancel)
      window.addEventListener('focus', onFocusFileUpload)
    }
  }

  const onFocusFileUpload = () => {
    if (isPanel) {
      dispatch(PanelActions.setCloseOnDeactivate(true))
      window.removeEventListener('focus', onFocusFileUpload)
    }
  }

  const onFileUpload = React.useCallback(
    (file: React.ChangeEvent<HTMLInputElement>) => {
      if (file.target.files) {
        setFile(file.target.files)
        setHasImportError(false)
        passwordInputRef.current?.focus()
      }
    },
    [],
  )

  const handlePasswordChanged = React.useCallback(
    (detail: InputEventDetail) => {
      setPassword(detail.value)
      setHasImportError(false)
      clearClipboard()
    },
    [clearClipboard],
  )

  const onClickCreateAccount = React.useCallback(async () => {
    if (!selectedAccountType) {
      return
    }
    if (importOption === 'key') {
      const fixedNetwork = selectedAccountType.fixedNetwork
      try {
        if (selectedAccountType.coin === QoraiWallet.CoinType.FIL) {
          assert(
            fixedNetwork === QoraiWallet.FILECOIN_MAINNET
              || fixedNetwork === QoraiWallet.FILECOIN_TESTNET,
          )
          await importFilAccount({
            accountName,
            privateKey,
            network: fixedNetwork,
          })
        } else if (selectedAccountType.coin === QoraiWallet.CoinType.BTC) {
          assert(
            fixedNetwork === QoraiWallet.BITCOIN_MAINNET
              || fixedNetwork === QoraiWallet.BITCOIN_TESTNET,
          )
          await importBtcAccount({
            accountName,
            payload: privateKey,
            network: fixedNetwork,
          })
        } else if (selectedAccountType.coin === QoraiWallet.CoinType.ETH) {
          await importEthAccount({
            accountName,
            privateKey,
          }).unwrap()
        } else if (selectedAccountType.coin === QoraiWallet.CoinType.SOL) {
          await importSolAccount({
            accountName,
            privateKey,
          }).unwrap()
        } else {
          assertNotReached(`Unknown coin ${selectedAccountType.coin}`)
        }
      } catch (error) {
        setHasImportError(true)
        return
      }
      history.push(WalletRoutes.Accounts)
      return
    }

    if (file) {
      const index = file[0]
      const reader = new FileReader()
      reader.onload = async function () {
        if (reader.result) {
          try {
            await importEthAccountFromJson({
              accountName,
              password,
              json: reader.result.toString().trim(),
            }).unwrap()
            history.push(WalletRoutes.Accounts)
          } catch (error) {
            setHasImportError(true)
          }
        }
      }

      reader.readAsText(index)
    }
  }, [
    importOption,
    file,
    selectedAccountType,
    importFilAccount,
    accountName,
    privateKey,
    history,
    importBtcAccount,
    importEthAccount,
    importEthAccountFromJson,
    importSolAccount,
    password,
  ])

  const handleKeyDown = React.useCallback(
    (detail: InputEventDetail) => {
      if (isDisabled) {
        return
      }
      if ((detail.innerEvent as unknown as KeyboardEvent).key === 'Enter') {
        onClickCreateAccount()
      }
    },
    [isDisabled, onClickCreateAccount],
  )

  const onSelectAccountType = React.useCallback(
    (accountType: CreateAccountOptionsType) => () => {
      history.push(
        WalletRoutes.ImportAccountModal.replace(
          ':accountTypeName?',
          accountType.name.toLowerCase(),
        ),
      )
    },
    [history],
  )

  const isDAppCoin =
    !!selectedAccountType
    && DAppSupportedCoinTypes.includes(selectedAccountType?.coin)

  // render
  return (
    <PopupModal
      title={modalTitle}
      onClose={onClickClose}
    >
      <DividerLine />

      {!selectedAccountType && (
        <SelectAccountType
          createAccountOptions={createAccountOptions}
          buttonText={getLocale('qoraiWalletAddAccountImport')}
          onSelectAccountType={onSelectAccountType}
        />
      )}

      {selectedAccountType && (
        <StyledWrapper>
          {isDAppCoin && (
            <Alert type='warning'>
              {getLocale('qoraiWalletImportAccountDisclaimer')}
            </Alert>
          )}

          {selectedAccountType.coin === QoraiWallet.CoinType.FIL && (
            <Alert type='warning'>{filPrivateKeyFormatDescription}</Alert>
          )}
          {selectedAccountType.coin === QoraiWallet.CoinType.BTC && (
            <Alert type='warning'>
              {getLocale(
                'qoraiWalletBtcImportPrivateKeyFormatDescription',
              ).replace(
                '$1',
                selectedAccountType.fixedNetwork === QoraiWallet.BITCOIN_MAINNET
                  ? 'zprv'
                  : 'tprv',
              )}
            </Alert>
          )}

          <CreateAccountStyledWrapper>
            {selectedAccountType.coin === QoraiWallet.CoinType.ETH && (
              <Dropdown
                value={importOption}
                onChange={onChangeImportOption}
              >
                <div slot='label'>
                  {getLocale('qoraiWalletPrivateKeyImportType')}
                </div>

                <div slot='value'>
                  {getLocale(
                    importOption === 'key'
                      ? 'qoraiWalletImportAccountKey'
                      : 'qoraiWalletImportAccountFile',
                  )}
                </div>

                <qora-option
                  key={'key'}
                  value='key'
                >
                  {getLocale('qoraiWalletImportAccountKey')}
                </qora-option>

                <qora-option
                  key={'file'}
                  value='file'
                >
                  {getLocale('qoraiWalletImportAccountFile')}
                </qora-option>
              </Dropdown>
            )}

            {hasImportError && (
              <ErrorText>
                {getLocale('qoraiWalletImportAccountError')}
              </ErrorText>
            )}

            {importOption === 'key' ? (
              <Input
                placeholder={getLocale('qoraiWalletImportAccountPlaceholder')}
                onBlur={clearClipboard}
                type='password'
                onInput={handlePrivateKeyChanged}
                onKeyDown={handleKeyDown}
              >
                {
                  // Label
                  getLocale('qoraiWalletImportAccountKey')
                }
              </Input>
            ) : (
              <>
                <ImportRow>
                  <ImportButton htmlFor='recoverFile'>
                    {getLocale('qoraiWalletImportAccountUploadButton')}
                  </ImportButton>
                  <DisclaimerText>
                    {file
                      ? reduceFileName(file[0].name)
                      : getLocale('qoraiWalletImportAccountUploadPlaceholder')}
                  </DisclaimerText>
                </ImportRow>
                <input
                  type='file'
                  id='recoverFile'
                  name='recoverFile'
                  style={{ display: 'none' }}
                  onChange={onFileUpload}
                  onClick={onClickFileUpload}
                />
                <Input
                  placeholder={getLocale('qoraiWalletInputLabelPassword')}
                  onInput={handlePasswordChanged}
                  onKeyDown={handleKeyDown}
                  onBlur={clearClipboard}
                  type='password'
                  ref={passwordInputRef}
                >
                  {
                    // Label
                    getLocale('qoraiWalletEnterPasswordIfApplicable')
                  }
                </Input>
              </>
            )}

            <Input
              value={accountName}
              placeholder={getLocale('qoraiWalletAddAccountPlaceholder')}
              onInput={handleAccountNameChanged}
              onKeyDown={handleKeyDown}
              showErrors={hasAccountNameError}
              maxlength={QoraiWallet.ACCOUNT_NAME_MAX_CHARACTER_LENGTH}
            >
              {
                // Label
                getLocale('qoraiWalletAddAccountPlaceholder')
              }
            </Input>

            <QoraSquaredButton
              onClick={onClickCreateAccount}
              isDisabled={isDisabled}
              kind='filled'
            >
              {getLocale('qoraiWalletAddAccountImport')}
            </QoraSquaredButton>
          </CreateAccountStyledWrapper>
        </StyledWrapper>
      )}
    </PopupModal>
  )
}

export default ImportAccountModal
