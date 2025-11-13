// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { skipToken } from '@reduxjs/toolkit/query/react'
import Icon from '@qorai/qora/react/icon'
import ProgressRing from '@qorai/qora/react/progressRing'

// Selectors
import {
  useSafeWalletSelector, //
} from '../../../../../common/hooks/use-safe-selector'
import { WalletSelectors } from '../../../../../common/selectors'

// Types
import {
  QoraiWallet,
  AddressMessageInfo,
  AddressMessageInfoIds,
  CoinTypesMap,
} from '../../../../../constants/types'

// Queries
import {
  useAccountsQuery,
  useGetCombinedTokensListQuery,
  useReceiveAddressQuery,
} from '../../../../../common/slices/api.slice.extra'
import {
  useEnableEnsOffchainLookupMutation,
  useGenerateReceiveAddressMutation,
  useGetAddressFromNameServiceUrlQuery,
  useGetEthAddressChecksumQuery,
  useGetFVMAddressQuery,
  useGetIsBase58EncodedSolPubkeyQuery,
  useGetZCashAccountInfoQuery,
  useGetZCashTransactionTypeQuery,
} from '../../../../../common/slices/api.slice'

// Utils
import {
  isValidBtcAddress,
  isValidEVMAddress,
  isValidFilAddress,
  isValidCardanoAddress,
} from '../../../../../utils/address-utils'

// Messages
import {
  FEVMAddressConversionMessage,
  InvalidAddressMessage,
  HasNoDomainAddressMessage,
  AddressValidationMessages,
} from '../../send-ui-messages'

// Utils
import { getLocale } from '../../../../../../common/locale'
import { endsWithAny } from '../../../../../utils/string-utils'
import {
  findTokenByContractAddress,
  getAssetIdKey,
} from '../../../../../utils/asset-utils'
import { isFVMAccount } from '../../../../../utils/account-utils'

// Constants
import {
  supportedENSExtensions,
  supportedSNSExtensions,
  supportedUDExtensions,
} from '../../../../../common/constants/domain-extensions'

// Components
import {
  PopupModal, //
} from '../../../../../components/desktop/popup-modals/index'
import {
  AddressMessage, //
} from '../address-message/address-message'
import {
  AccountListItem, //
} from '../account_list_item/account_list_item'
import { ChecksumInfo } from './checksum_info'

// Styled Components
import {
  Row,
  Column,
  VerticalSpace,
  Text,
} from '../../../../../components/shared/style'
import {
  Wrapper,
  ScrollContainer,
  LabelText,
  AddressInput,
  AddressButton,
  WalletIcon,
  AddressButtonText,
  DomainLoadIcon,
  SearchBoxContainer,
} from './select_address_modal.style'

interface Props {
  onClose: () => void
  selectedNetwork: QoraiWallet.NetworkInfo | undefined
  fromAccountId: QoraiWallet.AccountId | undefined
  selectedAsset: QoraiWallet.BlockchainToken | undefined
  toAddressOrUrl: string
  setToAddressOrUrl: (address: string) => void
  setResolvedDomainAddress: (address: string) => void
}

