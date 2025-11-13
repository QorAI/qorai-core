// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// Types
import { QoraiWallet, DAppPermissionDurationOption } from '../constants/types'

export const DAppPermissionDurationOptions: DAppPermissionDurationOption[] = [
  {
    name: 'qoraiWalletPermissionUntilClose',
    id: QoraiWallet.PermissionLifetimeOption.kPageClosed,
  },
  {
    name: 'qoraiWalletPermissionOneDay',
    id: QoraiWallet.PermissionLifetimeOption.k24Hours,
  },
  {
    name: 'qoraiWalletPermissionOneWeek',
    id: QoraiWallet.PermissionLifetimeOption.k7Days,
  },
  {
    name: 'qoraiWalletPermissionForever',
    id: QoraiWallet.PermissionLifetimeOption.kForever,
  },
]
