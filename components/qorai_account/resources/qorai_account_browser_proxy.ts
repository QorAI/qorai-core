/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { Authentication } from './qorai_account.mojom-webui.js'
import type { AuthenticationInterface } from './qorai_account.mojom-webui.js'
import { PasswordStrengthMeter } from './password_strength_meter.mojom-webui.js'
import type { PasswordStrengthMeterInterface } from './password_strength_meter.mojom-webui.js'

export interface QoraiAccountBrowserProxy {
  authentication: AuthenticationInterface
  password_strength_meter: PasswordStrengthMeterInterface
  closeDialog: () => void
}

export class QoraiAccountBrowserProxyImpl implements QoraiAccountBrowserProxy {
  authentication: AuthenticationInterface
  password_strength_meter: PasswordStrengthMeterInterface

  private constructor() {
    this.authentication = Authentication.getRemote()
    this.password_strength_meter = PasswordStrengthMeter.getRemote()
  }

  closeDialog() {
    chrome.send('dialogClose')
  }

  static getInstance(): QoraiAccountBrowserProxy {
    return instance || (instance = new QoraiAccountBrowserProxyImpl())
  }
}

let instance: QoraiAccountBrowserProxy | null = null
