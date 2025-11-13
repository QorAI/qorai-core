// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { createRoot } from 'react-dom/client'
import { setIconBasePath } from '@qorai/qora/react/icon'
import App from './App'

setIconBasePath('//resources/qorai-icons')

createRoot(document.querySelector('#root')!).render(
  <App />
)
