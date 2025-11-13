/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// Import QoraiNewsControllerMock first.
import './default/data/mockQoraiNewsController'

import * as React from 'react'
import { Dispatch } from 'redux'
import { Provider as ReduxProvider } from 'react-redux'
// Components
import NewTabPage from '../containers/newTab'
import { getActionsForDispatch } from '../api/getActions'
import store from '../store'
import { useNewTabData, getGridSitesData } from './default/data/storybookState'
import { onChangeColoredBackground, onUseQoraiBackground, onShowBrandedImageChanged } from './default/data/backgroundWallpaper'
import getTodayState from './default/data/todayStorybookState'
import getQoraiVPNState from './default/data/qoraiVPNStorybookState'
import getQoraiNewsDisplayAd from './default/data/getQoraiNewsDisplayAd'
import { getDataUrl, getUnpaddedAsDataUrl } from '../../common/privateCDN'
import { images, updateImages } from '../data/backgrounds'

const doNothingDispatch: Dispatch = (action: any) => action

function getActions () {
  return getActionsForDispatch(doNothingDispatch)
}

// @ts-expect-error
window.qoraiStorybookUnpadUrl = async function UnpadUrl (paddedUrl: string, mimeType = 'image/jpg'): Promise<string> {
  const response = await fetch(paddedUrl)
  const blob = await response.blob()
  const buffer = await blob.arrayBuffer()
  if (paddedUrl.endsWith('.pad')) {
    return await getUnpaddedAsDataUrl(buffer, mimeType)
  }
  // Image is already unpadded
  return await getDataUrl(buffer)
}

const StoreProvider: React.FC<React.PropsWithChildren> = ({ children }) => {
  return (
    <ReduxProvider store={store}>
     {children}
    </ReduxProvider>
  )
}

export default {
  title: 'New Tab',
  decorators: [
    (Story: any) => <StoreProvider><Story /></StoreProvider>
  ]
}

updateImages(images.map((image): NewTab.QoraiBackground => {
  return {
    ...image,
    wallpaperImageUrl: require('../../img/newtab/backgrounds/' + image.wallpaperImageUrl)
  }
}))

export const Regular = () => {
  const doNothing = (value?: any) => value
  const state = store.getState()
  const newTabData = useNewTabData(state.newTabData)
  const gridSitesData = getGridSitesData(state.gridSitesData)
  const todayState = getTodayState()
  const qoraiVPNState = getQoraiVPNState()

  return (
    <NewTabPage
      newTabData={newTabData}
      todayData={todayState}
      qoraiVPNData={qoraiVPNState}
      gridSitesData={gridSitesData}
      actions={getActions()}
      saveShowBackgroundImage={doNothing}
      saveShowRewards={doNothing}
      saveShowQoraiTalk={doNothing}
      saveBrandedWallpaperOptIn={onShowBrandedImageChanged}
      saveSetAllStackWidgets={doNothing}
      getQoraiNewsDisplayAd={getQoraiNewsDisplayAd}
      setQoraiBackground={onUseQoraiBackground}
      chooseNewCustomBackgroundImage={doNothing}
      setCustomImageBackground={doNothing}
      removeCustomImageBackground={doNothing}
      setColorBackground={onChangeColoredBackground}
    />
  )
}
