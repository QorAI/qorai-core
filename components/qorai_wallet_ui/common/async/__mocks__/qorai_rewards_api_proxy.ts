// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { QoraiRewardsProxyOverrides } from '../../../constants/testing_types'
import type { QoraiRewardsProxyInstance } from '../qorai_rewards_api_proxy'

export class MockQoraiRewardsProxy {
  overrides: QoraiRewardsProxyOverrides = {
    rewardsEnabled: true,
    balance: 100.5,
    externalWallet: null,
  }

  applyOverrides = (overrides?: QoraiRewardsProxyOverrides) => {
    if (!overrides) {
      return
    }

    this.overrides = { ...this.overrides, ...overrides }
  }

  getRewardsEnabled = async () => {
    return this.overrides.rewardsEnabled
  }

  fetchBalance = async () => {
    return this.overrides.balance
  }

  getExternalWallet = async () => {
    return this.overrides.externalWallet
  }
}

export type MockQoraiRewardsProxyInstance = InstanceType<
  typeof MockQoraiRewardsProxy
>

let qoraiRewardsProxyInstance: MockQoraiRewardsProxyInstance

export const getQoraiRewardsProxy = () => {
  if (!qoraiRewardsProxyInstance) {
    qoraiRewardsProxyInstance = new MockQoraiRewardsProxy()
  }

  return qoraiRewardsProxyInstance as unknown as QoraiRewardsProxyInstance
    & MockQoraiRewardsProxy
}

export function resetRewardsProxy(
  overrides?: QoraiRewardsProxyOverrides | undefined,
) {
  qoraiRewardsProxyInstance = new MockQoraiRewardsProxy()
  qoraiRewardsProxyInstance.applyOverrides(overrides)
}
