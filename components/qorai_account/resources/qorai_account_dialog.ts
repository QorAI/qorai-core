/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import {
  CrLitElement,
  PropertyValues,
} from '//resources/lit/v3_0/lit.rollup.js'

import { getCss } from './qorai_account_dialog.css.js'
import { getHtml } from './qorai_account_dialog.html.js'

export class QoraiAccountDialogElement extends CrLitElement {
  static get is() {
    return 'qorai-account-dialog'
  }

  static override get styles() {
    return getCss()
  }

  override render() {
    return getHtml.bind(this)()
  }

  static override get properties() {
    return {
      alertMessage: { type: String },
      dialogDescription: { type: String },
      dialogTitle: { type: String },
      isFooterSlotted: { type: Boolean },
      showBackButton: { type: Boolean },
    }
  }

  protected accessor alertMessage: string = ''
  protected accessor dialogDescription: string = ''
  protected accessor dialogTitle: string = ''
  protected accessor isFooterSlotted: boolean = false
  protected accessor showBackButton: boolean = false

  override firstUpdated(changedProperties: PropertyValues<this>) {
    super.firstUpdated(changedProperties)
    const footer = this.shadowRoot?.querySelector(
      'slot[name="footer"]',
    ) as HTMLSlotElement
    if (footer) {
      footer.addEventListener('slotchange', () => {
        this.isFooterSlotted = footer.assignedNodes().length > 0
      })
    }
  }
}

declare global {
  interface HTMLElementTagNameMap {
    'qorai-account-dialog': QoraiAccountDialogElement
  }
}

customElements.define(QoraiAccountDialogElement.is, QoraiAccountDialogElement)
