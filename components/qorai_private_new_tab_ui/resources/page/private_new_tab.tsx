// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { createRoot } from 'react-dom/client'
import { initLocale } from 'qorai-ui'

import { loadTimeData } from '../../../common/loadTimeData'
import QoraiCoreThemeProvider from '../../../common/QoraiCoreThemeProvider'
import Container from './container'

function App () {
  return (
    <QoraiCoreThemeProvider>
      <Container />
    </QoraiCoreThemeProvider>
  )
}

function initialize () {
  initLocale(loadTimeData.data_)
  const root = createRoot(document.getElementById('mountPoint')!)
  root.render(<App />)
}

document.addEventListener('DOMContentLoaded', initialize)
