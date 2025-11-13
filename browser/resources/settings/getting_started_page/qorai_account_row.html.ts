/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { html } from '//resources/lit/v3_0/lit.rollup.js'

import { loadTimeData } from '//resources/js/load_time_data.js'
import { SettingsQoraiAccountRow } from './qorai_account_row.js'

export function getHtml(this: SettingsQoraiAccountRow) {
  return html`
    <div class="row">
      <div class="circle">
        <qora-icon name="social-qorai-release-favicon-fullheight-color">
        </qora-icon>
      </div>
      <div class="title-and-description">
        <div class="title">
          ${this.signedIn
            ? 'John Doe'
            : loadTimeData.getString('qoraiAccountRowTitle')}
        </div>
        <div class="description">
          ${this.signedIn
            ? 'johndoe@gmail.com'
            : loadTimeData.getString('qoraiAccountRowDescription')}
        </div>
      </div>
      <qora-button kind=${this.signedIn ? 'outline' : 'filled'}
                  size="small"
                  @click=${this.onButtonClicked}>
        ${this.signedIn
          ? loadTimeData.getString('qoraiAccountManageAccountButtonLabel')
          : loadTimeData.getString('qoraiAccountGetStartedButtonLabel')
        }
      </qora-button>
    </div>`
}