export const SelectAddressModal = React.forwardRef<HTMLDivElement, Props>(
  (props: Props, forwardedRef) => {
    const {
      onClose,
      fromAccountId,
      selectedNetwork,
      selectedAsset,
      toAddressOrUrl,
      setToAddressOrUrl,
      setResolvedDomainAddress,
    } = props

    // Mutations
    const [enableEnsOffchainLookup] = useEnableEnsOffchainLookupMutation()
    const [generateReceiveAddress, { isLoading: isGeneratingAddress }] =
      useGenerateReceiveAddressMutation()

    // State
    const [searchValue, setSearchValue] = React.useState<string>(
      toAddressOrUrl ?? '',
    )
    const [showChecksumInfo, setShowChecksumInfo] =
      React.useState<boolean>(false)
    const [isOffChainEnsWarningDismissed, dismissOffchainEnsWarning] =
      React.useState<boolean>(false)

    // Queries
    const { accounts } = useAccountsQuery()
    const { data: fullTokenList } = useGetCombinedTokensListQuery()
    const { receiveAddress: fromAccountAddress } =
      useReceiveAddressQuery(fromAccountId)

    // Domain name lookup Queries
    const selectedSendAssetId = selectedAsset
      ? getAssetIdKey(selectedAsset)
      : null

    const lowercaseSearchValue = searchValue.toLowerCase()

    const searchValueHasValidExtension = lowercaseSearchValue
      ? endsWithAny(supportedUDExtensions, lowercaseSearchValue)
        || (selectedAsset?.coin === QoraiWallet.CoinType.SOL
          && endsWithAny(supportedSNSExtensions, lowercaseSearchValue))
        || (selectedAsset?.coin === QoraiWallet.CoinType.ETH
          && endsWithAny(supportedENSExtensions, lowercaseSearchValue))
      : false

    const {
      data: nameServiceInfo,
      isFetching: isSearchingForDomain,
      isError: hasNameServiceError = false,
    } = useGetAddressFromNameServiceUrlQuery(
      searchValueHasValidExtension
        ? {
            tokenId: selectedSendAssetId,
            // preventing additional lookups for address casing changes
            url: lowercaseSearchValue,
          }
        : skipToken,
    )

    const resolvedDomainAddress =
      searchValueHasValidExtension
      && !hasNameServiceError
      && nameServiceInfo?.address
        ? nameServiceInfo.address
        : ''

    const showEnsOffchainWarning =
      nameServiceInfo?.requireOffchainConsent || false

    // Memos
    const accountsByNetwork = React.useMemo(() => {
      if (!selectedNetwork || !fromAccountId) {
        return []
      }

      if (fromAccountId.coin === QoraiWallet.CoinType.FIL) {
        const filecoinAccounts = accounts.filter(
          (account) => account.accountId.keyringId === fromAccountId?.keyringId,
        )
        const fevmAccounts = accounts.filter(
          (account) => account.accountId.coin === QoraiWallet.CoinType.ETH,
        )
        return filecoinAccounts.concat(fevmAccounts)
      }

      // TODO(apaymyshev): for bitcoin should allow sending to my account, but
      // from different keyring (i.e. segwit -> taproot)
      // https://github.com/qorai/qorai-browser/issues/29262
      return accounts.filter(
        (account) =>
          account.accountId.keyringId === fromAccountId.keyringId
          || (selectedAsset?.contractAddress === ''
            && isFVMAccount(account, selectedNetwork)),
      )
    }, [accounts, selectedNetwork, fromAccountId, selectedAsset])

    const filteredAccounts = React.useMemo(() => {
      return accountsByNetwork.filter(
        (account) =>
          account.accountId.address
            .toLocaleLowerCase()
            .startsWith(searchValue.toLocaleLowerCase())
          || account.name
            .toLowerCase()
            .startsWith(searchValue.toLocaleLowerCase()),
      )
    }, [accountsByNetwork, searchValue])

    const evmAddressesForFVMTranslation = React.useMemo(
      () =>
        accountsByNetwork
          .filter(
            (account) => account.accountId.coin === QoraiWallet.CoinType.ETH,
          )
          .map((account) => account.accountId.address),
      [accountsByNetwork],
    )

    const { data: fevmTranslatedAddresses } = useGetFVMAddressQuery(
      selectedNetwork
        && selectedNetwork?.coin === QoraiWallet.CoinType.FIL
        && evmAddressesForFVMTranslation.length
        ? {
            coin: selectedNetwork.coin,
            addresses: evmAddressesForFVMTranslation,
            isMainNet: selectedNetwork.chainId === QoraiWallet.FILECOIN_MAINNET,
          }
        : skipToken,
    )

    const trimmedSearchValue = searchValue.trim()
    const isValidEvmAddress = isValidEVMAddress(trimmedSearchValue)

    const { data: ethAddressChecksum = '' } = useGetEthAddressChecksumQuery(
      isValidEvmAddress ? trimmedSearchValue : skipToken,
    )

    const showFilecoinFEVMWarning =
      fromAccountId?.coin === QoraiWallet.CoinType.FIL
        ? trimmedSearchValue.startsWith('0x')
          && !validateETHAddress(trimmedSearchValue, ethAddressChecksum)
        : false

    const { data: isBase58 = false } = useGetIsBase58EncodedSolPubkeyQuery(
      fromAccountId?.coin === QoraiWallet.CoinType.SOL && trimmedSearchValue
        ? trimmedSearchValue
        : skipToken,
    )

    const {
      data: getZCashTransactionTypeResult = {
        txType: QoraiWallet.ZCashTxType.kUnknown,
        error: QoraiWallet.ZCashAddressError.kNoError,
      },
    } = useGetZCashTransactionTypeQuery(
      fromAccountId
        && selectedNetwork
        && fromAccountId.coin === QoraiWallet.CoinType.ZEC
        && trimmedSearchValue
        ? {
            chainId: selectedNetwork.chainId,
            accountId: fromAccountId,
            useShieldedPool: !!selectedAsset?.isShielded,
            address: trimmedSearchValue,
          }
        : skipToken,
    )

    const addressMessageId: AddressMessageInfoIds | undefined =
      React.useMemo(() => {
        return processAddressOrUrl({
          addressOrUrl: trimmedSearchValue,
          fromAccountAddress: fromAccountAddress,
          ethAddressChecksum,
          isBase58,
          coinType: fromAccountId?.coin ?? QoraiWallet.CoinType.ETH,
          token: selectedAsset,
          zcashAddressError: getZCashTransactionTypeResult.error,
          fullTokenList,
          hasNameServiceError,
          isValidExtension: searchValueHasValidExtension,
          isSearchingForDomain,
          resolvedDomainAddress,
          showEnsOffchainWarning,
          isOffChainEnsWarningDismissed,
        })
      }, [
        trimmedSearchValue,
        fromAccountAddress,
        fromAccountId?.coin,
        ethAddressChecksum,
        isBase58,
        selectedAsset,
        getZCashTransactionTypeResult,
        fullTokenList,
        hasNameServiceError,
        searchValueHasValidExtension,
        isSearchingForDomain,
        resolvedDomainAddress,
        showEnsOffchainWarning,
        isOffChainEnsWarningDismissed,
      ])

    const addressMessageInformation = React.useMemo(() => {
      return getAddressMessageInfo({
        showFilecoinFEVMWarning,
        fevmTranslatedAddresses,
        toAddressOrUrl: searchValue,
        messageId: addressMessageId,
        coinType: fromAccountId?.coin,
      })
    }, [
      showFilecoinFEVMWarning,
      fevmTranslatedAddresses,
      searchValue,
      addressMessageId,
      fromAccountId?.coin,
    ])

    const showAddressMessage =
      (addressMessageInformation
        && addressMessageInformation.id
          === AddressMessageInfoIds.sameAddressError
        && filteredAccounts.length !== 0)
      || (!isSearchingForDomain
        && addressMessageInformation
        && filteredAccounts.length === 0)

    // Methods
    const onSelectAccount = React.useCallback(
      async (account: QoraiWallet.AccountInfo, shieldedAddress?: string) => {
        if (shieldedAddress) {
          setToAddressOrUrl(shieldedAddress)
          setResolvedDomainAddress('')
          onClose()
          return
        }
        if (
          account.accountId.coin === QoraiWallet.CoinType.BTC
          || account.accountId.coin === QoraiWallet.CoinType.ZEC
          || account.accountId.coin === QoraiWallet.CoinType.ADA
        ) {
          const generatedAddress = await generateReceiveAddress(
            account.accountId,
          ).unwrap()
          setToAddressOrUrl(generatedAddress)
        } else {
          setToAddressOrUrl(account.address)
        }
        setResolvedDomainAddress('')
        onClose()
      },
      [
        setToAddressOrUrl,
        generateReceiveAddress,
        onClose,
        setResolvedDomainAddress,
      ],
    )

    const onSelectAddress = React.useCallback(
      (address: string) => {
        setToAddressOrUrl(address)
        setResolvedDomainAddress(resolvedDomainAddress)
        onClose()
      },
      [
        setToAddressOrUrl,
        setResolvedDomainAddress,
        resolvedDomainAddress,
        onClose,
      ],
    )

    const onENSConsent = React.useCallback(() => {
      enableEnsOffchainLookup()
      dismissOffchainEnsWarning(true)
    }, [enableEnsOffchainLookup])

    if (showChecksumInfo) {
      return (
        <PopupModal
          onClose={onClose}
          onBack={() => setShowChecksumInfo(false)}
          title=''
          width='560px'
          height='90vh'
          ref={forwardedRef}
        >
          <ChecksumInfo />
        </PopupModal>
      )
    }

    // render
    return (
      <PopupModal
        onClose={onClose}
        title={getLocale('qoraiWalletChooseRecipient')}
        width='560px'
        height='90vh'
        ref={forwardedRef}
      >
        <Wrapper
          fullWidth={true}
          justifyContent='flex-start'
        >
          <SearchBoxContainer
            fullWidth={true}
            padding='0px 40px'
            margin='0px 0px 16px 0px'
          >
            <Row
              width='100%'
              justifyContent='flex-start'
              padding='0px 4px'
              marginBottom={4}
            >
              <LabelText
                textSize='12px'
                isBold={true}
              >
                {getLocale('qoraiWalletSendTo')}
              </LabelText>
            </Row>
            <AddressInput
              value={searchValue}
              onInput={(e) => setSearchValue(e.value)}
              placeholder={getLocale('qoraiWalletAddressOrDomainPlaceholder')}
              type='text'
              disabled={isGeneratingAddress}
            >
              <div slot='right-icon'>
                <Icon name='copy-plain-text' />
              </div>
            </AddressInput>
          </SearchBoxContainer>
          {isGeneratingAddress ? (
            <Column
              fullHeight
              fullWidth
            >
              <ProgressRing mode='indeterminate' />
            </Column>
          ) : (
            <ScrollContainer
              fullWidth={true}
              justifyContent='flex-start'
            >
              {filteredAccounts.length !== 0 && (
                <>
                  <Row
                    width='100%'
                    justifyContent='flex-start'
                    padding='0px 8px'
                    marginBottom={4}
                  >
                    <LabelText
                      textSize='12px'
                      isBold={true}
                    >
                      {getLocale('qoraiWalletMyAddresses')}
                    </LabelText>
                  </Row>
                  {filteredAccounts.map((account) => (
                    <AccountGroupItem
                      key={account.accountId.uniqueKey}
                      account={account}
                      onSelectAccount={onSelectAccount}
                      fromAccountId={fromAccountId}
                      selectedAsset={selectedAsset}
                      accountAlias={
                        fevmTranslatedAddresses?.[account.accountId.address]
                      }
                    />
                  ))}
                </>
              )}
              {isSearchingForDomain && (
                <Row margin='26px 0px 0px 0px'>
                  <DomainLoadIcon />
                  <Text
                    textSize='14px'
                    isBold={false}
                    textColor='secondary'
                  >
                    {getLocale('qoraiWalletSearchingForDomain')}
                  </Text>
                </Row>
              )}
              {filteredAccounts.length === 0
                && !isSearchingForDomain
                && !showEnsOffchainWarning
                && addressMessageInformation?.type !== 'error' && (
                  <AddressButton onClick={() => onSelectAddress(searchValue)}>
                    <WalletIcon />
                    <Column alignItems='flex-start'>
                      <AddressButtonText
                        textSize='14px'
                        isBold={true}
                        textColor='primary'
                        textAlign='left'
                      >
                        {searchValue}
                      </AddressButtonText>
                      {searchValueHasValidExtension && (
                        <AddressButtonText
                          textSize='14px'
                          isBold={false}
                          textColor='secondary'
                          textAlign='left'
                        >
                          {resolvedDomainAddress}
                        </AddressButtonText>
                      )}
                    </Column>
                  </AddressButton>
                )}
              {showAddressMessage && (
                <>
                  <VerticalSpace space='8px' />
                  <AddressMessage
                    addressMessageInfo={addressMessageInformation}
                    onClickEnableENSOffchain={
                      addressMessageInformation.id
                      === AddressMessageInfoIds.ensOffchainLookupWarning
                        ? onENSConsent
                        : undefined
                    }
                    onClickHowToSolve={
                      addressMessageInformation.id
                        === AddressMessageInfoIds.invalidChecksumError
                      || addressMessageInformation.id
                        === AddressMessageInfoIds.missingChecksumWarning
                        ? () => setShowChecksumInfo(true)
                        : undefined
                    }
                  />
                </>
              )}
            </ScrollContainer>
          )}
        </Wrapper>
      </PopupModal>
    )
  },
)

