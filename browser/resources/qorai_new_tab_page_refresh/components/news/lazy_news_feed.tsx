/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import { useQoraiNews } from '../../../../../components/qorai_news/browser/resources/shared/Context'
import { useNewTabState } from '../../context/new_tab_context'

import { style } from './lazy_news_feed.style'

const NewsFeed = React.lazy(() => import('./news_feed'))

export function LazyNewsFeed() {
  const qoraiNews = useQoraiNews()
  const newsFeatureEnabled = useNewTabState((s) => s.newsFeatureEnabled)
  const newsVisible = qoraiNews.isShowOnNTPPrefEnabled
  const renderNews =
    newsFeatureEnabled && (newsVisible || qoraiNews.customizePage)

  if (!renderNews) {
    return null
  }

  return (
    <div data-css-scope={style.scope}>
      <React.Suspense fallback={newsVisible && <div className='loading' />}>
        <NewsFeed />
      </React.Suspense>
    </div>
  )
}
