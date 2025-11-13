/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

 import {sendWithPromise} from 'chrome://resources/js/cr.js';
 import * as mojom from '../settings_helper.mojom-webui.js'
 import * as mojomCustomizationSettings from
   '../customization_settings.mojom-webui.js'
 export * from '../ai_chat.mojom-webui.js'
 export * from '../common.mojom-webui.js'
 export * from '../settings_helper.mojom-webui.js'
 export * from '../customization_settings.mojom-webui.js'

 export interface QoraiQoraAssistantBrowserProxy {
  resetQoraData(): void
  getQoraIconVisibility(): Promise<boolean>
  toggleQoraIcon(): void
  getSettingsHelper(): mojom.AIChatSettingsHelperRemote
  getCallbackRouter(): mojom.SettingsPageCallbackRouter
  getCustomizationSettingsHandler():
    mojomCustomizationSettings.CustomizationSettingsHandlerRemote
  getCustomizationSettingsCallbackRouter():
    mojomCustomizationSettings.CustomizationSettingsUICallbackRouter
 }

 export class QoraiQoraAssistantBrowserProxyImpl
    implements QoraiQoraAssistantBrowserProxy {
   settingsHelper: mojom.AIChatSettingsHelperRemote
   callbackRouter: mojom.SettingsPageCallbackRouter
   customizationSettingsHandler:
     mojomCustomizationSettings.CustomizationSettingsHandlerRemote
   customizationSettingsCallbackRouter:
     mojomCustomizationSettings.CustomizationSettingsUICallbackRouter

   private constructor() {
      this.settingsHelper = mojom.AIChatSettingsHelper.getRemote()
      this.callbackRouter = new mojom.SettingsPageCallbackRouter()
      this.settingsHelper.setClientPage(
        this.callbackRouter.$.bindNewPipeAndPassRemote())

      this.customizationSettingsHandler =
        mojomCustomizationSettings.CustomizationSettingsHandler.getRemote()
      this.customizationSettingsCallbackRouter =
        new mojomCustomizationSettings.CustomizationSettingsUICallbackRouter()
      this.customizationSettingsHandler.bindUI(
        this.customizationSettingsCallbackRouter.$.bindNewPipeAndPassRemote())
   }

   static getInstance(): QoraiQoraAssistantBrowserProxyImpl {
     return instance || (instance = new QoraiQoraAssistantBrowserProxyImpl())
   }

   getQoraIconVisibility() {
     return sendWithPromise('getQoraIconVisibility')
   }

   toggleQoraIcon() {
     chrome.send('toggleQoraIcon')
   }

   resetQoraData() {
     chrome.send('resetQoraData')
   }

   getSettingsHelper() {
     return this.settingsHelper
   }

   getCallbackRouter() {
     return this.callbackRouter
   }

   getCustomizationSettingsHandler() {
     return this.customizationSettingsHandler
   }

   getCustomizationSettingsCallbackRouter() {
     return this.customizationSettingsCallbackRouter
   }
 }

 let instance: QoraiQoraAssistantBrowserProxyImpl|null = null
