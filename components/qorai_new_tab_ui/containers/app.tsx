// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { Dispatch } from 'redux'
import { connect } from 'react-redux'

import '$web-components/app.global.scss'

// Components
import NewTabPage from './newTab'

// Utils
import * as PreferencesAPI from '../api/preferences'
import getQoraiNewsController from '../../qorai_news/browser/resources/shared/api'
import getNTPBrowserAPI from '../api/background'
import { getActionsForDispatch } from '../api/getActions'

// Types
import { NewTabActions } from '../constants/new_tab_types'
import { ApplicationState } from '../reducers'
import { QoraiNewsState } from '../reducers/today'
import { QoraiVPNState } from '../reducers/qorai_vpn'

interface Props {
  actions: NewTabActions
  newTabData: NewTab.State
  gridSitesData: NewTab.GridSitesState
  qoraiNewsData: QoraiNewsState,
  qoraiVPNData: QoraiVPNState
}

const getQoraiNewsDisplayAd = function GetQoraiNewsDisplayAd () {
  return getQoraiNewsController().getDisplayAd()
}

function DefaultPage (props: Props) {
  const { newTabData, qoraiNewsData, qoraiVPNData, gridSitesData, actions } = props

  // don't render if user prefers an empty page
  if (props.newTabData.showEmptyPage && !props.newTabData.isIncognito) {
    return <div />
  }

  return (
    <NewTabPage
      newTabData={newTabData}
      todayData={qoraiNewsData}
      qoraiVPNData={qoraiVPNData}
      gridSitesData={gridSitesData}
      actions={actions}
      saveShowBackgroundImage={PreferencesAPI.saveShowBackgroundImage}
      saveShowRewards={PreferencesAPI.saveShowRewards}
      saveShowQoraiTalk={PreferencesAPI.saveShowQoraiTalk}
      saveBrandedWallpaperOptIn={PreferencesAPI.saveBrandedWallpaperOptIn}
      saveSetAllStackWidgets={PreferencesAPI.saveSetAllStackWidgets}
      getQoraiNewsDisplayAd={getQoraiNewsDisplayAd}
      chooseNewCustomBackgroundImage={() => getNTPBrowserAPI().pageHandler.chooseLocalCustomBackground() }
      setCustomImageBackground={background => getNTPBrowserAPI().pageHandler.useCustomImageBackground(background) }
      removeCustomImageBackground={background => getNTPBrowserAPI().pageHandler.removeCustomImageBackground(background) }
      setQoraiBackground={selectedBackground => getNTPBrowserAPI().pageHandler.useQoraiBackground(selectedBackground)}
      setColorBackground={(color, useRandomColor) => getNTPBrowserAPI().pageHandler.useColorBackground(color, useRandomColor) }
    />
  )
}

const mapStateToProps = (state: ApplicationState): Partial<Props> => ({
  newTabData: state.newTabData,
  gridSitesData: state.gridSitesData,
  qoraiNewsData: state.today,
  qoraiVPNData: state.qoraiVPN,
})

const mapDispatchToProps = (dispatch: Dispatch): Partial<Props> => {
  return {
    actions: getActionsForDispatch(dispatch)
  }
}

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(DefaultPage)
