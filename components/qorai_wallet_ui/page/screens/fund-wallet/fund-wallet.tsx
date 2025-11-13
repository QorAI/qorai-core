// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { skipToken } from '@reduxjs/toolkit/query/react'
import { Redirect, Route, Switch, useHistory, useParams } from 'react-router'

// Selectors
import { useSafeUISelector } from '../../../common/hooks/use-safe-selector'
import { UISelectors } from '../../../common/selectors'

// utils
import { getLocale } from '../../../../common/locale'
import {
  getAssetIdKey,
  getRampAssetSymbol,
  isSelectedAssetInAssetOptions,
} from '../../../utils/asset-utils'

// types
import {
  QoraiWallet,
  BuyOption,
  NetworkFilterType,
  WalletRoutes,
} from '../../../constants/types'

// options
import { AllNetworksOption } from '../../../options/network-filter-options'
import { SelectBuyOption } from '../../../components/buy-send-swap/select-buy-option/select-buy-option'

// hooks
import {
  useGetBuyUrlQuery,
  useGetDefaultFiatCurrencyQuery,
  useGetNetworkQuery,
  useGetOnRampAssetsQuery,
  useGetOnRampFiatCurrenciesQuery,
  useGetOnRampNetworksQuery,
  useLazyGetBuyUrlQuery,
} from '../../../common/slices/api.slice'
import {
  useAccountsQuery,
  useReceiveAddressQuery,
} from '../../../common/slices/api.slice.extra'

// style
import {
  Column,
  Flex,
  LoadingIcon,
  Row,
  VerticalSpace,
  QoraSquaredButton,
} from '../../../components/shared/style'
import {
  ScrollContainer,
  SearchWrapper,
  SelectAssetWrapper,
  Title,
  Description,
  Divider,
  Alert,
  AlertText,
  InfoIcon,
  TokenListWrapper,
  StyledWrapper,
} from './fund-wallet.style'

// components
import {
  RenderTokenFunc,
  VirtualizedTokensList,
} from '../../../components/desktop/views/portfolio/components/token-lists/virtualized-tokens-list'
import SearchBar from '../../../components/shared/search-bar'
import SelectAccountItem from '../../../components/shared/select-account-item'
import SelectAccount from '../../../components/shared/select-account'
import { BuyAssetOptionItem } from '../../../components/shared/buy-option/buy-asset-option'
import CreateAccountTab from '../../../components/buy-send-swap/create-account'
import {
  BuyAmountInput, //
} from '../../../components/buy-send-swap/buy_amount_input/buy_amount_input'
import SelectHeader from '../../../components/buy-send-swap/select-header'
import {
  SelectOnRampFiatCurrency, //
} from '../../../components/buy-send-swap/select-currency/select-currency'
import WalletPageWrapper from '../../../components/desktop/wallet-page-wrapper/wallet-page-wrapper'
import { PageTitleHeader } from '../../../components/desktop/card-headers/page-title-header'
import {
  FilterTokenRow, //
} from '../../../components/desktop/views/portfolio/style'
import {
  NetworkFilterSelector, //
} from '../../../components/desktop/network-filter-selector'
import { BuyOptions } from '../../../options/buy-with-options'
import {
  makeFundWalletPurchaseOptionsRoute,
  makeAndroidFundWalletRoute,
} from '../../../utils/routes-utils'
import { networkSupportsAccount } from '../../../utils/network-utils'

interface Params {
  assetId: string
}

export const FundWalletScreen = () => {
  // render
  return (
    <Switch>
      <Route
        path={WalletRoutes.FundWalletPurchaseOptionsPage}
        exact
      >
        <PurchaseOptionSelection />
      </Route>

      <Route
        path={WalletRoutes.FundWalletPage}
        exact
      >
        <AssetSelection />
      </Route>

      <Redirect to={WalletRoutes.FundWalletPage} />
    </Switch>
  )
}

