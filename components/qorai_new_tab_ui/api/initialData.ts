// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as preferencesAPI from './preferences'
import * as statsAPI from './stats'
import * as wallpaper from './wallpaper'
import * as newTabAdsDataAPI from './newTabAdsData'
import getNTPBrowserAPI from './background'
import getVPNServiceHandler, * as QoraiVPN from './qoraiVpn'
import { loadTimeData } from '$web-common/loadTimeData'

export type InitialData = {
  preferences: NewTab.Preferences
  stats: statsAPI.Stats
  wallpaperData?: NewTab.Wallpaper
  qoraiBackgrounds: NewTab.QoraiBackground[]
  customImageBackgrounds: NewTab.ImageBackground[]
  qoraiRewardsSupported: boolean
  qoraiTalkSupported: boolean
  searchPromotionEnabled: boolean
  purchasedState: QoraiVPN.PurchasedState
}

export type PreInitialRewardsData = {
  rewardsEnabled: boolean
  userType: string
  declaredCountry: string
  needsBrowserUpgradeToServeAds: boolean
  selfCustodyInviteDismissed: boolean
  isTermsOfServiceUpdateRequired: boolean
}

export type InitialRewardsData = {
  report: NewTab.RewardsBalanceReport
  balance?: number
  externalWallet?: RewardsExtension.ExternalWallet
  externalWalletProviders?: string[]
  adsAccountStatement: NewTab.AdsAccountStatement
  parameters: NewTab.RewardsParameters
  publishersVisitedCount: number
}

const isIncognito: boolean = chrome.extension.inIncognitoContext

// Gets all data required for the first render of the page
export async function getInitialData (): Promise<InitialData> {
  try {
    console.timeStamp('Getting initial data...')
    const [
      preferences,
      stats,
      wallpaperData,
      qoraiRewardsSupported,
      qoraiTalkSupported,
      searchPromotionEnabled,
      qoraiBackgrounds,
      customImageBackgrounds,
      purchasedState
    ] = await Promise.all([
      preferencesAPI.getPreferences(),
      statsAPI.getStats(),
      !isIncognito ? wallpaper.getWallpaper() : Promise.resolve(undefined),
      new Promise((resolve) => {
        chrome.qoraiRewards.isSupported((supported: boolean) => {
          resolve(supported)
        })
      }),
      new Promise((resolve) => {
        if (!('qoraiTalk' in chrome)) {
          resolve(false)
          return
        }

        chrome.qoraiTalk.isSupported((supported: boolean) => {
          resolve(supported)
        })
      }),
      getNTPBrowserAPI().pageHandler.isSearchPromotionEnabled().then(({ enabled }) => enabled),
      getNTPBrowserAPI().pageHandler.getQoraiBackgrounds().then(({ backgrounds }) => {
        return backgrounds.map(background => ({ type: 'qorai', wallpaperImageUrl: background.imageUrl.url, author: background.author, link: background.link.url }))
      }),
      getNTPBrowserAPI().pageHandler.getCustomImageBackgrounds().then(({ backgrounds }) => {
        return backgrounds.map(background => ({ type: 'image', wallpaperImageUrl: background.url.url }))
      }),
      new Promise((resolve) => {
        if (loadTimeData.getBoolean('vpnWidgetSupported')) {
          getVPNServiceHandler().getPurchasedState().then(({state}) => {
            resolve(state.state)
          })
        } else {
          resolve(QoraiVPN.PurchasedState.NOT_PURCHASED)
        }
      })
    ])
    console.timeStamp('Got all initial data.')
    return {
      preferences,
      stats,
      wallpaperData,
      qoraiBackgrounds,
      customImageBackgrounds,
      qoraiRewardsSupported,
      qoraiTalkSupported,
      searchPromotionEnabled,
      purchasedState
    } as InitialData
  } catch (e) {
    console.error(e)
    throw Error('Error getting initial data')
  }
}

export async function getRewardsPreInitialData (): Promise<PreInitialRewardsData> {
  const [
    rewardsEnabled,
    userType,
    declaredCountry,
    selfCustodyInviteDismissed,
    isTermsOfServiceUpdateRequired,
    adsData
  ] = await Promise.all([
    new Promise<boolean>(
      (resolve) => chrome.qoraiRewards.getRewardsEnabled(resolve)),
    new Promise<string>(
      (resolve) => chrome.qoraiRewards.getUserType(resolve)),
    new Promise<string>(
      (resolve) => chrome.qoraiRewards.getDeclaredCountry(resolve)),
    new Promise<boolean>(
        (resolve) => chrome.qoraiRewards.selfCustodyInviteDismissed(resolve)),
    new Promise<boolean>(
        (resolve) => chrome.qoraiRewards.isTermsOfServiceUpdateRequired(resolve)
    ),
    newTabAdsDataAPI.getNewTabAdsData()
  ])

  const needsBrowserUpgradeToServeAds = adsData.needsBrowserUpgradeToServeAds

  return {
    rewardsEnabled,
    userType,
    declaredCountry,
    needsBrowserUpgradeToServeAds,
    selfCustodyInviteDismissed,
    isTermsOfServiceUpdateRequired
  }
}

export async function getRewardsInitialData (): Promise<InitialRewardsData> {
  try {
    const [
      adsAccountStatement,
      report,
      balance,
      parameters,
      externalWallet,
      externalWalletProviders,
      publishersVisitedCount
    ] = await Promise.all([
      new Promise(resolve => chrome.qoraiRewards.getAdsAccountStatement((success: boolean, adsAccountStatement: NewTab.AdsAccountStatement) => {
        resolve(success ? adsAccountStatement : undefined)
      })),
      new Promise(resolve => chrome.qoraiRewards.getBalanceReport(new Date().getMonth() + 1, new Date().getFullYear(), (report: NewTab.RewardsBalanceReport) => {
        resolve(report)
      })),
      new Promise(resolve => chrome.qoraiRewards.fetchBalance(
        (balance?: number) => {
          resolve(balance)
        }
      )),
      new Promise(resolve => chrome.qoraiRewards.getRewardsParameters((parameters: NewTab.RewardsParameters) => {
        resolve(parameters)
      })),
      new Promise(resolve => {
        chrome.qoraiRewards.getExternalWallet((wallet) => resolve(wallet))
      }),
      new Promise(resolve => {
        chrome.qoraiRewards.getExternalWalletProviders(resolve)
      }),
      new Promise(resolve => {
        chrome.qoraiRewards.getPublishersVisitedCount(resolve)
      })
    ])
    return {
      adsAccountStatement,
      report,
      balance,
      parameters,
      externalWallet,
      externalWalletProviders,
      publishersVisitedCount
    } as InitialRewardsData
  } catch (err) {
    throw Error(err)
  }
}
