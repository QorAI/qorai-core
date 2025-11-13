/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import './qorai_account_dialog.js'

import { html } from '//resources/lit/v3_0/lit.rollup.js'
import { loadTimeData } from '//resources/js/load_time_data.js'

import { QoraiAccountErrorDialogElement } from './qorai_account_error_dialog.js'
import { Flow, FlowToErrorCode } from './qorai_account_common.js'
import { RegisterErrorCode } from './qorai_account.mojom-webui.js'

export function getHtml(this: QoraiAccountErrorDialogElement) {
  return html`<!--_html_template_start_-->
    <qorai-account-dialog
      alert-message=${(() => {
        const REGISTER_ERROR_STRINGS = {
          [RegisterErrorCode.kAccountExists]:
            '$i18n{qoraiAccountErrorDialogAccountExists}',
          [RegisterErrorCode.kEmailDomainNotSupported]:
            '$i18n{qoraiAccountErrorDialogEmailDomainNotSupported}',
          [RegisterErrorCode.kTooManyVerifications]:
            '$i18n{qoraiAccountErrorDialogTooManyVerifications}',
        } satisfies Partial<Record<RegisterErrorCode, string>>

        const ERROR_STRINGS: {
          [F in Flow]: Partial<Record<FlowToErrorCode[F], string>>
        } = {
          register: REGISTER_ERROR_STRINGS,
        }

        const { statusCode, errorCode } = this.error.details

        if (statusCode == null) {
          // client-side error
          return loadTimeData.getStringF(
            'qoraiAccountErrorDialogClientError',
            errorCode != null
              ? ` ($i18n{qoraiAccountErrorDialogError}=${errorCode})`
              : '',
          )
        }

        // server-side error
        return (
          (errorCode != null ? ERROR_STRINGS[this.error.flow][errorCode] : null)
          ?? loadTimeData.getStringF(
            'qoraiAccountErrorDialogServerError',
            statusCode,
            errorCode != null
              ? `, $i18n{qoraiAccountErrorDialogError}=${errorCode}`
              : '',
          )
        )
      })()}
      dialog-description="$i18n{qoraiAccountErrorDialogDescription}"
      dialog-title="$i18n{qoraiAccountErrorDialogTitle}"
    >
      <qora-button
        slot="buttons"
        @click=${() => this.fire('back-button-clicked')}
      >
        $i18n{qoraiAccountBackButtonLabel}
      </qora-button>
    </qorai-account-dialog>
    <!--_html_template_end_-->`
}
