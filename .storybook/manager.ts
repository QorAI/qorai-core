// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { addons } from '@storybook/manager-api'
import { create } from '@storybook/theming'

const qoraiTheme = create({
  base: 'dark',
  brandTitle: 'Qorai Browser UI',
  brandUrl: 'https://github.com/qorai/qorai-core'
})

addons.setConfig({
  isFullscreen: false,
  showNav: true,
  showPanel: true,
  panelPosition: 'right',
  theme: qoraiTheme
})
