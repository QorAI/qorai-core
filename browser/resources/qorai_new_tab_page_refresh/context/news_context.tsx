/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import { QoraiNewsContextProvider } from '../../../../components/qorai_news/browser/resources/shared/Context'
import { useNewTabState } from './new_tab_context'

export function NewsProvider(props: { children: React.ReactNode }) {
  const newsFeatureEnabled = useNewTabState((s) => s.newsFeatureEnabled)
  if (!newsFeatureEnabled) {
    return <>{props.children}</>
  }
  return (
    <QoraiNewsContextProvider>
      {props.children}
    </QoraiNewsContextProvider>
  )
}
