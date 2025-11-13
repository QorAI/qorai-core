// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// Types
import { GasFeeOption } from '../constants/types'

export const gasFeeOptions: GasFeeOption[] = [
  {
    id: 'slow',
    name: 'qoraiSwapSlow',
  },
  {
    id: 'average',
    name: 'qoraiSwapAverage',
  },
  {
    id: 'fast',
    name: 'qoraiSwapFast',
  },
]
