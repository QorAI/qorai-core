// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import '//resources/cr_elements/md_select.css.js'
import 'chrome://resources/qorai/qora.bundle.js'
import { I18nMixin } from 'chrome://resources/cr_elements/i18n_mixin.js'
import { PolymerElement } from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'
import { WebUiListenerMixin } from 'chrome://resources/cr_elements/web_ui_listener_mixin.js'
import { PrefsMixin } from '/shared/settings/prefs/prefs_mixin.js'
import { loadTimeData } from '../i18n_setup.js'
import { getTemplate } from './qorai_survey_panelist_page.html.js'

const QoraiSurveyPanelistPageBaseElement =
  WebUiListenerMixin(I18nMixin(PrefsMixin(PolymerElement)))

/**
 * 'settings-qorai-survey-panalist-page' is the settings page containing
 * qorai's Survey Panelist features.
 */
class QoraiSurveyPanelistPageElement extends QoraiSurveyPanelistPageBaseElement {
  static get is() {
    return 'settings-qorai-survey-panelist-page'
  }

  static get template() {
    return getTemplate()
  }

  onSurveyPanelistLearnMoreLinkClick_() {
    window.open(loadTimeData.getString('qoraiSurveyPanelistLearnMoreURL'), "_blank", "noopener noreferrer")
  }
}

customElements.define(
  QoraiSurveyPanelistPageElement.is, QoraiSurveyPanelistPageElement)
