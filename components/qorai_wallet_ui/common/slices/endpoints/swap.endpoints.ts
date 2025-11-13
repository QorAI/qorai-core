// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// types
import { QoraiWallet } from '../../../constants/types'
import { WalletApiEndpointBuilderParams } from '../api-base.slice'

// utils
import { handleEndpointError } from '../../../utils/api-utils'

export const swapEndpoints = ({
  mutation,
  query,
}: WalletApiEndpointBuilderParams) => {
  return {
    generateSwapQuote: mutation<
      {
        response: QoraiWallet.SwapQuoteUnion | null
        fees: QoraiWallet.SwapFees | null
        error: QoraiWallet.SwapErrorUnion | null
        errorString: string
      },
      QoraiWallet.SwapQuoteParams
    >({
      queryFn: async (params, { endpoint }, extraOptions, baseQuery) => {
        const { swapService } = baseQuery(undefined).data
        try {
          const result = await swapService.getQuote(params)

          if (result.errorString) {
            console.log(`generateSwapQuote API error: ${result.errorString}`)
          }

          return {
            data: result,
          }
        } catch (error) {
          return handleEndpointError(
            endpoint,
            'Unable to generate Qorai Swap quote',
            error,
          )
        }
      },
    }),

    generateSwapTransaction: mutation<
      {
        response: QoraiWallet.SwapTransactionUnion | null
        error: QoraiWallet.SwapErrorUnion | null
        errorString: string
      },
      QoraiWallet.SwapTransactionParamsUnion
    >({
      queryFn: async (params, { endpoint }, extraOptions, baseQuery) => {
        const { swapService } = baseQuery(undefined).data
        try {
          const result = await swapService.getTransaction(params)
          return {
            data: result,
          }
        } catch (error) {
          return handleEndpointError(
            endpoint,
            'Unable to generate Qorai Swap transaction',
            error,
          )
        }
      },
    }),
  }
}
