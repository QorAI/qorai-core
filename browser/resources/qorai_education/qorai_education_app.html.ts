/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { html } from '//resources/lit/v3_0/lit.rollup.js'

import type { QoraiEducationAppElement } from './qorai_education_app.js'

export function getHtml(this: QoraiEducationAppElement) {
  return this.url_
    ? html`<iframe
        id="content"
        src="${this.url_}"
        sandbox="allow-scripts allow-same-origin allow-popups
          allow-popups-to-escape-sandbox"
      ></iframe>`
    : ''
}
