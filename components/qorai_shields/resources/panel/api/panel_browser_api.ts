// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as QoraiShields from 'gen/qorai/components/qorai_shields/core/common/qorai_shields_panel.mojom.m.js'
// Provide access to all the generated types
export * from 'gen/qorai/components/qorai_shields/core/common/qorai_shields_panel.mojom.m.js'
export * from 'gen/qorai/components/qorai_shields/core/common/shields_settings.mojom.m.js'

interface API {
  panelHandler: QoraiShields.PanelHandlerRemote
  dataHandler: QoraiShields.DataHandlerRemote
}

let panelBrowserAPIInstance: API
class PanelBrowserAPI implements API {
  panelHandler = new QoraiShields.PanelHandlerRemote()
  dataHandler = new QoraiShields.DataHandlerRemote()

  constructor () {
    const factory = QoraiShields.PanelHandlerFactory.getRemote()
    factory.createPanelHandler(
      this.panelHandler.$.bindNewPipeAndPassReceiver(),
      this.dataHandler.$.bindNewPipeAndPassReceiver()
    )
  }
}

export default function getPanelBrowserAPI () {
  if (!panelBrowserAPIInstance) {
    panelBrowserAPIInstance = new PanelBrowserAPI()
  }
  return panelBrowserAPIInstance
}
