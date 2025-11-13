// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';

import {SettingsViewMixin} from '../settings_page/settings_view_mixin.js';
import {ChooserType, ContentSettingsTypes} from '../site_settings/constants.js';

import {getTemplate} from './site_settings_qorai_ai.html.js';

const SiteSettingsQoraiAIPageElementBase = SettingsViewMixin(PolymerElement);

export class SiteSettingsQoraiAIPageElement extends SiteSettingsQoraiAIPageElementBase {
  static get is() {
    return 'site-settings-qorai-ai-page';
  }

  static get template() {
    return getTemplate();
  }

  static get properties() {
    return {
      // Expose ContentSettingsTypes enum to the HTML template.
      contentSettingsTypesEnum_: {
        type: Object,
        value: ContentSettingsTypes,
      },
    };
  }

  // SettingsViewMixin implementation.
  override focusBackButton() {
    this.shadowRoot!.querySelector('settings-subpage')!.focusBackButton();
  }
}

declare global {
  interface HTMLElementTagNameMap {
    'site-settings-qorai-ai-page': SiteSettingsQoraiAIPageElement;
  }
}

customElements.define(SiteSettingsQoraiAIPageElement.is, SiteSettingsQoraiAIPageElement);
