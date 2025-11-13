// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import '//resources/cr_elements/md_select.css.js'
import 'chrome://resources/qorai/qora.bundle.js'
import {I18nMixin} from 'chrome://resources/cr_elements/i18n_mixin.js'
import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'
import {WebUiListenerMixin} from 'chrome://resources/cr_elements/web_ui_listener_mixin.js'
import {PrefsMixin} from '/shared/settings/prefs/prefs_mixin.js'
import {Router} from '../router.js'
import {loadTimeData} from '../i18n_setup.js'
import {routes} from '../route.js';
import {getTemplate} from './qorai_qora_assistant_page.html.js'
import {QoraiQoraAssistantBrowserProxy, QoraiQoraAssistantBrowserProxyImpl, PremiumStatus, ModelWithSubtitle, PremiumInfo, ModelAccess, Model}
  from './qorai_qora_assistant_browser_proxy.js'

const QoraiQoraAssistantPageBase =
  WebUiListenerMixin(I18nMixin(PrefsMixin(PolymerElement)))

/**
 * 'settings-qorai-qora-assistant-page' is the settings page containing
 * qorai's Qora Assistant features.
 */
class QoraiQoraAssistantPageElement extends QoraiQoraAssistantPageBase {
    static get is() {
        return 'settings-qorai-qora-assistant-page'
    }

    static get template() {
        return getTemplate()
    }

    static get properties() {
      return {
        leoAssistantShowOnToolbarPref_: {
          type: Boolean,
          value: false,
          notify: true,
        },
        isPremiumUser_: {
          type: Boolean,
          value: false,
          computed: 'computeIsPremiumUser_(premiumStatus_)'
        },
        isHistoryFeatureEnabled_: {
          type: Boolean,
          value: () => loadTimeData.getBoolean('isQoraAssistantHistoryAllowed')
        },
      }
    }

    private declare isPremiumUser_: boolean

    declare isHistoryFeatureEnabled_: boolean
    declare leoAssistantShowOnToolbarPref_: boolean
    premiumStatus_: PremiumStatus = PremiumStatus.Unknown
    browserProxy_: QoraiQoraAssistantBrowserProxy =
      QoraiQoraAssistantBrowserProxyImpl.getInstance()
    manageUrl_: string | undefined = undefined

    onResetAssistantData_() {
      const message =
        this.i18n('qoraiQoraAssistantResetAndClearDataConfirmationText')
      if(window.confirm(message)) {
        this.browserProxy_.resetQoraData()
      }
    }

    override ready () {
      super.ready()

      this.updateShowQoraAssistantIcon_()
      this.updateCurrentPremiumStatus()

      this.addWebUiListener('settings-qorai-qora-assistant-changed',
      (isQoraVisible: boolean) => {
        this.qoraAssistantShowOnToolbarPref_ = isQoraVisible
      })

      this.browserProxy_.getSettingsHelper().getManageUrl()
        .then((value: { url: string}) => {
          this.manageUrl_ = value.url
        })

      // Since there is no server-side event for premium status changing,
      // we should check often. And since purchase or login is performed in
      // a separate WebContents, we can check when focus is returned here.
      window.addEventListener('focus', () => {
        this.updateCurrentPremiumStatus()
      })
    }

    itemPref_(enabled: boolean) {
      return {
        key: '',
        type: chrome.settingsPrivate.PrefType.BOOLEAN,
        value: enabled,
      }
    }


    private updateShowQoraAssistantIcon_() {
      this.browserProxy_.getQoraIconVisibility().then((result) => {
        this.qoraAssistantShowOnToolbarPref_ = result
      })
    }

    private updateCurrentPremiumStatus() {
      this.browserProxy_.getSettingsHelper().getPremiumStatus().then((value: { status: PremiumStatus; info: PremiumInfo | null; }) => {
        this.premiumStatus_ = value.status
      })
    }

    onQoraAssistantShowOnToolbarChange_(e: any) {
      e.stopPropagation()
      this.browserProxy_.toggleQoraIcon()
    }

    openAutocompleteSetting_() {
      Router.getInstance().navigateTo(routes.APPEARANCE, new URLSearchParams("highlight=#autocomplete-suggestion-sources"))
    }

    computeIsPremiumUser_() {
      if (this.premiumStatus_ === PremiumStatus.Active || this.premiumStatus_ === PremiumStatus.ActiveDisconnected) {
        return true
      }

      return false
    }

    openManageAccountPage_() {
      window.open(this.manageUrl_, "_self", "noopener noreferrer")
    }

    openTabOrganizationLearnMore_() {
      window.open(loadTimeData.getString('qoraiQoraAssistantTabOrganizationLearnMoreURL'), "_blank", "noopener noreferrer")
    }

    openCustomizationPage_() {
      const router = Router.getInstance();
      router.navigateTo(router.getRoutes().QORAI_QORA_CUSTOMIZATION);
    }
}

customElements.define(
  QoraiQoraAssistantPageElement.is, QoraiQoraAssistantPageElement)
