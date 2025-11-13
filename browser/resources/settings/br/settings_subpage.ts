// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import {RegisterStyleOverride} from 'chrome://resources/qorai/polymer_overriding.js'
import {html} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'

RegisterStyleOverride(
  'settings-subpage', html`
  <style include="settings-shared">
    :host {
        min-height: auto !important;
        display: inline;
        position: relative;
    }
    :host(:not(.multi-card)) {
        background-color: var(--qora-color-page-background) !important;
        box-shadow: none !important;
    }
    :host(:not(.multi-card):not([id=safetyHub])) slot {
        box-shadow: var(--qora-effect-elevation-01) !important;
        background-color: var(--qora-color-container-background) !important;
        border-radius: var(--qora-radius-m) !important;
        display: block;
        padding-bottom: var(--qora-spacing-2xl);
    }
    #headerLine {
        padding-top: 0 !important;
        padding-left: var(--qora-spacing-m) !important;
        padding-right: var(--qora-spacing-m) !important;
        padding-bottom: 0 !important;
        margin-top: var(--cr-section-vertical-margin);
    }
    .cr-title-text {
        color: var(--cr-title-text-color);
        font-weight: 600 !important;
        font-size: var(--qora-typography-heading-h4-font-size) !important;
    }
  </style>`
)
