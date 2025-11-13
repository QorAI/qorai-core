/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { CrLitElement } from '//resources/lit/v3_0/lit.rollup.js'

import { getCss } from './qorai_account_sign_in_dialog.css.js'
import { getHtml } from './qorai_account_sign_in_dialog.html.js'
import { isEmailValid } from './qorai_account_common.js'

// @ts-expect-error
import { Login } from 'chrome://resources/qorai/opaque_ke.bundle.js'

export class QoraiAccountSignInDialogElement extends CrLitElement {
  static get is() {
    return 'qorai-account-sign-in-dialog'
  }

  static override get styles() {
    return getCss()
  }

  override render() {
    return getHtml.bind(this)()
  }

  static override get properties() {
    return {
      email: { type: String },
      isEmailValid: { type: Boolean },
      isPasswordValid: { type: Boolean },
    }
  }

  protected onEmailInput(detail: { value: string }) {
    this.email = detail.value
    this.isEmailValid = isEmailValid(this.email)
  }

  protected onPasswordInput(detail: { value: string }) {
    this.isPasswordValid = detail.value.length !== 0
  }

  protected accessor email: string = ''
  protected accessor isEmailValid: boolean = false
  protected accessor isPasswordValid: boolean = false
  protected login = new Login()
}

declare global {
  interface HTMLElementTagNameMap {
    'qorai-account-sign-in-dialog': QoraiAccountSignInDialogElement
  }
}

customElements.define(
  QoraiAccountSignInDialogElement.is,
  QoraiAccountSignInDialogElement,
)
