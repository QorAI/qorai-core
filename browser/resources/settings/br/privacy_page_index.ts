/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import {
  RegisterPolymerTemplateModifications,
  RegisterPolymerPrototypeModification,
  html
} from 'chrome://resources/qorai/polymer_overriding.js'
import type { Route } from '../router.js';
import { routes } from '../route.js';
import { loadTimeData } from "../i18n_setup.js"
import { pageVisibility } from './page_visibility.js'
import '../qorai_survey_panelist_page/qorai_survey_panelist_page.js'
import '../site_settings/site_settings_autoplay.js'
import '../site_settings/site_settings_localhost.js'
import '../site_settings/site_settings_cardano.js'
import '../site_settings/site_settings_ethereum.js'
import '../site_settings/site_settings_google.js'
import '../site_settings/site_settings_shields.js'
import '../site_settings/site_settings_qorai_ai.js'
import '../site_settings/site_settings_solana.js'
import { ContentSettingsTypes } from '../site_settings/constants.js';

RegisterPolymerPrototypeModification({
  'settings-privacy-page-index': (prototype) => {
    const oldGetDefaultViews = prototype.getDefaultViews_;
    prototype.getDefaultViews_ = function () {
      const views = oldGetDefaultViews.call(this)
        // Hide the privacy guide promo view.
        .filter((v: string) => v !== 'privacyGuidePromo');

      // Add dataCollection view.
      views.splice(1, 0, 'dataCollection');

      // <if expr="enable_tor">
      // Add tor view if it should be shown.
      if (pageVisibility.qoraiTor) {
        views.splice(1, 0, 'tor');
      }
      // </if>

      return views;
    }

    const oldGetViewIdsForRoute = prototype.getViewIdsForRoute_;
    prototype.getViewIdsForRoute_ = function (route: Route) {
      if (route === routes.QORAI_SURVEY_PANELIST) {
        return ['surveyPanelist'];
      }
      return oldGetViewIdsForRoute.call(this, route);
    }
  }
})

