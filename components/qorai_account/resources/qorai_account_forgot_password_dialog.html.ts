/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { html } from '//resources/lit/v3_0/lit.rollup.js'

import './qorai_account_dialog.js'
import { QoraiAccountForgotPasswordDialogElement } from './qorai_account_forgot_password_dialog.js'

export function getHtml(this: QoraiAccountForgotPasswordDialogElement) {
  return html`<!--_html_template_start_-->
    <qorai-account-dialog
      alert-message="$i18n{qoraiAccountAlertMessage}"
      dialog-description="$i18n{qoraiAccountForgotPasswordDialogDescription}"
      dialog-title="$i18n{qoraiAccountForgotPasswordDialogTitle}"
      show-back-button
    >
      <div slot="inputs">
        <qora-input
          placeholder="$i18n{qoraiAccountEmailInputPlaceholder}"
          @input=${this.onEmailInput}
        >
          <div
            class="label ${this.email.length !== 0 && !this.isEmailValid
              ? 'error'
              : ''}"
          >
            $i18n{qoraiAccountEmailInputLabel}
          </div>
        </qora-input>
      </div>
      <qora-button
        slot="buttons"
        ?isDisabled=${!this.isEmailValid}
      >
        $i18n{qoraiAccountResetPasswordButtonLabel}
      </qora-button>
    </qorai-account-dialog>
    <!--_html_template_end_-->`
}
