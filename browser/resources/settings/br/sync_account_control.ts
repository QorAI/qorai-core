/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import {RegisterPolymerComponentProperties, RegisterPolymerTemplateModifications} from 'chrome://resources/qorai/polymer_overriding.js'

RegisterPolymerTemplateModifications({
  'settings-sync-account-control': (templateContent) => {
    const banner = templateContent.querySelector('#banner')
    if (!banner) {
      console.error('[Qorai Settings Overrides] Could not find sync banner')
      return
    }
    const promoHeader = templateContent.querySelector('#promo-header')
    if (!promoHeader) {
      console.error('[Qorai Settings Overrides] Could not find promo header')
      return
    }
    banner.hidden = true
    promoHeader.hidden = true
  }
})

RegisterPolymerComponentProperties({
  'settings-sync-account-control': {
    shouldShowAvatarRow_: {
      type: Boolean,
      value: false
    }
  }
})
