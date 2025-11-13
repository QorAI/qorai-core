/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import {
  RegisterPolymerComponentReplacement,
  RegisterPolymerTemplateModifications,
  RegisterStyleOverride
} from 'chrome://resources/qorai/polymer_overriding.js'

import {getTrustedHTML} from 'chrome://resources/js/static_types.js'
import {html} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'

import {
  QoraiSettingsClearBrowsingDataDialogElement
} from '../qorai_clear_browsing_data_dialog/qorai_clear_browsing_data_dialog_behavior.js'

import {loadTimeData} from '../i18n_setup.js'

RegisterStyleOverride(
  'settings-clear-browsing-data-dialog',
  html`
    <style>
      :host {
        --body-container-height: 372px !important;
      }
      #reset-qorai-rewards-data, #clear-qorai-ads-data {
        display: block;
        margin-top: 10px;
      }
    </style>
  `
)

RegisterPolymerComponentReplacement(
  'settings-clear-browsing-data-dialog',
  QoraiSettingsClearBrowsingDataDialogElement
)

RegisterPolymerTemplateModifications({
  'settings-clear-browsing-data-dialog': (templateContent) => {
    // Append On exit tab page.
    const pagesElement = templateContent.querySelector('#pages')
    if (!pagesElement) {
      console.error('[Settings] missing #pages in clear-browsing-data-dialog')
      return
    }
    pagesElement.insertAdjacentHTML(
      'beforeend',
      getTrustedHTML`
        <settings-qorai-clear-browsing-data-on-exit-page
          id="on-exit-tab"
          prefs="{{prefs}}"
        />
      `)

    // Append Save button.
    const confirmButtonElement = templateContent.querySelector('#clearButton')
    if (!confirmButtonElement) {
      console.error(
        '[Settings] missing #clearButton in clear-browsing-data-dialog')
      return
    }
    confirmButtonElement.insertAdjacentHTML(
      'afterend',
      getTrustedHTML`
        <cr-button
          id="saveOnExitSettingsConfirm"
          class="action-button"
          disabled hidden>
        </cr-button>
      `)
    const saveButton =
      templateContent.getElementById('saveOnExitSettingsConfirm')
    if (!saveButton) {
      console.error('[Settings] missing save button')
    } else {
      saveButton.textContent = loadTimeData.getString('save')
    }

    // Append clear Qorai Ads data link
    const body = templateContent.querySelector('[slot="body"]')
    if (!body) {
      console.error(
        '[Settings] missing \'slot="body"\' in clear-browsing-data-dialog')
      return
    }
    body.insertAdjacentHTML(
      'beforeend',
      getTrustedHTML`
        <a id="clear-qorai-ads-data"
          href="chrome://settings/privacy"
          onClick="[[onClearQoraiAdsDataClickHandler_]]"
          hidden="[[qoraiRewardsEnabled_]]">
        </a>
      `)
    const clearQoraiAdsLink =
      templateContent.getElementById('clear-qorai-ads-data')
    if (!clearQoraiAdsLink) {
      console.error('[Settings] missing clear Qorai Ads link')
    } else {
      clearQoraiAdsLink.textContent =
        loadTimeData.getString('clearQoraiAdsData')
    }

    // Append reset Qorai Rewards data link
    body.insertAdjacentHTML(
      'beforeend',
      getTrustedHTML`
        <a id="reset-qorai-rewards-data"
          href="chrome://rewards/#reset"
          hidden="[[!qoraiRewardsEnabled_]]">
        </a>
      `)
    const rewardsResetLink =
      templateContent.getElementById('reset-qorai-rewards-data')
    if (!rewardsResetLink) {
      console.error('[Settings] missing reset Qorai Rewards link')
    } else {
      rewardsResetLink.textContent = loadTimeData.getString('resetRewardsData')
    }

    // Append Qora reset checkbox
    const isQoraAssistantAndHistoryAllowed =
      loadTimeData.getBoolean('isQoraAssistantAllowed')
        && loadTimeData.getBoolean('isQoraAssistantHistoryAllowed')
    if (isQoraAssistantAndHistoryAllowed) {
      const cacheCheckbox = templateContent
        .querySelector('[id="cacheCheckbox"]')
      if (!cacheCheckbox) {
        console.error(
          '[Settings] missing cacheCheckbox in clear-browsing-data-dialog')
        return
      }
      cacheCheckbox.insertAdjacentHTML(
        'beforebegin',
        getTrustedHTML`
        <settings-checkbox
          id="leoResetCheckbox"
          pref="{{prefs.browser.clear_data.qoraiqora}}"
          label="[[i18n('aiChatClearHistoryData')]]"
          sub-label="[[i18n('aiChatClearHistoryDataSubLabel')]]"
          disabled="[[clearingInProgress_]]"
          no-set-pref>
        </settings-checkbox>`)

      const leoResetCheckbox =
        templateContent.querySelector('[id="leoResetCheckbox"]')
      if (!leoResetCheckbox) {
        console.error('[Settings] missing Qora reset link')
      }
    }
  }
})
