/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { CrLitElement } from '//resources/lit/v3_0/lit.rollup.js'

import { getCss } from './qorai_account_entry_dialog.css.js'
import { getHtml } from './qorai_account_entry_dialog.html.js'

export class QoraiAccountEntryDialogElement extends CrLitElement {
  static get is() {
    return 'qorai-account-entry-dialog'
  }

  static override get styles() {
    return getCss()
  }

  override render() {
    return getHtml.bind(this)()
  }
}

declare global {
  interface HTMLElementTagNameMap {
    'qorai-account-entry-dialog': QoraiAccountEntryDialogElement
  }
}

customElements.define(
  QoraiAccountEntryDialogElement.is,
  QoraiAccountEntryDialogElement,
)
