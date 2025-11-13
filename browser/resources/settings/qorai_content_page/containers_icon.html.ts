// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { html } from '//resources/lit/v3_0/lit.rollup.js'

import { SettingsQoraiContentContainersIconElement } from './containers_icon'

export function getHtml(this: SettingsQoraiContentContainersIconElement) {
  return html`
    <div
      class="icon-container ${this.selected ? 'selected' : ''}"
      style="background-color: ${this.backgroundColor}"
      @click="${this.handleIconClick_}"
    >
      <qora-icon name="${this.qoraIcon}"></qora-icon>
    </div>
  `
}
