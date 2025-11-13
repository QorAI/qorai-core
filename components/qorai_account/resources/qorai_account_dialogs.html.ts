/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import {
  html,
  nothing,
  TemplateResult,
} from '//resources/lit/v3_0/lit.rollup.js'

import './qorai_account_create_dialog.js'
import './qorai_account_entry_dialog.js'
import './qorai_account_error_dialog.js'
import './qorai_account_forgot_password_dialog.js'
import './qorai_account_sign_in_dialog.js'
import { QoraiAccountDialogs, Dialog } from './qorai_account_dialogs.js'
import { Error } from './qorai_account_common.js'

export function getHtml(this: QoraiAccountDialogs) {
  const dialogHtml: Record<
    Dialog['type'],
    () => TemplateResult | typeof nothing
  > = {
    NONE: () => nothing,
    ENTRY: () => html`
      <qorai-account-entry-dialog
        @close-dialog=${this.onCloseDialog}
        @create-button-clicked=${() => (this.dialog = { type: 'CREATE' })}
        @self-custody-button-clicked=${() => (this.dialog = { type: 'NONE' })}
        @sign-in-button-clicked=${() => (this.dialog = { type: 'SIGN_IN' })}
      >
      </qorai-account-entry-dialog>
    `,
    CREATE: () => html`
      <qorai-account-create-dialog
        @back-button-clicked=${this.onBackButtonClicked}
        @close-dialog=${this.onCloseDialog}
        @error-occurred=${(e: CustomEvent<Error>) =>
          (this.dialog = {
            type: 'ERROR',
            error: e.detail,
          })}
      >
      </qorai-account-create-dialog>
    `,
    SIGN_IN: () => html`
      <qorai-account-sign-in-dialog
        @back-button-clicked=${this.onBackButtonClicked}
        @close-dialog=${this.onCloseDialog}
        @forgot-password-button-clicked=${() =>
          (this.dialog = { type: 'FORGOT_PASSWORD' })}
        @sign-in-button-clicked=${() => {
          this.dialog = { type: 'NONE' }
          this.signedIn = true
        }}
      >
      </qorai-account-sign-in-dialog>
    `,
    FORGOT_PASSWORD: () => html`
      <qorai-account-forgot-password-dialog
        @back-button-clicked=${this.onBackButtonClicked}
        @close-dialog=${this.onCloseDialog}
      </qorai-account-forgot-password-dialog>
    `,
    ERROR: () => html`
      <qorai-account-error-dialog
        @back-button-clicked=${this.onBackButtonClicked}
        @close-dialog=${this.onCloseDialog}
        .error=${(this.dialog as Extract<Dialog, { type: 'ERROR' }>).error}
      >
      </qorai-account-error-dialog>
    `,
  }

  return dialogHtml[this.dialog.type]()
}
