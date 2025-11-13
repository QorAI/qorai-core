// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { injectStyle } from '//resources/qorai/lit_overriding.js'
import { css } from '//resources/lit/v3_0/lit.rollup.js'
import { DownloadsItemElement } from './item-chromium.js'

injectStyle(DownloadsItemElement, css`
    #progress {
        --cr-progress-active-color: var(--qora-color-icon-interactive) !important;
    }
    @media (prefers-color-scheme: light) {
        #content:not(.is-active) {
            /* Color for "filled cards" */
            background-color: var(--qora-color-container-highlight) !important;
        }
    }
`)

export * from './item-chromium.js'
