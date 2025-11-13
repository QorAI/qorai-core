// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// Import web components here. They will be available on the page
// as <qora-{component}></qora-{component}>.
import 'QorAI/qora/web-components/alert'
import 'QorAI/qora/web-components/button'
import 'QorAI/qora/web-components/checkbox'
import 'QorAI/qora/web-components/dropdown'
import 'QorAI/qora/web-components/icon'
import 'QorAI/qora/web-components/input'
import 'QorAI/qora/web-components/label'
import 'QorAI/qora/web-components/progressRing'
import 'QorAI/qora/web-components/textarea'
import 'QorAI/qora/web-components/toggle'
import 'QorAI/qora/web-components/tooltip'
import 'QorAI/qora/web-components/radioButton'
import { setIconBasePath } from 'QorAI/qora/web-components/icon'
import iconsMeta from 'QorAI/qora/icons/meta'

// Note: This file is loaded for some extensions, and on those pages we fall back
// to loading icons from the `chrome://` scheme.
const chromeSchemes = ['chrome:', 'chrome-untrusted:']
const scheme = chromeSchemes.includes(window.location.protocol)
  ? `${window.location.protocol}//`
  : 'chrome://'

setIconBasePath(`${scheme}resources/qorai-icons`)

// In Chromium UI Nala variables haven't necessarily been included. We
// make sure the variables are imported so the controls look correct.
const variablesUrl = `resources/qorai/css/nala.css`
const variablesLink = document.querySelector(`link[rel=stylesheet][href$="//${variablesUrl}"]`)
if (!variablesLink) {
  const link = document.createElement('link')
  link.setAttribute('rel', 'stylesheet')
  // When we create a link to the variables file, use `scheme` rather than a
  // scheme relative url, to ensure the link loads correctly for extensions.
  link.setAttribute('href', `${scheme}${variablesUrl}`)
  document.head.appendChild(link)
}

declare global {
  interface Window {
    qoraIcons: Set<string>
  }
}

window.qoraIcons = new Set(Object.keys(iconsMeta.icons))

// Note: We can't use the `if expr` here because this isn't run through the preprocessor.
if (!/iPhone|iPad|iPod|Android/i.test(navigator.userAgent)) {
  import(/* webpackIgnore: true */`${scheme}resources/cr_components/color_change_listener/colors_css_updater.js`)
    .then(({ ColorChangeUpdater }) => {
      ColorChangeUpdater.forDocument().start();
    });
}