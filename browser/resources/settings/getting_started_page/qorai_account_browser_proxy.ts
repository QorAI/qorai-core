/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { QoraiAccountSettingsHandler } from '../qorai_account_settings_handler.mojom-webui.js'
import type { QoraiAccountSettingsHandlerInterface } from '../qorai_account_settings_handler.mojom-webui.js'

export interface QoraiAccountBrowserProxy {
  handler: QoraiAccountSettingsHandlerInterface
}

export class QoraiAccountBrowserProxyImpl implements QoraiAccountBrowserProxy {
  handler: QoraiAccountSettingsHandlerInterface

  private constructor() {
    this.handler = QoraiAccountSettingsHandler.getRemote()
  }

  static getInstance(): QoraiAccountBrowserProxy {
    return instance || (instance = new QoraiAccountBrowserProxyImpl())
  }
}

let instance: QoraiAccountBrowserProxy | null = null