interface AccountsListProps {
  account: QoraiWallet.AccountInfo
  onSelectAccount: (
    account: QoraiWallet.AccountInfo,
    shieldedAddress?: string,
  ) => void
  selectedAsset?: QoraiWallet.BlockchainToken
  fromAccountId?: QoraiWallet.AccountId
  accountAlias?: string
}

export const AccountGroupItem = (props: AccountsListProps) => {
  const {
    account,
    onSelectAccount,
    selectedAsset,
    fromAccountId,
    accountAlias,
  } = props

  // Selectors
  const isZCashShieldedTransactionsEnabled = useSafeWalletSelector(
    WalletSelectors.isZCashShieldedTransactionsEnabled,
  )

  // Queries
  const { data: zcashAccountInfo } = useGetZCashAccountInfoQuery(
    isZCashShieldedTransactionsEnabled
      && account.accountId.coin === QoraiWallet.CoinType.ZEC
      ? account.accountId
      : skipToken,
  )

  // Computed
  const isShieldedAccount =
    isZCashShieldedTransactionsEnabled
    && !!zcashAccountInfo
    && !!zcashAccountInfo.accountShieldBirthday

  return (
    <>
      <AccountListItem
        account={account}
        onClick={() => onSelectAccount(account)}
        isDisabled={
          !!selectedAsset?.isShielded
          || account.accountId.uniqueKey === fromAccountId?.uniqueKey
        }
        isSelected={account.accountId.uniqueKey === fromAccountId?.uniqueKey}
        addressOverride={
          account.accountId.coin === QoraiWallet.CoinType.ZEC
          && zcashAccountInfo
            ? zcashAccountInfo.nextTransparentReceiveAddress.addressString
            : undefined
        }
        accountAlias={accountAlias}
      />
      {zcashAccountInfo && isShieldedAccount && (
        <AccountListItem
          account={account}
          onClick={() =>
            onSelectAccount(account, zcashAccountInfo.orchardInternalAddress)
          }
          isDisabled={!!selectedAsset?.isShielded}
          isSelected={
            !!selectedAsset?.isShielded
            && account.accountId.uniqueKey === fromAccountId?.uniqueKey
          }
          isShielded={true}
          addressOverride={
            account.accountId.coin === QoraiWallet.CoinType.ZEC
            && zcashAccountInfo
              ? zcashAccountInfo.orchardInternalAddress
              : undefined
          }
          accountAlias={undefined}
        />
      )}
    </>
  )
}

