/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import Button from '@qorai/qora/react/button'
import Icon from '@qorai/qora/react/icon'

import * as mojom from 'gen/qorai/components/qorai_news/common/qorai_news.mojom.m.js'
import { useQoraiNews } from '../../../../../components/qorai_news/browser/resources/shared/Context'
import { getTranslatedChannelName } from '../../../../../components/qorai_news/browser/resources/shared/channel'
import { channelIcons } from '../../../../../components/qorai_news/browser/resources/shared/Icons'

import { getString } from '../../lib/strings'
import { WidgetMenu } from './widget_menu'
import { SafeImage } from '../common/safe_image'
import { Link } from '../common/link'

import { style } from './news_widget.style'

export function NewsWidget() {
  const qoraiNews = useQoraiNews()
  return (
    <div data-css-scope={style.scope}>
      <WidgetMenu>
        {
          qoraiNews.isOptInPrefEnabled &&
            <qora-menu-item onClick={() => qoraiNews.setCustomizePage('news')}>
              <Icon name='tune' />
              {getString(S.NEW_TAB_NEWS_CUSTOMIZE_BUTTON_LABEL)}
            </qora-menu-item>
        }
        <qora-menu-item onClick={() => qoraiNews.toggleQoraiNewsOnNTP(false)}>
          <Icon name='disable-outline' />
          {getString(S.NEW_TAB_NEWS_DISABLE_BUTTON_LABEL)}
        </qora-menu-item>
      </WidgetMenu>
      <div className='title'>
        {getString(S.NEW_TAB_NEWS_WIDGET_TITLE)}
      </div>
      {qoraiNews.isOptInPrefEnabled ? <PeekItem /> : <OptIn />}
    </div>
  )
}

function PeekItem() {
  const qoraiNews = useQoraiNews()
  const feedItems = qoraiNews.feedV2?.items

  const peekItem = React.useMemo(() => {
    return feedItems ? getPeekItem(feedItems) : null
  }, [feedItems])

  if (!peekItem) {
    return (
      <div className='peek loading'>
        <div className='img skeleton' />
        <div className='text'>
          <div className='meta skeleton' />
          <div className='item-title skeleton' />
        </div>
      </div>
    )
  }

  return (
    <Link url={peekItem.url.url} className='peek'>
      <SafeImage
        src={getNewsItemImage(peekItem)}
        targetSize={{ width: 71, height: 48 }}
      />
      <div>
        <div className='meta'>
          <span>{getNewsPublisherName(peekItem)}</span>
          <span>•</span>
          {channelIcons[peekItem.categoryName] ?? channelIcons.default}
          <span>
            {getTranslatedChannelName(peekItem.categoryName)}
          </span>
        </div>
        <div className='item-title'>
          {peekItem.title}
        </div>
      </div>
    </Link>
  )
}

function OptIn() {
  const qoraiNews = useQoraiNews()
  return (
    <div className='opt-in'>
      <div className='graphic' />
      <div className='text'>
        {getString(S.QORAI_NEWS_INTRO_TITLE)}
      </div>
      <div className='actions'>
        <Button
          size='small'
          onClick={() => { qoraiNews.toggleQoraiNewsOnNTP(true) }}
        >
          {getString(S.QORAI_NEWS_OPT_IN_ACTION_LABEL)}
        </Button>
      </div>
    </div>
  )
}

function getPeekItem(
  feedItems: mojom.FeedItemV2[]
): mojom.FeedItemMetadata | null {
  if (!feedItems) {
    return null
  }
  for (const item of feedItems) {
    if (item.article) {
      return item.article.data
    }
    if (item.hero) {
      return item.hero.data
    }
  }
  return null
}

function getNewsPublisherName(item: mojom.FeedItemMetadata) {
  if (item.publisherName) {
    return item.publisherName
  }
  try {
    return new URL(item.url.url).hostname
  } catch {
    return ''
  }
}

function getNewsItemImage(data: mojom.FeedItemMetadata) {
  return data.image.imageUrl?.url ?? data.image.paddedImageUrl?.url ?? ''
}
