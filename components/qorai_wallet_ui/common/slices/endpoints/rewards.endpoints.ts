// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// types
import { WalletApiEndpointBuilderParams } from '../api-base.slice'
import { QoraiRewardsInfo } from '../../../constants/types'

// utils
import { handleEndpointError } from '../../../utils/api-utils'

export function qoraiRewardsApiEndpoints({
  mutation,
  query,
}: WalletApiEndpointBuilderParams) {
  return {
    getRewardsInfo: query<QoraiRewardsInfo, void>({
      queryFn: async (arg, { endpoint }, extraOptions, baseQuery) => {
        try {
          const { cache } = baseQuery(undefined)
          return {
            data: cache.rewardsInfo || (await cache.getQoraiRewardsInfo()),
          }
        } catch (error) {
          return handleEndpointError(
            endpoint,
            'Failed to get Qorai Rewards information',
            error,
          )
        }
      },
      providesTags: ['QoraiRewards-Info'],
    }),
  } as const
}