RegisterPolymerTemplateModifications({
  'settings-privacy-page-index': (templateContent) => {
    const viewManager = templateContent.querySelector('#viewManager')
    if (!viewManager) {
      throw new Error("Couldn't find a view manager for settings-privacy-page-index!")
    }

    // Hide the privacy guide promo
    const privacyGuidePromoTemplate = templateContent.
      querySelector('template[is=dom-if][if="[[isPrivacyGuideAvailable]]"]')
    if (privacyGuidePromoTemplate) {
      privacyGuidePromoTemplate.remove()
    } else {
      throw new Error('[Settings] Missing privacyGuidePromoTemplate')
    }

    // <if expr="enable_tor">
    viewManager.appendChild(html`<template is="dom-if"
        if="[[showPage_(pageVisibility_.qoraiTor)]]">
      <settings-qorai-tor-subpage
        id="tor"
        slot="view"
        prefs="{{prefs}}"
        in-search-mode="[[inSearchMode_]]">
      </settings-qorai-tor-subpage>
    </template>`)
    // </if>

    viewManager.appendChild(html`<settings-qorai-data-collection-subpage
      id="dataCollection"
      slot="view"
      prefs="{{prefs}}"
      in-search-mode="[[inSearchMode_]]">
    </settings-qorai-data-collection-subpage>`)

    if (loadTimeData.getBoolean('isSurveyPanelistAllowed')) {
      viewManager.appendChild(html`<settings-qorai-survey-panelist-page
        id="surveyPanelist"
        data-parent-view-id="dataCollection"
        slot="view"
        prefs="{{prefs}}"
        in-search-mode="[[inSearchMode_]]">
      </settings-qorai-survey-panelist-page>`)
    }

    if (loadTimeData.getBoolean('isGoogleSignInFeatureEnabled')) {
      viewManager.appendChild(html`
        <site-settings-google-page
            id="${ContentSettingsTypes.GOOGLE_SIGN_IN}"
            route-path$="[[routes_.SITE_SETTINGS_GOOGLE_SIGN_IN.path]]"
            data-parent-view-id="siteSettings"
            slot="view"
            in-search-mode="[[inSearchMode_]]">
          </site-settings-google-page>`)
    }

    viewManager.appendChild(html`
      <site-settings-shields-page
          id="${ContentSettingsTypes.QORAI_SHIELDS}"
          route-path$="[[routes_.SITE_SETTINGS_SHIELDS_STATUS.path]]"
          data-parent-view-id="siteSettings"
          slot="view"
          in-search-mode="[[inSearchMode_]]">
        </site-settings-shields-page>`)

    viewManager.appendChild(html`
      <site-settings-autoplay-page
          id="${ContentSettingsTypes.AUTOPLAY}"
          route-path$="[[routes_.SITE_SETTINGS_AUTOPLAY.path]]"
          data-parent-view-id="siteSettings"
          slot="view"
          in-search-mode="[[inSearchMode_]]">
        </site-settings-autoplay-page>`)

    if (loadTimeData.getBoolean('isLocalhostAccessFeatureEnabled')) {
      viewManager.appendChild(html`
            <site-settings-localhost-page
                id="${ContentSettingsTypes.LOCALHOST_ACCESS}"
                route-path$="[[routes_.SITE_SETTINGS_LOCALHOST_ACCESS.path]]"
                data-parent-view-id="siteSettings"
                slot="view"
                in-search-mode="[[inSearchMode_]]">
              </site-settings-localhost-page>`)
    }

    if (loadTimeData.getBoolean('isOpenAIChatFromQoraiSearchEnabled')) {
      viewManager.appendChild(html`
      <site-settings-qorai-ai-page
          id=${ContentSettingsTypes.QORAI_OPEN_AI_CHAT}
          route-path$="[[routes_.SITE_SETTINGS_QORAI_OPEN_AI_CHAT.path]]"
          data-parent-view-id="siteSettings"
          slot="view"
          in-search-mode="[[inSearchMode_]]">
        </site-settings-qorai-ai-page>`)
      }

      if (loadTimeData.getBoolean('isQoraiWalletAllowed') && loadTimeData.getBoolean('isNativeQoraiWalletFeatureEnabled')) {
        viewManager.appendChild(html`
          <site-settings-ethereum-page
              id="${ContentSettingsTypes.ETHEREUM}"
              route-path$="[[routes_.SITE_SETTINGS_ETHEREUM.path]]"
              data-parent-view-id="siteSettings"
              slot="view"
              in-search-mode="[[inSearchMode_]]">
            </site-settings-ethereum-page>`)

        viewManager.appendChild(html`
          <site-settings-solana-page
              id="${ContentSettingsTypes.SOLANA}"
              route-path$="[[routes_.SITE_SETTINGS_SOLANA.path]]"
              data-parent-view-id="siteSettings"
              slot="view"
              in-search-mode="[[inSearchMode_]]">
            </site-settings-solana-page>`)

        if (loadTimeData.getBoolean('isCardanoDappSupportFeatureEnabled')) {
          viewManager.appendChild(html`
            <site-settings-cardano-page
                id="${ContentSettingsTypes.CARDANO}"
                route-path$="[[routes_.SITE_SETTINGS_CARDANO.path]]"
                data-parent-view-id="siteSettings"
                slot="view"
                in-search-mode="[[inSearchMode_]]">
              </site-settings-cardano-page>`)
        }
    }

    // Move the safety hub to the end of the page
    const safetyHubTemplate = templateContent.querySelector(
      'template[is=dom-if][if="[[showPage_(pageVisibility_.safetyHub)]]"]')
    if (safetyHubTemplate && safetyHubTemplate.parentElement) {
      safetyHubTemplate.parentElement.appendChild(safetyHubTemplate)
    } else {
      throw new Error('[Settings] Missing safetyHubTemplate')
    }
  }
})
