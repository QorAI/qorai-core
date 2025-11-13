/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as QoraiNewTabPage from 'gen/qorai/components/qorai_new_tab_ui/qorai_new_tab_page.mojom.m.js'
import * as NTPBackgroundMedia from 'gen/qorai/components/ntp_background_images/browser/mojom/ntp_background_images.mojom.m.js'

// Provide access to all the generated types
export * from 'gen/qorai/components/qorai_new_tab_ui/qorai_new_tab_page.mojom.m.js'

import { images as backgrounds, solidColorsForBackground, gradientColorsForBackground } from '../data/backgrounds'

/**
 * Generates a random image for new tab backgrounds
 */
export const randomBackgroundImage = (): NewTab.QoraiBackground => {
  const randomIndex: number = Math.floor(Math.random() * backgrounds.length)
  const image: NewTab.QoraiBackground = { ...backgrounds[randomIndex], random: true }
  return image
}

export const randomColorBackground = (color: string): NewTab.BackgroundWallpaper => {
  console.assert(color === QoraiNewTabPage.RANDOM_SOLID_COLOR_VALUE || color === QoraiNewTabPage.RANDOM_GRADIENT_COLOR_VALUE)

  const targetColors = color === QoraiNewTabPage.RANDOM_SOLID_COLOR_VALUE ? solidColorsForBackground : gradientColorsForBackground
  const randomIndex: number = Math.floor(Math.random() * targetColors.length)
  const randomColor: NewTab.ColorBackground = {
    ...targetColors[randomIndex],
    random: true
  }
  return randomColor
}

interface API {
  pageCallbackRouter: QoraiNewTabPage.PageCallbackRouter
  pageHandler: QoraiNewTabPage.PageHandlerRemote
  newTabMetrics: QoraiNewTabPage.NewTabMetricsRemote
  sponsoredRichMediaAdEventHandler: NTPBackgroundMedia.SponsoredRichMediaAdEventHandlerRemote
  addBackgroundUpdatedListener: (listener: BackgroundUpdated) => void
  addCustomImageBackgroundsUpdatedListener: (listener: CustomImageBackgroundsUpdated) => void
  addSearchPromotionDisabledListener: (listener: () => void) => void
}

type BackgroundUpdated = (background: QoraiNewTabPage.Background) => void
type CustomImageBackgroundsUpdated = (backgrounds: QoraiNewTabPage.CustomBackground[]) => void

let ntpBrowserAPIInstance: API

class NTPBrowserAPI implements API {
  pageCallbackRouter = new QoraiNewTabPage.PageCallbackRouter()
  pageHandler = new QoraiNewTabPage.PageHandlerRemote()
  newTabMetrics = new QoraiNewTabPage.NewTabMetricsRemote()
  sponsoredRichMediaAdEventHandler = new NTPBackgroundMedia.SponsoredRichMediaAdEventHandlerRemote()

  constructor () {
    const factory = QoraiNewTabPage.PageHandlerFactory.getRemote()
    factory.createPageHandler(
      this.pageCallbackRouter.$.bindNewPipeAndPassRemote(),
      this.pageHandler.$.bindNewPipeAndPassReceiver(),
      this.newTabMetrics.$.bindNewPipeAndPassReceiver(),
      this.sponsoredRichMediaAdEventHandler.$.bindNewPipeAndPassReceiver()
    )
  }

  addBackgroundUpdatedListener (listener: BackgroundUpdated) {
    this.pageCallbackRouter.onBackgroundUpdated.addListener(listener)
  }

  addCustomImageBackgroundsUpdatedListener (listener: CustomImageBackgroundsUpdated) {
    this.pageCallbackRouter.onCustomImageBackgroundsUpdated.addListener(listener)
  }

  addSearchPromotionDisabledListener (listener: () => void) {
    this.pageCallbackRouter.onSearchPromotionDisabled.addListener(listener)
  }
}

export default function getNTPBrowserAPI () {
  if (!ntpBrowserAPIInstance) {
    ntpBrowserAPIInstance = new NTPBrowserAPI()
  }
  return ntpBrowserAPIInstance
}