function getAddressMessageInfo({
  fevmTranslatedAddresses,
  showFilecoinFEVMWarning,
  toAddressOrUrl,
  messageId,
  coinType,
}: {
  showFilecoinFEVMWarning: boolean
  fevmTranslatedAddresses: Record<string, string> | undefined
  toAddressOrUrl: string
  messageId: AddressMessageInfoIds | undefined
  coinType: QoraiWallet.CoinType | undefined
}): AddressMessageInfo | undefined {
  if (showFilecoinFEVMWarning) {
    return {
      ...FEVMAddressConversionMessage,
      placeholder: fevmTranslatedAddresses?.[toAddressOrUrl],
    }
  }
  if (
    messageId === AddressMessageInfoIds.invalidAddressError
    // Checking for not undefined here since BTC coinType is 0
    // which is a falsey value.
    && coinType !== undefined
  ) {
    return {
      ...InvalidAddressMessage,
      placeholder: CoinTypesMap[coinType],
    }
  }
  if (
    messageId === AddressMessageInfoIds.hasNoDomainAddress
    // Checking for not undefined here since BTC coinType is 0
    // which is a falsey value.
    && coinType !== undefined
  ) {
    return {
      ...HasNoDomainAddressMessage,
      placeholder: CoinTypesMap[coinType],
    }
  }

  return AddressValidationMessages.find((message) => message.id === messageId)
}

