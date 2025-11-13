// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// Types
import { QoraiWallet, SupportedOnRampNetworks } from '../../../constants/types'
import { WalletApiEndpointBuilderParams } from '../api-base.slice'

// Utils
import {
  addLogoToToken,
  getUniqueAssets,
  sortNativeAndAndQorAssetsToTop,
} from '../../../utils/asset-utils'
import { mapLimit } from 'async'
import { handleEndpointError } from '../../../utils/api-utils'

export const onRampEndpoints = ({ query }: WalletApiEndpointBuilderParams) => {
  return {
    getOnRampAssets: query<
      {
        rampAssetOptions: QoraiWallet.BlockchainToken[]
        transakAssetOptions: QoraiWallet.BlockchainToken[]
        stripeAssetOptions: QoraiWallet.BlockchainToken[]
        coinbaseAssetOptions: QoraiWallet.BlockchainToken[]
        allAssetOptions: QoraiWallet.BlockchainToken[]
      },
      void
    >({
      queryFn: async (_arg, _store, _extraOptions, baseQuery) => {
        try {
          const {
            data: { blockchainRegistry },
            cache,
          } = baseQuery(undefined)
          const { kRamp, kTransak, kStripe, kCoinbase } =
            QoraiWallet.OnRampProvider

          const rampAssets = await mapLimit(
            SupportedOnRampNetworks,
            10,
            async (chainId: string) =>
              await blockchainRegistry.getBuyTokens(kRamp, chainId),
          )

          const transakAssets = await mapLimit(
            SupportedOnRampNetworks,
            10,
            async (chainId: string) =>
              await blockchainRegistry.getBuyTokens(kTransak, chainId),
          )
          const stripeAssets = await mapLimit(
            SupportedOnRampNetworks,
            10,
            async (chainId: string) =>
              await blockchainRegistry.getBuyTokens(kStripe, chainId),
          )

          const coinbaseAssets = await mapLimit(
            SupportedOnRampNetworks,
            10,
            async (chainId: string) =>
              await blockchainRegistry.getBuyTokens(kCoinbase, chainId),
          )

          const updateLogo = async (token: QoraiWallet.BlockchainToken) => {
            const tokenLogo = await cache.getTokenLogo(token)
            return addLogoToToken(token, tokenLogo)
          }

          // add token logos
          const rampAssetOptions: QoraiWallet.BlockchainToken[] =
            await mapLimit(
              rampAssets.flatMap((p) => p.tokens),
              10,
              updateLogo,
            )

          const transakAssetOptions: QoraiWallet.BlockchainToken[] =
            await mapLimit(
              transakAssets.flatMap((p) => p.tokens),
              10,
              updateLogo,
            )

          const stripeAssetOptions: QoraiWallet.BlockchainToken[] =
            await mapLimit(
              stripeAssets.flatMap((p) => p.tokens),
              10,
              updateLogo,
            )

          const coinbaseAssetOptions: QoraiWallet.BlockchainToken[] =
            await mapLimit(
              coinbaseAssets.flatMap((p) => p.tokens),
              10,
              updateLogo,
            )

          // sort lists
          // Move Gas coins and QOR to front of list
          const sortedRampOptions =
            sortNativeAndAndQorAssetsToTop(rampAssetOptions)
          const sortedTransakOptions =
            sortNativeAndAndQorAssetsToTop(transakAssetOptions)
          const sortedStripeOptions =
            sortNativeAndAndQorAssetsToTop(stripeAssetOptions)
          const sortedCoinbaseOptions =
            sortNativeAndAndQorAssetsToTop(coinbaseAssetOptions)

          const results = {
            rampAssetOptions: sortedRampOptions,
            transakAssetOptions: sortedTransakOptions,
            stripeAssetOptions: sortedStripeOptions,
            coinbaseAssetOptions: sortedCoinbaseOptions,
            allAssetOptions: sortNativeAndAndQorAssetsToTop(
              getUniqueAssets(
                sortedRampOptions.concat(
                  sortedTransakOptions,
                  sortedStripeOptions,
                ),
              ),
            ),
          }

          return {
            data: results,
          }
        } catch (error) {
          const errorMessage = `Unable to fetch onRamp assets: ${error}`
          console.log(errorMessage)
          return {
            error: errorMessage,
          }
        }
      },
      providesTags: (_results, error, _arg) => {
        if (error) {
          return ['UNKNOWN_ERROR']
        }
        return ['OnRampAssets']
      },
    }),

    getOnRampFiatCurrencies: query<QoraiWallet.OnRampCurrency[], void>({
      queryFn: async (_arg, { endpoint }, _extraOptions, baseQuery) => {
        try {
          const { data: api } = baseQuery(undefined)
          const { currencies } =
            await api.blockchainRegistry.getOnRampCurrencies()
          if (!currencies.length) {
            throw new Error('No currencies found')
          }
          return {
            data: currencies,
          }
        } catch (error) {
          return handleEndpointError(
            endpoint,
            'Failed to fetch on-ramp fiat currencies',
            error,
          )
        }
      },
    }),

    getBuyUrl: query<
      string,
      {
        onRampProvider: QoraiWallet.OnRampProvider
        chainId: string
        address: string
        assetSymbol: string
        amount: string
        currencyCode: string
      }
    >({
      queryFn: async (arg, { endpoint }, extraOptions, baseQuery) => {
        try {
          const { data: api } = baseQuery(undefined)
          const { url, error } = await api.assetRatioService.getBuyUrlV1(
            arg.onRampProvider,
            arg.chainId,
            arg.address,
            arg.assetSymbol,
            arg.amount,
            arg.currencyCode,
          )

          if (error) {
            throw new Error(error)
          }

          return {
            data: url,
          }
        } catch (error) {
          return handleEndpointError(
            endpoint,
            `Failed to get ${getRampProviderName(
              arg.onRampProvider,
            )} buy URL for: ${JSON.stringify(arg, undefined, 2)}`,
            error,
          )
        }
      },
    }),
  }
}

// internals
function getRampProviderName(onRampProvider: QoraiWallet.OnRampProvider) {
  return Object.keys(QoraiWallet.OnRampProvider)
    .find(
      (key: keyof typeof QoraiWallet.OnRampProvider) =>
        QoraiWallet.OnRampProvider[key] === onRampProvider,
    )
    ?.substring(1)
}
