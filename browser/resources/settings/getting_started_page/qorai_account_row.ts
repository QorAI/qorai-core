/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { CrLitElement } from '//resources/lit/v3_0/lit.rollup.js'

import {
  QoraiAccountBrowserProxy,
  QoraiAccountBrowserProxyImpl
} from './qorai_account_browser_proxy.js'
import { getCss } from './qorai_account_row.css.js'
import { getHtml } from './qorai_account_row.html.js'

export class SettingsQoraiAccountRow extends CrLitElement {
  static get is() {
    return 'settings-qorai-account-row'
  }

  static override get styles() {
    return getCss()
  }

  override render() {
    return getHtml.bind(this)()
  }

  static override get properties() {
    return {
      signedIn: { type: Boolean, reflect: true },
    }
  }

  protected onButtonClicked() {
    this.browserProxy.handler.openDialog()
  }

  private browserProxy: QoraiAccountBrowserProxy =
    QoraiAccountBrowserProxyImpl.getInstance()
  protected accessor signedIn: boolean = false
}

declare global {
  interface HTMLElementTagNameMap {
    'settings-qorai-account-row': SettingsQoraiAccountRow
  }
}

customElements.define(SettingsQoraiAccountRow.is, SettingsQoraiAccountRow)