const validateETHAddress = (address: string, checksumAddress: string) => {
  if (!isValidEVMAddress(address)) {
    return AddressMessageInfoIds.invalidAddressError
  }

  if (checksumAddress === address) {
    return undefined
  }

  if ([address.toLowerCase(), address.toUpperCase()].includes(address)) {
    return AddressMessageInfoIds.missingChecksumWarning
  }

  return AddressMessageInfoIds.invalidChecksumError
}

const processEthereumAddress = (
  addressOrUrl: string,
  token: QoraiWallet.BlockchainToken | undefined,
  checksumAddress: string,
) => {
  if (
    token
    && (token.chainId === QoraiWallet.FILECOIN_ETHEREUM_MAINNET_CHAIN_ID
      || token.chainId === QoraiWallet.FILECOIN_ETHEREUM_TESTNET_CHAIN_ID)
    && isValidFilAddress(addressOrUrl)
  ) {
    return undefined
  }

  return validateETHAddress(addressOrUrl, checksumAddress)
}

const processZCashAddress = (
  zcashAddressError: QoraiWallet.ZCashAddressError,
) => {
  if (zcashAddressError === QoraiWallet.ZCashAddressError.kNoError) {
    return undefined
  }
  if (
    zcashAddressError === QoraiWallet.ZCashAddressError.kInvalidUnifiedAddress
  ) {
    return AddressMessageInfoIds.zcashInvalidUnifiedAddressError
  }
  if (
    zcashAddressError
    === QoraiWallet.ZCashAddressError.kInvalidTransparentAddress
  ) {
    return AddressMessageInfoIds.zcashInvalidTransparentAddressError
  }
  if (
    zcashAddressError
    === QoraiWallet.ZCashAddressError
      .kInvalidUnifiedAddressMissingTransparentPart
  ) {
    // eslint-disable-next-line max-len
    return AddressMessageInfoIds.zcashInvalidUnifiedAddressMissingTransparentPartError
  }
  if (
    zcashAddressError
    === QoraiWallet.ZCashAddressError.kInvalidUnifiedAddressMissingOrchardPart
  ) {
    // eslint-disable-next-line max-len
    return AddressMessageInfoIds.zcashInvalidUnifiedAddressMissingOrchardPartError
  }
  if (
    zcashAddressError
    === QoraiWallet.ZCashAddressError.kInvalidAddressNetworkMismatch
  ) {
    return AddressMessageInfoIds.zcashInvalidAddressNetworkMismatchError
  }

  return AddressMessageInfoIds.invalidAddressError
}

