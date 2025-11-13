// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { html, RegisterPolymerPrototypeModification, RegisterPolymerTemplateModifications } from 'chrome://resources/qorai/polymer_overriding.js'
import { routes } from '../route.js';
import type { Route } from '../router.js';

// Modify the prototype to handle route changes
RegisterPolymerPrototypeModification({
  'settings-appearance-page-index': (prototype) => {
    prototype.currentRouteChanged = function (newRoute: Route) {
      const showDefaultViews = () => {
        this.$.viewManager.switchViews(
          ['parent', 'tabs', 'sidebar'], 'no-animation', 'no-animation');
      }

      switch (newRoute) {
        case routes.BASIC:
        case routes.APPEARANCE:
          showDefaultViews();
          break;
      }
    }
  }
})

RegisterPolymerTemplateModifications({
  'settings-appearance-page-index': (template) => {
    // Support having multiple cards active at the same time.
    template.prepend(html`
      <style>
        cr-view-manager [slot=view]:not(.closing) {
          position: initial;
        }
      </style>
    `)

    const viewManager = template.querySelector('cr-view-manager')
    if (!viewManager) {
      console.error('View manager not found')
      return
    }

    // Fonts page is rendered in the content subpage.
    viewManager.querySelector('#fonts')?.remove()

    // Append tabs and sidebar settings to the appearance page.
    viewManager.append(html`
      <settings-qorai-appearance-tabs
        id="tabs"
        slot="view"
        prefs="{{prefs}}"
        in-search-mode="[[inSearchMode_]]">
      </settings-qorai-appearance-tabs>

      <settings-qorai-appearance-sidebar
        id="sidebar"
        slot="view"
        prefs="{{prefs}}"
        in-search-mode="[[inSearchMode_]]">
      </settings-qorai-appearance-sidebar>`)
  }
})