function AssetSelection() {
  // Selectors
  const isMobile = useSafeUISelector(UISelectors.isMobile)

  // routing
  const history = useHistory()
  const { assetId: selectedOnRampAssetId } = useParams<Params>()
  const params = new URLSearchParams(history.location.search)
  const currencyCode = params.get('currencyCode')
  const buyAmountParam = params.get('buyAmount')
  const searchParam = params.get('search')
  const chainIdParam = params.get('chainId')
  const coinTypeParam = params.get('coinType')

  // redux
  const isPanel = useSafeUISelector(UISelectors.isPanel)

  // state
  const [selectedCurrency, setSelectedCurrency] = React.useState<string>(
    currencyCode || 'USD',
  )
  const [searchValue, setSearchValue] = React.useState<string>(
    searchParam ?? '',
  )
  const [showFiatSelection, setShowFiatSelection] =
    React.useState<boolean>(false)
  const [buyAmount, setBuyAmount] = React.useState<string>(buyAmountParam || '')
  const [selectedNetworkFilter, setSelectedNetworkFilter] =
    React.useState<NetworkFilterType>(
      chainIdParam && coinTypeParam !== null
        ? {
            chainId: chainIdParam,
            coin: Number(coinTypeParam),
          }
        : AllNetworksOption,
    )

  // queries
  const { data: defaultFiatCurrency = 'USD' } = useGetDefaultFiatCurrencyQuery(
    undefined,
    {
      selectFromResult: (res) => ({
        data: res.data?.toUpperCase(),
      }),
    },
  )
  const { data: buyAssetNetworks = [] } = useGetOnRampNetworksQuery()
  const { data: selectedNetworkFromFilter = AllNetworksOption } =
    useGetNetworkQuery(
      !selectedNetworkFilter
        || selectedNetworkFilter.chainId === AllNetworksOption.chainId
        ? skipToken
        : selectedNetworkFilter,
    )
  const { data: onRampAssets } = useGetOnRampAssetsQuery()
  const selectedAsset = onRampAssets?.allAssetOptions.find(
    (opt) => getAssetIdKey(opt) === selectedOnRampAssetId,
  )

  const { data: options } = useGetOnRampAssetsQuery()

  // methods
  // This filters a list of assets when the user types in search bar
  const onSearchValueChange = React.useCallback(
    (event: React.ChangeEvent<HTMLInputElement>) => {
      setSearchValue(event.target.value)
    },
    [],
  )

  const renderToken: RenderTokenFunc<QoraiWallet.BlockchainToken> =
    React.useCallback(
      ({ item: asset, ref }) => {
        const assetId = getAssetIdKey(asset)
        return (
          <BuyAssetOptionItem
            selectedCurrency={selectedCurrency}
            key={assetId}
            token={asset}
            onClick={() => history.push(makeAndroidFundWalletRoute(assetId))}
            ref={ref}
          />
        )
      },
      [history, selectedCurrency],
    )

  // memos & computed
  const assetsForFilteredNetwork = React.useMemo(() => {
    if (!options?.allAssetOptions) {
      return []
    }

    const assets =
      selectedNetworkFilter.chainId === AllNetworksOption.chainId
        ? options.allAssetOptions
        : options.allAssetOptions.filter(
            ({ chainId }) => selectedNetworkFilter.chainId === chainId,
          )

    return assets
  }, [selectedNetworkFilter.chainId, options?.allAssetOptions])

  const assetListSearchResults = React.useMemo(() => {
    if (searchValue === '') {
      return assetsForFilteredNetwork
    }
    return assetsForFilteredNetwork.filter((asset) => {
      const searchValueLower = searchValue.toLowerCase()
      return (
        asset.name.toLowerCase().startsWith(searchValueLower)
        || asset.symbol.toLowerCase().startsWith(searchValueLower)
      )
    })
  }, [searchValue, assetsForFilteredNetwork])

  const assetsUI = React.useMemo(
    () =>
      options?.allAssetOptions?.length ? (
        <VirtualizedTokensList
          userAssetList={assetListSearchResults}
          selectedAssetId={selectedOnRampAssetId}
          renderToken={renderToken}
        />
      ) : (
        <Column>
          <LoadingIcon
            opacity={1}
            size='100px'
            color='interactive05'
          />
        </Column>
      ),
    [
      options?.allAssetOptions,
      assetListSearchResults,
      selectedOnRampAssetId,
      renderToken,
    ],
  )

  const networksFilterOptions: QoraiWallet.NetworkInfo[] = React.useMemo(() => {
    return [AllNetworksOption, ...buyAssetNetworks]
  }, [buyAssetNetworks])

  // computed
  const isNextStepEnabled = !!selectedAsset
  const pageTitle = `${getLocale('qoraiWalletBuy')}${
    selectedAsset ? ` ${selectedAsset.symbol}` : ''
  }`

  // effects
  React.useEffect(() => {
    // initialize selected currency
    if (defaultFiatCurrency) {
      setSelectedCurrency(defaultFiatCurrency)
    }
  }, [defaultFiatCurrency])

  // render
  if (showFiatSelection) {
    return (
      <WalletPageWrapper
        wrapContentInBox={true}
        hideNav={isMobile}
        hideHeader={isMobile}
        cardHeader={
          <PageTitleHeader
            title={pageTitle}
            onBack={() => setShowFiatSelection(false)}
          />
        }
      >
        <Column
          padding='0 12px'
          fullWidth
        >
          <SelectOnRampFiatCurrency
            onSelectCurrency={(currency) => {
              setSelectedCurrency(currency.currencyCode.toUpperCase())
              setShowFiatSelection(false)
            }}
            onBack={() => setShowFiatSelection(false)}
          />
        </Column>
      </WalletPageWrapper>
    )
  }

  return (
    <WalletPageWrapper
      wrapContentInBox={true}
      hideNav={isMobile}
      hideHeader={isMobile}
      useFullHeight={true}
      cardHeader={<PageTitleHeader title={pageTitle} />}
    >
      <StyledWrapper
        fullWidth={true}
        justifyContent='flex-start'
      >
        <SelectAssetWrapper
          fullWidth={true}
          fullHeight={true}
          justifyContent='flex-start'
        >
          <Row
            marginBottom={8}
            padding='0 12px'
          >
            <BuyAmountInput
              onAmountChange={setBuyAmount}
              buyAmount={buyAmount}
              selectedAsset={selectedAsset}
              autoFocus={true}
              onShowCurrencySelection={() => setShowFiatSelection(true)}
              selectedFiatCurrencyCode={selectedCurrency}
            />
          </Row>

          <FilterTokenRow
            horizontalPadding={12}
            isV2={false}
          >
            <Column
              flex={1}
              style={{ minWidth: '25%' }}
              alignItems='flex-start'
            >
              <SearchBar
                placeholder={getLocale('qoraiWalletSearchText')}
                action={onSearchValueChange}
                value={searchValue}
                isV2={false}
              />
            </Column>
            <NetworkFilterSelector
              isV2={false}
              networkListSubset={networksFilterOptions}
              selectedNetwork={selectedNetworkFromFilter}
              onSelectNetwork={setSelectedNetworkFilter}
              dropdownPosition='right'
            />
          </FilterTokenRow>

          <TokenListWrapper
            fullWidth={true}
            justifyContent='flex-start'
          >
            {assetsUI}
          </TokenListWrapper>
        </SelectAssetWrapper>
        <Row
          width='unset'
          padding='20px 0px 0px 0px'
        >
          <QoraSquaredButton
            size={isPanel ? 'medium' : 'large'}
            onClick={() => {
              if (!selectedOnRampAssetId) {
                return
              }

              const searchValueLower = searchValue.toLowerCase()

              // save latest form values in router history
              history.replace(
                makeAndroidFundWalletRoute(selectedOnRampAssetId, {
                  currencyCode: selectedCurrency,
                  buyAmount,
                  // save latest search-box value (if it matches selection name
                  // or symbol)
                  searchText:
                    searchValue
                    && (selectedAsset?.name
                      .toLowerCase()
                      .startsWith(searchValueLower)
                      || selectedAsset?.symbol
                        .toLowerCase()
                        .startsWith(searchValueLower))
                      ? searchValue
                      : undefined,
                  // saving network filter (if it matches selection)
                  chainId:
                    selectedAsset?.chainId === selectedNetworkFilter.chainId
                      ? selectedNetworkFilter.chainId
                        || AllNetworksOption.chainId
                      : AllNetworksOption.chainId,
                  coinType:
                    selectedAsset?.coin === selectedNetworkFilter.coin
                      ? selectedNetworkFilter.coin.toString()
                        || AllNetworksOption.coin.toString()
                      : AllNetworksOption.coin.toString(),
                }),
              )

              // go to payment option selection
              history.push(
                makeFundWalletPurchaseOptionsRoute(selectedOnRampAssetId, {
                  buyAmount: buyAmount || '0',
                  currencyCode: selectedCurrency,
                }),
              )
            }}
            isDisabled={!isNextStepEnabled}
          >
            {selectedAsset
              ? getLocale('qoraiWalletBuyContinueButton')
              : getLocale('qoraiWalletBuySelectAsset')}
          </QoraSquaredButton>
        </Row>
      </StyledWrapper>
    </WalletPageWrapper>
  )
}

