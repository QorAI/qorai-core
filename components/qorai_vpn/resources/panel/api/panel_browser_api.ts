// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as QoraiVPN from 'gen/qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.m.js'
// Provide access to all the generated types
export * from 'gen/qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.m.js'

export type SupportData = QoraiVPN.ServiceHandler_GetSupportData_ResponseParams

interface API {
  pageCallbackRouter: QoraiVPN.PageInterface
  panelHandler: QoraiVPN.PanelHandlerInterface
  serviceHandler: QoraiVPN.ServiceHandlerInterface
}

let panelBrowserAPIInstance: API
class PanelBrowserAPI implements API {
  pageCallbackRouter = new QoraiVPN.PageCallbackRouter()
  panelHandler = new QoraiVPN.PanelHandlerRemote()
  serviceHandler = new QoraiVPN.ServiceHandlerRemote()

  constructor () {
    const factory = QoraiVPN.PanelHandlerFactory.getRemote()
    factory.createPanelHandler(
      this.pageCallbackRouter.$.bindNewPipeAndPassRemote(),
      this.panelHandler.$.bindNewPipeAndPassReceiver(),
      this.serviceHandler.$.bindNewPipeAndPassReceiver()
    )
  }
}

export default function getPanelBrowserAPI () {
  if (!panelBrowserAPIInstance) {
    panelBrowserAPIInstance = new PanelBrowserAPI()
  }
  return panelBrowserAPIInstance
}

export function setPanelBrowserApiForTesting (api: API) {
  panelBrowserAPIInstance = api
}
