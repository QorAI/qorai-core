/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import {RegisterPolymerTemplateModifications} from 'chrome://resources/qorai/polymer_overriding.js'

RegisterPolymerTemplateModifications({
    'settings-safety-check-page': (templateContent) => {
        const safetyCheckParentLabel = templateContent.querySelector('.flex,.cr-padded-text')
        if (!safetyCheckParentLabel) {
            console.error('[Qorai Settings Overrides] Could not find safetyCheckParentLabel on safety page.')
        } else {
            safetyCheckParentLabel.style.cssText = 'padding-right: 32px;'
        }
    }
})