function PurchaseOptionSelection() {
  // Selectors
  const isMobile = useSafeUISelector(UISelectors.isMobile)

  // routing
  const history = useHistory()
  const { assetId: selectedOnRampAssetId } = useParams<Params>()
  const params = new URLSearchParams(history.location.search)
  const currencyCodeParam = params.get('currencyCode')
  const buyAmountParam = params.get('buyAmount')

  // queries
  const { accounts } = useAccountsQuery()
  const { data: fiatCurrencies = [] } = useGetOnRampFiatCurrenciesQuery()
  const selectedCurrency = fiatCurrencies.find(
    (c) => c.currencyCode === currencyCodeParam,
  )
  const currencyCode = selectedCurrency ? selectedCurrency.currencyCode : 'USD'

  const { data: options } = useGetOnRampAssetsQuery()
  const selectedAsset = options?.allAssetOptions.find(
    (opt) => getAssetIdKey(opt) === selectedOnRampAssetId,
  )

  const { data: assetNetwork } = useGetNetworkQuery(selectedAsset || skipToken)

  const [getBuyUrl] = useLazyGetBuyUrlQuery()

  const accountsForSelectedAssetNetwork = React.useMemo(() => {
    if (!assetNetwork) {
      return []
    }
    return accounts.filter((a) =>
      networkSupportsAccount(assetNetwork, a.accountId),
    )
  }, [assetNetwork, accounts])

  // state
  const [showAccountSearch, setShowAccountSearch] =
    React.useState<boolean>(false)
  const [accountSearchText, setAccountSearchText] = React.useState<string>('')
  const [selectedAccount, setSelectedAccount] = React.useState<
    QoraiWallet.AccountInfo | undefined
  >(accountsForSelectedAssetNetwork[0])

  // state-dependant queries
  const { receiveAddress: generatedAddress } = useReceiveAddressQuery(
    selectedAccount?.accountId,
  )

  const { data: buyWithStripeUrl } = useGetBuyUrlQuery(
    selectedAsset && assetNetwork && generatedAddress
      ? {
          assetSymbol: selectedAsset.symbol.toLowerCase(),
          onRampProvider: QoraiWallet.OnRampProvider.kStripe,
          chainId: assetNetwork.chainId,
          address: generatedAddress,
          amount: buyAmountParam || '0',
          currencyCode: currencyCode.toLowerCase(),
        }
      : skipToken,
  )

  // memos
  const accountListSearchResults = React.useMemo(() => {
    if (accountSearchText === '') {
      return accountsForSelectedAssetNetwork
    }

    return accountsForSelectedAssetNetwork.filter((item) => {
      return item.name.toLowerCase().startsWith(accountSearchText.toLowerCase())
    })
  }, [accountSearchText, accountsForSelectedAssetNetwork])

  const onRampAssetMap = React.useMemo(() => {
    if (!options) {
      return undefined
    }

    return {
      [QoraiWallet.OnRampProvider.kRamp]: options.rampAssetOptions,
      [QoraiWallet.OnRampProvider.kTransak]: options.transakAssetOptions,
      [QoraiWallet.OnRampProvider.kStripe]: options.stripeAssetOptions,
      [QoraiWallet.OnRampProvider.kCoinbase]: options.coinbaseAssetOptions,
    }
  }, [options])

  const selectedAssetBuyOptions: BuyOption[] = React.useMemo(() => {
    if (!onRampAssetMap) {
      return []
    }

    return selectedAsset
      ? BuyOptions.filter((buyOption) =>
          isSelectedAssetInAssetOptions(
            selectedAsset,
            onRampAssetMap[buyOption.id],
          ),
        )
          .filter((buyOption) => {
            if (buyOption.id === QoraiWallet.OnRampProvider.kStripe) {
              // hide the option if Stripe URL could not be created
              return buyWithStripeUrl
            }
            return true
          })
          .sort((optionA, optionB) => optionA.name.localeCompare(optionB.name))
      : []
  }, [selectedAsset, onRampAssetMap, buyWithStripeUrl])

  // computed
  const needsAccount: boolean =
    !!selectedAsset && accountsForSelectedAssetNetwork.length < 1

  const pageTitle = selectedAsset
    ? `${getLocale('qoraiWalletBuy')} ${selectedAsset.symbol}`
    : getLocale('qoraiWalletBuy')

  // methods
  const openAccountSearch = React.useCallback(
    () => setShowAccountSearch(true),
    [],
  )
  const closeAccountSearch = React.useCallback(
    () => setShowAccountSearch(false),
    [],
  )
  const onSearchTextChanged = React.useCallback(
    (e: React.ChangeEvent<HTMLInputElement>) =>
      setAccountSearchText(e.target.value),
    [],
  )

  const onSelectAccountFromSearch = React.useCallback(
    (account: QoraiWallet.AccountInfo) => {
      closeAccountSearch()
      setSelectedAccount(account)
    },
    [closeAccountSearch],
  )

  const openBuyAssetLink = React.useCallback(
    async (buyOption: QoraiWallet.OnRampProvider) => {
      if (!selectedAsset || !assetNetwork || !generatedAddress) {
        return
      }

      try {
        const url = await getBuyUrl({
          assetSymbol:
            buyOption === QoraiWallet.OnRampProvider.kRamp
              ? getRampAssetSymbol(selectedAsset)
              : buyOption === QoraiWallet.OnRampProvider.kStripe
                ? selectedAsset.symbol.toLowerCase()
                : selectedAsset.symbol,
          onRampProvider: buyOption,
          chainId: assetNetwork.chainId,
          address: generatedAddress,
          amount: buyAmountParam || '0',
          currencyCode:
            buyOption === QoraiWallet.OnRampProvider.kStripe
              ? currencyCode.toLowerCase()
              : currencyCode,
        }).unwrap()

        if (url && chrome.tabs !== undefined) {
          chrome.tabs.create({ url }, () => {
            if (chrome.runtime.lastError) {
              console.error(
                'tabs.create failed: ' + chrome.runtime.lastError.message,
              )
            }
          })
        } else {
          // Tabs.create is desktop specific. Using window.open for android.
          window.open(url, '_blank', 'noopener')
        }
      } catch (error) {
        console.error(error)
      }
    },
    [
      buyAmountParam,
      selectedAsset,
      assetNetwork,
      getBuyUrl,
      currencyCode,
      generatedAddress,
    ],
  )

  // effects
  React.useEffect(() => {
    // force selected account option state
    setSelectedAccount(accountsForSelectedAssetNetwork[0])
  }, [accountsForSelectedAssetNetwork])

  // render
  if (!selectedOnRampAssetId) {
    return <Redirect to={WalletRoutes.FundWalletPageStart} />
  }

  return (
    <WalletPageWrapper
      wrapContentInBox={true}
      hideNav={isMobile}
      hideHeader={isMobile}
      cardHeader={
        <PageTitleHeader
          title={pageTitle}
          onBack={history.goBack}
        />
      }
    >
      <Column
        padding='0 12px'
        fullWidth
      >
        {needsAccount && assetNetwork ? (
          // Creates wallet Account if needed
          <CreateAccountTab
            network={assetNetwork}
            onCancel={history.goBack}
            onCreated={setSelectedAccount}
          />
        ) : showAccountSearch || !selectedAccount ? (
          <SearchWrapper>
            <SelectHeader
              title={getLocale('qoraiWalletSelectAccount')}
              onBack={closeAccountSearch}
              hasAddButton={false}
            />
            <SearchBar
              placeholder={getLocale('qoraiWalletSearchAccount')}
              action={onSearchTextChanged}
              isV2={true}
            />
            <VerticalSpace space='16px' />

            <ScrollContainer>
              <SelectAccount
                accounts={accountListSearchResults}
                selectedAccount={selectedAccount}
                onSelectAccount={onSelectAccountFromSearch}
              />
            </ScrollContainer>
          </SearchWrapper>
        ) : (
          // Buy Option selection & Account selection/search
          <>
            <Title>
              {getLocale('qoraiWalletFundWalletTitle').replace(
                '$1',
                selectedAsset?.symbol ?? '',
              )}
            </Title>

            <Description>
              {getLocale('qoraiWalletFundWalletDescription')}
            </Description>

            <VerticalSpace space='16px' />

            <Row
              justifyContent='space-around'
              alignItems='center'
            >
              <Flex>
                <SelectAccountItem
                  selectedNetwork={assetNetwork}
                  account={selectedAccount}
                  onSelectAccount={openAccountSearch}
                  showTooltips
                  showSwitchAccountsIcon
                  isV2={true}
                />
              </Flex>
            </Row>

            <VerticalSpace space='6px' />
            <Divider />

            <SelectBuyOption
              layoutType='loose'
              buyOptions={selectedAssetBuyOptions}
              onSelect={openBuyAssetLink}
              selectedOption={undefined}
            />

            <Alert>
              <InfoIcon name='info-filled' />
              <AlertText>{getLocale('qoraiWalletBuyDisclaimer')}</AlertText>
            </Alert>
          </>
        )}
      </Column>
    </WalletPageWrapper>
  )
}

export default FundWalletScreen
