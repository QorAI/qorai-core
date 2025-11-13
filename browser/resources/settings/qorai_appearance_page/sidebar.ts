// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import '../settings_shared.css.js'
import '../settings_vars.css.js'

import {PrefsMixin, PrefsMixinInterface} from '/shared/settings/prefs/prefs_mixin.js';
import {I18nMixin, I18nMixinInterface} from 'chrome://resources/cr_elements/i18n_mixin.js'
import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'
import {loadTimeData} from '../i18n_setup.js'

import {getTemplate} from './sidebar.html.js'

const SettingsQoraiAppearanceSidebarElementBase = PrefsMixin(I18nMixin(PolymerElement)) as {
  new (): PolymerElement & I18nMixinInterface & PrefsMixinInterface
}

/**
 * 'settings-qorai-appearance-sidebar' is the settings page area containing
 * qorai's sidebar settings in appearance settings.
 * This is separated from 'settings-qorai-appearance-toolbar' because sidebar
 * option is located below the home button option.
 */
export class SettingsQoraiAppearanceSidebarElement extends SettingsQoraiAppearanceSidebarElementBase {
  static get is() {
    return 'settings-qorai-appearance-sidebar'
  }

  static get template() {
    return getTemplate()
  }


  static get properties() {
    return {
      sidebarShowEnabledLabel_: {
        readOnly: false,
        type: String,
      },
      sidebarShowOptions_: {
        readyOnly: true,
        type: Array,
        value() {
          return [
            {
              value: 0,
              name: loadTimeData.getString(
                'appearanceSettingsShowOptionAlways')
            },
            {
              value: 1,
              name: loadTimeData.getString(
                'appearanceSettingsShowOptionMouseOver')
            },
            {
              value: 3,
              name: loadTimeData.getString(
                'appearanceSettingsShowOptionNever')
            },
          ]
        }
      },
    }
  }

  static get observers() {
    return [
      'onShowOptionChanged_(prefs.qorai.sidebar.sidebar_show_option.value)',
    ]
  }

  private declare sidebarShowOptions_:
    Array<{value: number, name: string}>
  private declare sidebarShowEnabledLabel_: string

  private onShowOptionChanged_() {
    this.sidebarShowEnabledLabel_ = (this.get('prefs.qorai.sidebar.sidebar_show_option.value') === 3)
        ? this.i18n('appearanceSettingsSidebarDisabledDesc')
        : this.i18n('appearanceSettingsSidebarEnabledDesc')
  }
}

customElements.define(SettingsQoraiAppearanceSidebarElement.is, SettingsQoraiAppearanceSidebarElement)
