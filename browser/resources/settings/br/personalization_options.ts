/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import '../qorai_privacy_page/qorai_personalization_options.js'

import {RegisterPolymerTemplateModifications} from 'chrome://resources/qorai/polymer_overriding.js'

RegisterPolymerTemplateModifications({
  'settings-personalization-options': (templateContent) => {
    const metricsReportingControl = templateContent.getElementById('metricsReportingControl')
    if (!metricsReportingControl) {
      console.error(`[Qorai Settings Overrides] Couldn't find metricsReportingControl`)
    } else {
      // Removed because we need to locate metrics reportng option between ours at our settings-qorai-personalization-options
      metricsReportingControl.remove()
    }

    // searchSugestToggle is moved to search engines section.
    const searchSuggestToggleTemplate = templateContent.querySelector('template[is="dom-if"][if="[[showSearchSuggestToggle_()]]"]')
    if (!searchSuggestToggleTemplate) {
      console.error('[Qorai Settings Overrides] Could not find searchSuggestToggle template')
    } else {
      const searchSuggestToggle = searchSuggestToggleTemplate.content.getElementById('searchSuggestToggle')
      if (!searchSuggestToggle) {
        console.error('[Qorai Settings Overrides] Could not find searchSuggestToggle id')
      } else {
        searchSuggestToggle.setAttribute('hidden', 'true')
      }
    }
  },
})
