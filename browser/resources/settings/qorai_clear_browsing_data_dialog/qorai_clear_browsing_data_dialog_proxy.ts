/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

 import {sendWithPromise} from 'chrome://resources/js/cr.js'

 export interface QoraiClearBrowsingDataDialogBrowserProxy {
  getQoraiRewardsEnabled: () => Promise<boolean>
  clearQoraiAdsData: () => void
 }

 export class QoraiClearBrowsingDataDialogBrowserProxyImpl
    implements QoraiClearBrowsingDataDialogBrowserProxy {

   getQoraiRewardsEnabled() {
    return sendWithPromise('getQoraiRewardsEnabled')
  }

  clearQoraiAdsData() {
    chrome.send('clearQoraiAdsData')
  }

  static getInstance(): QoraiClearBrowsingDataDialogBrowserProxyImpl {
    return instance ||
        (instance = new QoraiClearBrowsingDataDialogBrowserProxyImpl())
  }
}

let instance: QoraiClearBrowsingDataDialogBrowserProxyImpl|null = null