const processFilecoinAddress = (addressOrUrl: string, checksum: string) => {
  const valueToLowerCase = addressOrUrl.toLowerCase()

  // If value starts with 0x, will check if it's a valid address
  if (valueToLowerCase.startsWith('0x')) {
    return validateETHAddress(addressOrUrl, checksum)
  }

  if (!isValidFilAddress(valueToLowerCase)) {
    return AddressMessageInfoIds.invalidAddressError
  }

  // Default
  return undefined
}

const processSolanaAddress = (isBase58Encoded: boolean | undefined) => {
  // Check if value is a Base58 Encoded Solana Pubkey
  if (!isBase58Encoded) {
    return AddressMessageInfoIds.invalidAddressError
  }

  return undefined
}

const processBitcoinAddress = (addressOrUrl: string, testnet: boolean) => {
  if (!isValidBtcAddress(addressOrUrl, testnet)) {
    return AddressMessageInfoIds.invalidAddressError
  }

  return undefined
}

const processCardanoAddress = (addressOrUrl: string, testnet: boolean) => {
  if (!isValidCardanoAddress(addressOrUrl, testnet)) {
    return AddressMessageInfoIds.invalidAddressError
  }

  return undefined
}

const processDomainLookupResponseWarning = (
  urlHasValidExtension: boolean,
  resolvedAddress: string | undefined,
  hasDomainLookupError: boolean,
  showEnsOffchainWarning: boolean,
  isOffChainEnsWarningDismissed: boolean,
  fromAccountAddress?: string,
) => {
  if (showEnsOffchainWarning && !isOffChainEnsWarningDismissed) {
    return AddressMessageInfoIds.ensOffchainLookupWarning
  }

  if (!urlHasValidExtension) {
    return AddressMessageInfoIds.invalidDomainExtension
  }

  if (hasDomainLookupError || !resolvedAddress) {
    return AddressMessageInfoIds.hasNoDomainAddress
  }

  // If found address is the same as the selectedAccounts Wallet Address
  if (
    fromAccountAddress
    && resolvedAddress.toLowerCase() === fromAccountAddress.toLowerCase()
  ) {
    return AddressMessageInfoIds.sameAddressError
  }

  return undefined
}

