// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// types
import { QoraiWallet } from '../../../constants/types'
import { WalletApiEndpointBuilderParams } from '../api-base.slice'

// utils
import { handleEndpointError } from '../../../utils/api-utils'

export const transactionSimulationEndpoints = ({
  mutation,
  query,
}: WalletApiEndpointBuilderParams) => {
  return {
    getIsTxSimulationOptInStatus: query<QoraiWallet.BlowfishOptInStatus, void>({
      queryFn: async (arg, { endpoint }, extraOptions, baseQuery) => {
        const { data: api, cache } = baseQuery(undefined)

        const { isTransactionSimulationsFeatureEnabled } =
          await cache.getWalletInfo()

        if (!isTransactionSimulationsFeatureEnabled) {
          return {
            data: QoraiWallet.BlowfishOptInStatus.kDenied,
          }
        }

        const { status } =
          await api.qoraiWalletService.getTransactionSimulationOptInStatus()

        return {
          data: status,
        }
      },
      providesTags: ['TransactionSimulationsOptIn'],
    }),

    setIsTxSimulationOptInStatus: mutation<
      QoraiWallet.BlowfishOptInStatus,
      QoraiWallet.BlowfishOptInStatus
    >({
      queryFn: async (status, { endpoint }, extraOptions, baseQuery) => {
        const { data: api, cache } = baseQuery(undefined)
        api.qoraiWalletService.setTransactionSimulationOptInStatus(status)
        cache.clearWalletInfo()
        return {
          data: status,
        }
      },
      invalidatesTags: ['TransactionSimulationsOptIn'],
    }),

    getHasTransactionSimulationSupport: query<boolean, QoraiWallet.ChainId>({
      queryFn: async (chainId, { endpoint }, extraOptions, baseQuery) => {
        try {
          const { data: api } = baseQuery(undefined)
          const { result } =
            await api.simulationService.hasTransactionScanSupport(chainId)
          return {
            data: result,
          }
        } catch (error) {
          return handleEndpointError(
            endpoint,
            `Unable to check if this network (${
              chainId //
            }) has transaction simulation support`,
            error,
          )
        }
      },
    }),

    getEVMTransactionSimulation: query<
      QoraiWallet.EVMSimulationResponse,
      {
        txMetaId: string
      }
    >({
      queryFn: async (txArg, { endpoint }, extraOptions, baseQuery) => {
        try {
          const { data: api } = baseQuery(undefined)
          const { simulationService } = api

          const { errorResponse, errorString, response } =
            await simulationService.scanEVMTransaction(
              txArg.txMetaId,
              navigator.language,
            )

          if (errorResponse || errorString) {
            throw new Error(
              `EVM Transaction Simulation error for tx: ${
                txArg.txMetaId //
              } -- ${
                errorString //
              } -- ${errorResponse}`,
            )
          }

          if (!response) {
            throw new Error('empty EVM simulation response')
          }

          return {
            data: response,
          }
        } catch (error) {
          return handleEndpointError(
            endpoint,
            'Failed to simulate EVM transaction',
            error,
          )
        }
      },
    }),

    getSolanaTransactionSimulation: query<
      QoraiWallet.SolanaSimulationResponse,
      {
        txMetaId: string
      }
    >({
      queryFn: async (arg, { endpoint }, extraOptions, baseQuery) => {
        try {
          const { data: api } = baseQuery(undefined)
          const { simulationService } = api

          const { errorResponse, errorString, response } =
            await simulationService.scanSolanaTransaction(
              arg.txMetaId,
              navigator.language,
            )

          if (errorResponse || errorString) {
            throw new Error(
              `getSolanaTransactionSimulation({${
                arg.txMetaId //
              }}) failed -- ${errorString}: ${errorResponse}`,
            )
          }

          if (!response) {
            throw new Error('empty Solana simulation response')
          }

          return {
            data: response,
          }
        } catch (error) {
          return handleEndpointError(
            endpoint,
            'Failed to simulate Solana transaction',
            error,
          )
        }
      },
    }),

    getSolanaSignTransactionsRequestSimulation: query<
      QoraiWallet.SolanaSimulationResponse,
      {
        signSolTransactionsRequestId: number
      }
    >({
      queryFn: async (arg, { endpoint }, extraOptions, baseQuery) => {
        try {
          const { data: api } = baseQuery(undefined)
          const { simulationService } = api

          const { errorResponse, errorString, response } =
            await simulationService.scanSignSolTransactionsRequest(
              arg.signSolTransactionsRequestId,
              navigator.language,
            )

          if (errorResponse || errorString) {
            throw new Error(
              `getSolanaSignTransactionsRequestSimulation({${
                arg.signSolTransactionsRequestId //
              }}) failed -- ${errorString}: ${errorResponse}`,
            )
          }

          if (!response) {
            throw new Error('empty Solana simulation response')
          }

          return {
            data: response,
          }
        } catch (error) {
          return handleEndpointError(
            endpoint,
            'Failed to simulate Solana transaction',
            error,
          )
        }
      },
    }),
  }
}
