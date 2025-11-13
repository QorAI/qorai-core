// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import getQoraiNewsController, * as QoraiNews from '../../qorai_news/browser/resources/shared/api'
import { addFeedListener } from '../../qorai_news/browser/resources/shared/feedListener'
import AsyncActionHandler from '../../common/AsyncActionHandler'
import * as Actions from '../actions/today_actions'
import { ApplicationState } from '../reducers'
import store from '../store'

addFeedListener((hash) => {
  const current = store.getState().today.feed?.hash
  store.dispatch(Actions.isUpdateAvailable({ isUpdateAvailable: current !== hash }))
})

function storeInHistoryState (data: Object) {
  const oldHistoryState =
    typeof history.state === 'object' ? history.state : {}
  const newHistoryState = { ...oldHistoryState, ...data }
  history.pushState(newHistoryState, document.title)
}

const handler = new AsyncActionHandler()

handler.on<Actions.RefreshPayload>(
  Actions.refresh.getType(),
  async (store) => {
    try {
      console.debug('Qorai News: Getting data...')
      const [{ feed }, { publishers }] = await Promise.all([
        getQoraiNewsController().getFeed(),
        getQoraiNewsController().getPublishers()
      ])
      console.debug('Qorai News: ...data received.')
      store.dispatch(Actions.dataReceived({ feed, publishers }))
    } catch (e) {
      console.error('error receiving feed', e)
      store.dispatch(Actions.errorGettingDataFromBackground(e))
    }
  }
)

handler.on(Actions.ensureSettingsData.getType(), async (store) => {
  const state = store.getState() as ApplicationState
  if (state.today.publishers && Object.keys(state.today.publishers).length) {
    return
  }
  const { publishers } = await getQoraiNewsController().getPublishers()
  store.dispatch(Actions.dataReceived({ publishers }))
})

handler.on<Actions.ReadFeedItemPayload>(
  Actions.readFeedItem.getType(),
  async (store, payload) => {
    const state = store.getState() as ApplicationState
    if (payload.isPromoted) {
      const promotedArticle = payload.item.promotedArticle
      if (!promotedArticle) {
        console.error(
          'Qorai News: readFeedItem payload with invalid promoted article',
          payload
        )
        return
      }
      if (!payload.promotedUUID) {
        console.error(
          'Qorai News: invalid promotedUUID for readFeedItem',
          payload
        )
        return
      }
      getQoraiNewsController().onPromotedItemVisit(
        payload.promotedUUID,
        promotedArticle.creativeInstanceId
      )
    }
    const data =
      payload.item.article?.data ||
      payload.item.promotedArticle?.data ||
      payload.item.deal?.data
    if (!data) {
      console.error(
        'Qorai News: readFeedItem payload item not present',
        payload
      )
      return
    }
    if (!payload.openInNewTab) {
      // remember article so we can scroll to it on "back" navigation
      // TODO(petemill): Type this history.state data and put in an API module
      // (see `reducers/today`).
      storeInHistoryState({
        todayArticle: data,
        todayPageIndex: state.today.currentPageIndex,
        todayCardsVisited: state.today.cardsVisited
      })
      // visit article url
      window.location.href = data.url.url
    } else {
      window.open(data.url.url, '_blank', 'noreferrer')
    }
  }
)

handler.on<Actions.PromotedItemViewedPayload>(
  Actions.promotedItemViewed.getType(),
  async (store, payload) => {
    if (!payload.item.promotedArticle) {
      console.error(
        'Qorai News: promotedItemViewed invalid promoted article',
        payload
      )
      return
    }
    getQoraiNewsController().onPromotedItemView(
      payload.uuid,
      payload.item.promotedArticle.creativeInstanceId
    )
  }
)

handler.on<number>(
  Actions.feedItemViewedCountChanged.getType(),
  async (store, payload) => {
    const state = store.getState() as ApplicationState
    getQoraiNewsController().onNewCardsViewed(
      state.today.cardsViewedDelta
    )
  }
)

handler.on<Actions.RemoveDirectFeedPayload>(
  Actions.removeDirectFeed.getType(),
  async (store, payload) => {
    getQoraiNewsController().removeDirectFeed(payload.directFeed.publisherId)
    window.setTimeout(() => {
      store.dispatch(Actions.checkForUpdate())
    }, 3000)
  }
)

handler.on<Actions.SetPublisherPrefPayload>(
  Actions.setPublisherPref.getType(),
  async (store, payload) => {
    const { publisherId, enabled } = payload
    let userStatus =
      enabled === null
        ? QoraiNews.UserEnabled.NOT_MODIFIED
        : enabled
        ? QoraiNews.UserEnabled.ENABLED
        : QoraiNews.UserEnabled.DISABLED
    getQoraiNewsController().setPublisherPref(publisherId, userStatus)
    // Refreshing of content after prefs changed is throttled, so wait
    // a while before seeing if we have new content yet.
    // This doesn't have to be exact since we often check for update when
    // opening or scrolling through the feed.
    window.setTimeout(() => {
      store.dispatch(Actions.checkForUpdate())
    }, 3000)
  }
)

handler.on(Actions.checkForUpdate.getType(), async function (store) {
  const state = store.getState() as ApplicationState
  // Detect if we did not get any data successfully and therefore we can try again
  // to fetch data
  if (!state.today.feed) {
    store.dispatch(Actions.isUpdateAvailable({ isUpdateAvailable: true }))
    return
  }
  const hash = state.today.feed.hash
  const isUpdateAvailable: { isUpdateAvailable: boolean } =
    await getQoraiNewsController().isFeedUpdateAvailable(hash)
  store.dispatch(Actions.isUpdateAvailable(isUpdateAvailable))
})

handler.on(Actions.resetTodayPrefsToDefault.getType(), async function (store) {
  getQoraiNewsController().clearPrefs()
  const { publishers } = await getQoraiNewsController().getPublishers()
  store.dispatch(Actions.dataReceived({ publishers }))
  store.dispatch(Actions.checkForUpdate())
})

handler.on(Actions.anotherPageNeeded.getType(), async function (store) {
  store.dispatch(Actions.checkForUpdate())
})

handler.on<Actions.VisitDisplayAdPayload>(
  Actions.visitDisplayAd.getType(),
  async function (store, payload) {
    const state = store.getState() as ApplicationState
    const todayPageIndex = state.today.currentPageIndex
    getQoraiNewsController().onDisplayAdVisit(
      payload.ad.uuid,
      payload.ad.creativeInstanceId
    )
    const destinationUrl = payload.ad.targetUrl.url
    if (!payload.openInNewTab) {
      // Remember display ad location so we can scroll to it on "back" navigation
      // We remember position and not ad ID since it can be a different ad on
      // a new page load.
      // TODO(petemill): Type this history.state data and put in an API module
      // (see `reducers/today`).
      storeInHistoryState({
        todayAdPosition: todayPageIndex,
        todayPageIndex,
        todayCardsVisited: state.today.cardsVisited
      })
      // visit article url
      window.location.href = destinationUrl
    } else {
      window.open(destinationUrl, '_blank', 'noreferrer')
    }
  }
)

handler.on<Actions.DisplayAdViewedPayload>(
  Actions.displayAdViewed.getType(),
  async (store, item) => {
    getQoraiNewsController().onDisplayAdView(
      item.ad.uuid,
      item.ad.creativeInstanceId
    )
  }
)

export default handler.middleware
