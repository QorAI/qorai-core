/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as QoraiPrivateNewTab from 'gen/qorai/components/qorai_private_new_tab_ui/common/qorai_private_new_tab.mojom.m.js'

// Provide access to all the generated types
export * from 'gen/qorai/components/qorai_private_new_tab_ui/common/qorai_private_new_tab.mojom.m.js'

interface API {
  pageHandler: QoraiPrivateNewTab.PageHandlerRemote
  callbackRouter: QoraiPrivateNewTab.PrivateTabPageCallbackRouter
}

let apiInstance: API

class PageHandlerAPI implements API {
  pageHandler: QoraiPrivateNewTab.PageHandlerRemote
  callbackRouter: QoraiPrivateNewTab.PrivateTabPageCallbackRouter

  constructor () {
    this.pageHandler = QoraiPrivateNewTab.PageHandler.getRemote()
    this.callbackRouter = new QoraiPrivateNewTab.PrivateTabPageCallbackRouter()
    this.pageHandler.setClientPage(this.callbackRouter.$.bindNewPipeAndPassRemote())
  }
}

export default function getPageHandlerInstance () {
  if (!apiInstance) {
    apiInstance = new PageHandlerAPI()
  }
  return apiInstance
}
