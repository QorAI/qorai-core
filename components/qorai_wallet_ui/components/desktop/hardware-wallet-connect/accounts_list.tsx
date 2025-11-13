// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { assert, assertNotReached } from 'chrome://resources/js/assert.js'
import * as React from 'react'
import { EntityId } from '@reduxjs/toolkit'
import Dropdown from '@qorai/qora/react/dropdown'

// Types
import { QoraiWallet } from '../../../constants/types'
import {
  DerivationScheme,
  HardwareImportScheme,
  AccountFromDevice,
} from '../../../common/hardware/types'

// Utils
import { getLocale } from '../../../../common/locale'

import {
  useGetNetworksRegistryQuery, //
} from '../../../common/slices/api.slice'
import { makeNetworkAsset } from '../../../options/asset-options'
import {
  networkEntityAdapter, //
  selectAllNetworksFromQueryResult,
} from '../../../common/slices/entities/network.entity'

// Components
import { SearchBar } from '../../shared/search-bar/index'
import { NetworkFilterSelector } from '../network-filter-selector'
import { AccountListItem } from './account_list_item'

// Styles
import {
  DisclaimerText,
  DisclaimerWrapper,
} from '../popup-modals/add-account-modal/style'
import {
  ButtonsContainer,
  HardwareWalletAccountsListContainer,
  SelectRow,
  SelectWrapper,
  LoadingWrapper,
  LoadIcon,
  NoSearchResultText,
  AccountListContainer,
  AccountListHeader,
  AccountListContent,
  DropdownLabel,
  HelpLink,
} from './hardware_wallet_connect.styles'
import {
  ContinueButton, //
} from '../../../page/screens/onboarding/onboarding.style'
import { Row } from '../../shared/style'

export interface AccountFromDeviceListItem extends AccountFromDevice {
  alreadyInWallet: boolean
  shouldAddToWallet: boolean
}

interface Props {
  currentHardwareImportScheme: HardwareImportScheme
  supportedSchemes: HardwareImportScheme[]
  accounts: AccountFromDeviceListItem[]
  onLoadMore: () => void
  onAccountChecked: (path: string, checked: boolean) => void
  setHardwareImportScheme: (scheme: DerivationScheme) => void
  onAddAccounts: () => void
}

const defaultNetworkId = (
  currentHardwareImportScheme: HardwareImportScheme,
) => {
  if (currentHardwareImportScheme.coin === QoraiWallet.CoinType.ETH) {
    return QoraiWallet.MAINNET_CHAIN_ID
  }

  if (currentHardwareImportScheme.coin === QoraiWallet.CoinType.SOL) {
    return QoraiWallet.SOLANA_MAINNET
  }

  if (currentHardwareImportScheme.coin === QoraiWallet.CoinType.FIL) {
    assert(currentHardwareImportScheme.fixedNetwork)
    return currentHardwareImportScheme.fixedNetwork
  }

  if (currentHardwareImportScheme.coin === QoraiWallet.CoinType.BTC) {
    assert(currentHardwareImportScheme.fixedNetwork)
    return currentHardwareImportScheme.fixedNetwork
  }

  assertNotReached(
    `Unknown currentHardwareImportScheme ${currentHardwareImportScheme}`,
  )
}

const coinsSupportingSchemesDropdown = [
  QoraiWallet.CoinType.ETH,
  QoraiWallet.CoinType.SOL,
]

const getHardwareImportSchemeLabel = (scheme: HardwareImportScheme): string => {
  return `${scheme.name} "${scheme.pathTemplate('x')}"`
}

