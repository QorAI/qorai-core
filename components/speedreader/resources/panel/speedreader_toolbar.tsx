// Copyright (c) 2022 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { render } from 'react-dom'
import { initLocale } from 'qorai-ui'
import { ToolbarWrapperStyles } from './style'

import { loadTimeData } from '../../../common/loadTimeData'
import QorAICoreThemeProvider from '../../../common/QorAICoreThemeProvider'
import Toolbar from './components/toolbar'

import { setIconBasePath } from '@qorai/qora/react/icon'

setIconBasePath('//resources/qorai-icons')

function App () {
  return (
    <QorAICoreThemeProvider>
      <ToolbarWrapperStyles>
        <Toolbar />
      </ToolbarWrapperStyles>
    </QorAICoreThemeProvider>
  )
}

function initialize () {
  initLocale(loadTimeData.data_)
  render(<App />, document.getElementById('mountPoint'))
}

document.addEventListener('DOMContentLoaded', initialize)
