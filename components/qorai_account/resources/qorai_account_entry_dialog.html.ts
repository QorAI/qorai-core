/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { html } from '//resources/lit/v3_0/lit.rollup.js'

import './qorai_account_dialog.js'
import { QoraiAccountEntryDialogElement } from './qorai_account_entry_dialog.js'

export function getHtml(this: QoraiAccountEntryDialogElement) {
  return html`<!--_html_template_start_-->
    <qorai-account-dialog
      dialog-description="$i18n{qoraiAccountEntryDialogDescription}"
      dialog-title="$i18n{qoraiAccountEntryDialogTitle}"
    >
      <qora-button
        slot="buttons"
        @click=${() => this.fire('create-button-clicked')}
      >
        $i18n{qoraiAccountCreateQoraiAccountButtonLabel}
      </qora-button>
      <qora-button
        slot="buttons"
        kind="outline"
        @click=${() => this.fire('sign-in-button-clicked')}
      >
        $i18n{qoraiAccountAlreadyHaveAccountSignInButtonLabel}
      </qora-button>
      <div slot="footer">
        <div class="footer-text">
          $i18nRaw{qoraiAccountSelfCustodyDescription}
        </div>
        <qora-button
          kind="plain-faint"
          @click=${() => this.fire('self-custody-button-clicked')}
        >
          $i18n{qoraiAccountSelfCustodyButtonLabel}
        </qora-button>
      </div>
    </qorai-account-dialog>
    <!--_html_template_end_-->`
}