export const HardwareWalletAccountsList = ({
  currentHardwareImportScheme,
  supportedSchemes,
  setHardwareImportScheme,
  accounts,
  onLoadMore,
  onAccountChecked,
  onAddAccounts,
}: Props) => {
  const { coin } = currentHardwareImportScheme

  // queries
  const { data: networksRegistry } = useGetNetworksRegistryQuery()

  // state
  const [filteredAccountList, setFilteredAccountList] = React.useState<
    AccountFromDeviceListItem[]
  >([])
  const [isLoadingMore, setIsLoadingMore] = React.useState<boolean>(false)
  const [selectedNetworkId, setSelectedNetworkId] = React.useState<EntityId>(
    defaultNetworkId(currentHardwareImportScheme),
  )

  // memos
  const accountNativeAsset = React.useMemo(() => {
    if (!networksRegistry) {
      return undefined
    }
    return makeNetworkAsset(networksRegistry.entities[selectedNetworkId])
  }, [networksRegistry, selectedNetworkId])

  const networksSubset = React.useMemo(() => {
    if (!networksRegistry) {
      return []
    }

    if (currentHardwareImportScheme.fixedNetwork) {
      return selectAllNetworksFromQueryResult({
        data: networksRegistry,
      }).filter(
        (n) =>
          n.coin === currentHardwareImportScheme.coin
          && n.chainId === currentHardwareImportScheme.fixedNetwork,
      )
    }

    return networksRegistry.visibleIdsByCoinType[
      currentHardwareImportScheme.coin
    ].map((id) => networksRegistry.entities[id]!)
  }, [networksRegistry, currentHardwareImportScheme])

  const showSchemesDropdown = coinsSupportingSchemesDropdown.includes(
    currentHardwareImportScheme.coin,
  )

  const dropdownItems = React.useMemo(() => {
    if (!showSchemesDropdown) {
      return null
    }
    return (
      <>
        <div slot='value'>
          {getHardwareImportSchemeLabel(currentHardwareImportScheme)}
        </div>
        {supportedSchemes.map((scheme) => {
          return (
            <qora-option
              value={scheme.derivationScheme}
              key={scheme.derivationScheme}
            >
              {getHardwareImportSchemeLabel(scheme)}
            </qora-option>
          )
        })}
      </>
    )
  }, [currentHardwareImportScheme, showSchemesDropdown, supportedSchemes])

  // methods
  const onSelectAccountCheckbox =
    (account: AccountFromDeviceListItem) => () => {
      onAccountChecked(account.derivationPath, !account.shouldAddToWallet)
    }

  const filterAccountList = (event: React.ChangeEvent<HTMLInputElement>) => {
    const search = event?.target?.value || ''
    if (search === '') {
      setFilteredAccountList(accounts)
    } else {
      const filteredList = accounts.filter((account) => {
        return (
          account.address.toLowerCase() === search.toLowerCase()
          || account.address.toLowerCase().startsWith(search.toLowerCase())
        )
      })
      setFilteredAccountList(filteredList)
    }
  }

  const onClickLoadMore = () => {
    setIsLoadingMore(true)
    onLoadMore()
  }

  const onSelectNetwork = React.useCallback(
    (n: QoraiWallet.NetworkInfo): void => {
      setSelectedNetworkId(networkEntityAdapter.selectId(n))
      assert(!currentHardwareImportScheme.fixedNetwork)
    },
    [currentHardwareImportScheme],
  )

  const onChangeDerivationScheme = (value?: string) => {
    if (value) {
      setHardwareImportScheme(value as DerivationScheme)
    }
  }

  // effects
  React.useEffect(() => {
    setFilteredAccountList(accounts)
    setIsLoadingMore(false)
  }, [accounts])

  React.useEffect(() => {
    if (selectedNetworkId) {
      return
    }
    if (!networksRegistry) {
      return
    }

    // set network dropdown default value
    setSelectedNetworkId(networksRegistry.visibleIdsByCoinType[coin][0])
  }, [networksRegistry, coin, selectedNetworkId])

  // render
  return (
    <>
      <SelectRow>
        <SelectWrapper>
          <NetworkFilterSelector
            networkListSubset={networksSubset}
            selectedNetwork={networksRegistry?.entities[selectedNetworkId]}
            onSelectNetwork={onSelectNetwork}
            disableAllAccountsOption
            isV2
          />
          {coin === QoraiWallet.CoinType.ETH ? (
            <Dropdown
              value={currentHardwareImportScheme.derivationScheme}
              onChange={(e) => onChangeDerivationScheme(e.value)}
            >
              <Row
                width='100%'
                justifyContent='space-between'
                slot='label'
              >
                <DropdownLabel>{getLocale('qoraiWalletHDPath')}</DropdownLabel>
                <HelpLink
                  href='https://support.qorai.app/hc/categories/360001062531-Wallet'
                  target='_blank'
                  rel='noopener noreferrer'
                >
                  {getLocale('qoraiWalletHelpCenter')}
                </HelpLink>
              </Row>
              {dropdownItems}
            </Dropdown>
          ) : null}
          {coin === QoraiWallet.CoinType.SOL ? (
            <Dropdown
              value={currentHardwareImportScheme.derivationScheme}
              onChange={(e) => onChangeDerivationScheme(e.value)}
            >
              {dropdownItems}
            </Dropdown>
          ) : null}
        </SelectWrapper>
      </SelectRow>
      {showSchemesDropdown && (
        <DisclaimerWrapper>
          <DisclaimerText>
            {getLocale('qoraiWalletSwitchHDPathTextHardwareWallet')}
          </DisclaimerText>
        </DisclaimerWrapper>
      )}
      <SearchBar
        placeholder={getLocale('qoraiWalletSearchScannedAccounts')}
        action={filterAccountList}
        isV2
      />
      <HardwareWalletAccountsListContainer>
        {accounts.length === 0 && (
          <LoadingWrapper>
            <LoadIcon size={'big'} />
          </LoadingWrapper>
        )}

        {accounts.length > 0 && filteredAccountList.length === 0 && (
          <NoSearchResultText>
            {getLocale('qoraiWalletConnectHardwareSearchNothingFound')}
          </NoSearchResultText>
        )}

        {accountNativeAsset
          && accounts.length > 0
          && filteredAccountList.length > 0 && (
            <AccountListContainer>
              <AccountListHeader>
                <div>{getLocale('qoraiWalletSubviewAccount')}</div>
                <div>{getLocale('qoraiWalletBalance')}</div>
                <div>{getLocale('qoraiWalletAddAccountConnect')}</div>
              </AccountListHeader>
              <AccountListContent>
                {filteredAccountList.map((account) => {
                  return (
                    <AccountListItem
                      key={account.derivationPath}
                      balanceAsset={accountNativeAsset}
                      address={account.address}
                      selected={
                        account.alreadyInWallet || account.shouldAddToWallet
                      }
                      disabled={account.alreadyInWallet}
                      onSelect={onSelectAccountCheckbox(account)}
                    />
                  )
                })}
              </AccountListContent>
            </AccountListContainer>
          )}
      </HardwareWalletAccountsListContainer>
      <ButtonsContainer>
        <ContinueButton
          onClick={onClickLoadMore}
          isLoading={isLoadingMore}
          isDisabled={
            isLoadingMore
            || accounts.length === 0
            || currentHardwareImportScheme.singleAccount
          }
        >
          {isLoadingMore
            ? getLocale('qoraiWalletLoadingMoreAccountsHardwareWallet')
            : getLocale('qoraiWalletLoadMoreAccountsHardwareWallet')}
        </ContinueButton>
        <ContinueButton
          onClick={onAddAccounts}
          isDisabled={!accounts.find((acc) => acc.shouldAddToWallet)}
        >
          {getLocale('qoraiWalletButtonContinue')}
        </ContinueButton>
      </ButtonsContainer>
    </>
  )
}

export default HardwareWalletAccountsList
