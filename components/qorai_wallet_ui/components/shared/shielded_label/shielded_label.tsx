// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import Label from '@qorai/qora/react/label'
import Icon from '@qorai/qora/react/icon'

// Utils
import { getLocale } from '../../../../common/locale'

export const ShieldedLabel = () => {
  return (
    <Label color='neutral'>
      <div slot='icon-before'>
        <Icon name='shield-done' />
      </div>
      {getLocale('qoraiWalletShielded')}
    </Label>
  )
}
