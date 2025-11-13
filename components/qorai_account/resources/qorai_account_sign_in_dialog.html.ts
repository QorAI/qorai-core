/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { html } from '//resources/lit/v3_0/lit.rollup.js'

import './qorai_account_dialog.js'
import { onEyeIconClicked } from './qorai_account_common.js'
import { QoraiAccountSignInDialogElement } from './qorai_account_sign_in_dialog.js'

export function getHtml(this: QoraiAccountSignInDialogElement) {
  return html`<!--_html_template_start_-->
    <qorai-account-dialog
      dialog-description="$i18n{qoraiAccountSignInDialogDescription}"
      dialog-title="$i18n{qoraiAccountSignInDialogTitle}"
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
        <qora-input
          placeholder="$i18n{qoraiAccountPasswordInputPlaceholder}"
          type="password"
          @input=${this.onPasswordInput}
        >
          <div class="password">
            <div class="label">$i18n{qoraiAccountPasswordInputLabel}</div>
            <div
              class="forgot-password"
              @click=${() => this.fire('forgot-password-button-clicked')}
            >
              $i18n{qoraiAccountForgotPasswordButtonLabel}
            </div>
          </div>
          <qora-icon
            name="eye-off"
            slot="right-icon"
            @click=${onEyeIconClicked}
          >
          </qora-icon>
        </qora-input>
      </div>
      <qora-button
        slot="buttons"
        ?isDisabled=${!this.isEmailValid || !this.isPasswordValid}
        @click=${() => this.fire('sign-in-button-clicked')}
      >
        $i18n{qoraiAccountSignInButtonLabel}
      </qora-button>
    </qorai-account-dialog>
    <!--_html_template_end_-->`
}
