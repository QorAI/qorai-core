/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { CrLitElement } from '//resources/lit/v3_0/lit.rollup.js'

import { getHtml } from './qorai_account_error_dialog.html.js'
import { Error } from './qorai_account_common.js'

export class QoraiAccountErrorDialogElement extends CrLitElement {
  static get is() {
    return 'qorai-account-error-dialog'
  }

  override render() {
    return getHtml.bind(this)()
  }

  static override get properties() {
    return {
      error: { type: Object },
    }
  }

  protected accessor error!: Error
}

declare global {
  interface HTMLElementTagNameMap {
    'qorai-account-error-dialog': QoraiAccountErrorDialogElement
  }
}

customElements.define(
  QoraiAccountErrorDialogElement.is,
  QoraiAccountErrorDialogElement,
)
