// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { sendWithPromise } from 'chrome://resources/js/cr.js';

// TODO(petemill): Define the expected types instead of using any
export interface QoraiTorBrowserProxy {
  getBridgesConfig: () => Promise<any>
  setBridgesConfig: (config: any) => void
  requestBridgesCaptcha: () => Promise<any>
  resolveBridgesCaptcha: (captcha: any) => Promise<any>
  setTorEnabled: (value: boolean) => void
  isTorEnabled: () => Promise<boolean>
  isTorManaged: () => Promise<boolean>
  isSnowflakeExtensionAllowed: () => Promise<boolean>
  isSnowflakeExtensionEnabled: () => Promise<boolean>
  enableSnowflakeExtension: (enable: boolean) => Promise<boolean>
}

export class QoraiTorBrowserProxyImpl implements QoraiTorBrowserProxy {
  static getInstance() {
    return instance || (instance = new QoraiTorBrowserProxyImpl());
  }

  getBridgesConfig() {
    return sendWithPromise('qorai_tor.getBridgesConfig')
  }

  setBridgesConfig(config: any) {
    chrome.send('qorai_tor.setBridgesConfig', [config])
  }

  requestBridgesCaptcha() {
    return sendWithPromise('qorai_tor.requestBridgesCaptcha')
  }

  resolveBridgesCaptcha(captcha: any) {
    return sendWithPromise('qorai_tor.resolveBridgesCaptcha', captcha)
  }

  setTorEnabled(value: boolean) {
    chrome.send('qorai_tor.setTorEnabled', [value])
  }

  isTorEnabled() {
    return sendWithPromise('qorai_tor.isTorEnabled')
  }

  isTorManaged() {
    return sendWithPromise('qorai_tor.isTorManaged')
  }

  isSnowflakeExtensionAllowed() {
    return sendWithPromise('qorai_tor.isSnowflakeExtensionAllowed')
  }

  isSnowflakeExtensionEnabled() {
    return sendWithPromise('qorai_tor.isSnowflakeExtensionEnabled')
  }

  enableSnowflakeExtension(enable: boolean) {
    return sendWithPromise('qorai_tor.enableSnowflakeExtension', enable)
  }
}

let instance: QoraiTorBrowserProxy|null = null
