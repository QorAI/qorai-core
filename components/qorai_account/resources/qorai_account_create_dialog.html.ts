/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { html } from '//resources/lit/v3_0/lit.rollup.js'

import { onEyeIconClicked } from './qorai_account_common.js'
import { QoraiAccountCreateDialogElement } from './qorai_account_create_dialog.js'

export function getHtml(this: QoraiAccountCreateDialogElement) {
  return html`<!--_html_template_start_-->
    <qorai-account-dialog
      dialog-description="$i18n{qoraiAccountCreateDialogDescription}"
      dialog-title="$i18n{qoraiAccountCreateDialogTitle}"
      show-back-button
    >
      <div slot="inputs">
        <qora-input
          placeholder="$i18n{qoraiAccountEmailInputPlaceholder}"
          showErrors
          @input=${this.onEmailInput}
        >
          <div
            class="label ${(this.email.length !== 0 && !this.isEmailValid)
            || (this.isEmailValid && this.isEmailQoraiAlias)
              ? 'error'
              : ''}"
          >
            $i18n{qoraiAccountEmailInputLabel}
          </div>
          <div
            class="dropdown ${this.isEmailValid && this.isEmailQoraiAlias
              ? 'visible'
              : ''}"
            id="qorai-alias-dropdown"
            slot="errors"
          >
            <qora-icon name="warning-triangle-filled"></qora-icon>
            <div>$i18n{qoraiAccountEmailInputErrorMessage}</div>
          </div>
        </qora-input>
        <qora-input
          placeholder="$i18n{qoraiAccountPasswordInputPlaceholder}"
          showErrors
          type="password"
          @input=${this.onPasswordInput}
        >
          <div class="label">$i18n{qoraiAccountCreatePasswordInputLabel}</div>
          <qora-icon
            name="eye-off"
            slot="right-icon"
            @click=${onEyeIconClicked}
          >
          </qora-icon>
          <div
            slot="errors"
            class="dropdown ${this.passwordStrength !== 0 ? 'visible' : ''}"
            id="password-dropdown"
          >
            <password-strength-meter strength=${this.passwordStrength}>
            </password-strength-meter>
          </div>
        </qora-input>
        <qora-input
          placeholder="$i18n{qoraiAccountConfirmPasswordInputPlaceholder}"
          showErrors
          type="password"
          @input=${this.onConfirmPasswordInput}
        >
          <div
            class="label ${this.passwordConfirmation.length !== 0
            && this.passwordConfirmation !== this.password
              ? 'error'
              : ''}"
          >
            $i18n{qoraiAccountConfirmPasswordInputLabel}
          </div>
          <qora-icon
            name="eye-off"
            slot="right-icon"
            @click=${onEyeIconClicked}
          >
          </qora-icon>
          <div
            class="dropdown ${this.passwordConfirmation.length !== 0
              ? 'visible'
              : ''}"
            id="password-confirmation-dropdown"
            slot="errors"
          >
            <qora-icon name=${this.getIconName()}></qora-icon>
            <div>
              ${this.icon === 'check-circle-filled'
                ? html`$i18n{qoraiAccountConfirmPasswordInputSuccessMessage}`
                : html`$i18n{qoraiAccountConfirmPasswordInputErrorMessage}`}
            </div>
          </div>
        </qora-input>
        <qora-checkbox @change=${this.onCheckboxChanged}>
          <div>$i18nRaw{qoraiAccountConsentCheckboxLabel}</div>
        </qora-checkbox>
      </div>
      <qora-button
        slot="buttons"
        ?isDisabled=${!this.isEmailValid
        || (this.isEmailValid && this.isEmailQoraiAlias)
        || this.passwordStrength !== 100
        || this.passwordConfirmation !== this.password
        || !this.isCheckboxChecked}
        @click=${this.onCreateAccountButtonClicked}
      >
        $i18n{qoraiAccountCreateAccountButtonLabel}
      </qora-button>
    </qorai-account-dialog>
    <!--_html_template_end_-->`
}