function processAddressOrUrl({
  addressOrUrl,
  fromAccountAddress,
  ethAddressChecksum,
  isBase58,
  coinType,
  zcashAddressError,
  token,
  fullTokenList,
  isValidExtension,
  resolvedDomainAddress,
  isSearchingForDomain,
  hasNameServiceError,
  showEnsOffchainWarning,
  isOffChainEnsWarningDismissed,
}: {
  addressOrUrl: string
  fromAccountAddress: string | undefined
  coinType: QoraiWallet.CoinType | undefined
  token: QoraiWallet.BlockchainToken | undefined
  ethAddressChecksum: string
  isBase58: boolean
  zcashAddressError: QoraiWallet.ZCashAddressError
  fullTokenList: QoraiWallet.BlockchainToken[]
  isValidExtension: boolean
  resolvedDomainAddress: string | undefined
  isSearchingForDomain: boolean
  hasNameServiceError: boolean
  showEnsOffchainWarning: boolean
  isOffChainEnsWarningDismissed: boolean
}) {
  // Do nothing if value is an empty string
  if (addressOrUrl === '') {
    return undefined
  }

  if (addressOrUrl.includes('.') && !isSearchingForDomain) {
    return processDomainLookupResponseWarning(
      isValidExtension,
      resolvedDomainAddress,
      hasNameServiceError,
      showEnsOffchainWarning,
      isOffChainEnsWarningDismissed,
      fromAccountAddress,
    )
  }

  if (
    fromAccountAddress
    && fromAccountAddress.toLowerCase() === addressOrUrl.toLowerCase()
  ) {
    return AddressMessageInfoIds.sameAddressError
  }

  if (findTokenByContractAddress(addressOrUrl, fullTokenList) !== undefined) {
    return AddressMessageInfoIds.contractAddressError
  }

  switch (coinType) {
    case undefined:
      return undefined
    case QoraiWallet.CoinType.ETH: {
      return processEthereumAddress(addressOrUrl, token, ethAddressChecksum)
    }
    case QoraiWallet.CoinType.FIL: {
      return processFilecoinAddress(addressOrUrl, ethAddressChecksum)
    }
    case QoraiWallet.CoinType.SOL: {
      return processSolanaAddress(isBase58)
    }
    case QoraiWallet.CoinType.BTC: {
      return processBitcoinAddress(
        addressOrUrl,
        token?.chainId === QoraiWallet.BITCOIN_TESTNET,
      )
    }
    case QoraiWallet.CoinType.ZEC: {
      return processZCashAddress(zcashAddressError)
    }
    case QoraiWallet.CoinType.ADA: {
      return processCardanoAddress(
        addressOrUrl,
        token?.chainId === QoraiWallet.CARDANO_TESTNET,
      )
    }
    default: {
      console.log(`Unknown coin ${coinType}`)
      return undefined
    }
  }
}
