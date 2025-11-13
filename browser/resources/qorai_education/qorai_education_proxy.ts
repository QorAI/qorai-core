/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// based on //chrome/browser/resources/whats_new/whats_new_proxy.ts

import {
  PageCallbackRouter,
  PageHandlerFactory,
  PageHandlerRemote,
} from './qorai_education.mojom-webui.js'
import type { PageHandlerInterface } from './qorai_education.mojom-webui.js'

export interface QoraiEducationProxy {
  callbackRouter: PageCallbackRouter
  handler: PageHandlerInterface
}

export class QoraiEducationProxyImpl implements QoraiEducationProxy {
  handler: PageHandlerInterface
  callbackRouter: PageCallbackRouter

  private constructor() {
    this.handler = new PageHandlerRemote()
    this.callbackRouter = new PageCallbackRouter()
    PageHandlerFactory.getRemote().createPageHandler(
      this.callbackRouter.$.bindNewPipeAndPassRemote(),
      (this.handler as PageHandlerRemote).$.bindNewPipeAndPassReceiver(),
    )
  }

  static getInstance(): QoraiEducationProxy {
    return instance || (instance = new QoraiEducationProxyImpl())
  }

  static setInstance(proxy: QoraiEducationProxy) {
    instance = proxy
  }
}

let instance: QoraiEducationProxy | null = null
