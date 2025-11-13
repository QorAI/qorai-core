// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import {pageVisibility} from './br/page_visibility.js'
import {loadTimeData} from './i18n_setup.js'
import {SettingsRoutes} from './router.js'

export default function addQoraiRoutes(r: Partial<SettingsRoutes>) {
  const isGuest = loadTimeData.getBoolean('isGuest')
  if (!r.BASIC) {
    console.error('[Settings] Routes: could not find BASIC page')
    return
  }
  if (pageVisibility.getStarted) {
    r.GET_STARTED = r.BASIC.createSection('/getStarted', 'getStarted')

    // Bring back people's /manageProfile (now in getStarted)
    if (!r.MANAGE_PROFILE) {
      r.MANAGE_PROFILE = r.GET_STARTED.createChild('/manageProfile')
      r.MANAGE_PROFILE.section = 'getStarted'
    }
    // We re-section people page into getStarted section (see people_page Qorai
    // override), so we need to adjust the route accordingly in order for the
    // direct navigation to qorai://settings/importData to work.
    if (!r.IMPORT_DATA) {
      r.IMPORT_DATA = r.GET_STARTED.createChild('/importData')
      r.IMPORT_DATA.isNavigableDialog = true
      r.IMPORT_DATA.section = 'getStarted'
    }
  }
  if (pageVisibility.origin) {
    r.ORIGIN = r.BASIC.createSection('/origin', 'origin')
  }
  r.SHIELDS = r.BASIC.createSection('/shields', 'shields')
  r.SHIELDS_ADBLOCK = r.SHIELDS.createChild('/shields/filters')

  if (loadTimeData.getBoolean('areShortcutsSupported')) {
    if (r.SYSTEM) {
      r.SHORTCUTS = r.SYSTEM.createChild('/system/shortcuts')
    } else if (!isGuest) {
      console.error('[Settings] Routes: could not find SYSTEM page')
    }
  }

  r.EXTENSIONS = r.BASIC.createSection('/extensions', 'extensions')
  r.EXTENSIONS_V2 = r.EXTENSIONS.createChild('/extensions/v2')
  if (pageVisibility.qoraiSync) {
    r.QORAI_SYNC = r.BASIC.createSection('/qoraiSync', 'qoraiSync')
    r.QORAI_SYNC_SETUP = r.QORAI_SYNC.createChild('/qoraiSync/setup')
  }
  if (pageVisibility.qoraiWallet) {
    r.QORAI_WEB3 = r.BASIC.createSection('/web3', 'web3')

    r.QORAI_WALLET_NETWORKS = r.QORAI_WEB3.createChild('/wallet/networks')
  }
  r.QORAI_NEW_TAB = r.BASIC.createSection('/newTab', 'newTab')

  if (pageVisibility.qoraAssistant) {
    r.QORAI_QORA_ASSISTANT =
      r.BASIC.createSection('/qora-ai', 'leoAssistant')

    r.QORAI_QORA_CUSTOMIZATION = r.QORAI_QORA_ASSISTANT
      .createChild('/qora-ai/customization')
  }
  if (pageVisibility.content) {
    r.QORAI_CONTENT = r.BASIC.createSection('/qoraiContent', 'content')

    // Move fonts from APPEARANCE to QORAI_CONTENT
    if (r.FONTS) {
        delete r.FONTS
    }
    r.FONTS = r.QORAI_CONTENT.createChild('/fonts')
  }
  if (pageVisibility.surveyPanelist && r.PRIVACY) {
    r.QORAI_SURVEY_PANELIST =
      r.PRIVACY.createChild('/surveyPanelist')
  }
  if (r.SEARCH) {
    r.DEFAULT_SEARCH = r.SEARCH.createChild('defaultSearch')
    r.DEFAULT_SEARCH.isNavigableDialog = true
    r.PRIVATE_SEARCH = r.SEARCH.createChild('privateSearch')
    r.PRIVATE_SEARCH.isNavigableDialog = true
  }
  if (r.SITE_SETTINGS) {
    r.SITE_SETTINGS_AUTOPLAY = r.SITE_SETTINGS.createChild('autoplay')
    const isGoogleSignInFeatureEnabled =
      loadTimeData.getBoolean('isGoogleSignInFeatureEnabled')
    if (isGoogleSignInFeatureEnabled) {
      r.SITE_SETTINGS_GOOGLE_SIGN_IN =
        r.SITE_SETTINGS.createChild('googleSignIn')
    }
    const isLocalhostAccessFeatureEnabled =
      loadTimeData.getBoolean('isLocalhostAccessFeatureEnabled')
    if (isLocalhostAccessFeatureEnabled) {
      r.SITE_SETTINGS_LOCALHOST_ACCESS = r.SITE_SETTINGS
        .createChild('localhostAccess')
    }
    const isOpenAIChatFromQoraiSearchEnabled =
      loadTimeData.getBoolean('isOpenAIChatFromQoraiSearchEnabled')
    if (isOpenAIChatFromQoraiSearchEnabled) {
      r.SITE_SETTINGS_QORAI_OPEN_AI_CHAT =
        r.SITE_SETTINGS.createChild('qoraiOpenAIChat')
    }
    const isNativeQoraiWalletFeatureEnabled =
      loadTimeData.getBoolean('isNativeQoraiWalletFeatureEnabled')
    const isCardanoDappSupportFeatureEnabled =
      loadTimeData.getBoolean('isCardanoDappSupportFeatureEnabled')
    const isQoraiWalletAllowed = loadTimeData.getBoolean('isQoraiWalletAllowed')
    if (isNativeQoraiWalletFeatureEnabled && isQoraiWalletAllowed) {
      r.SITE_SETTINGS_ETHEREUM = r.SITE_SETTINGS.createChild('ethereum')
      r.SITE_SETTINGS_SOLANA = r.SITE_SETTINGS.createChild('solana')
      if (isCardanoDappSupportFeatureEnabled) {
        r.SITE_SETTINGS_CARDANO = r.SITE_SETTINGS.createChild('cardano')
      }
    }
    r.SITE_SETTINGS_SHIELDS_STATUS = r.SITE_SETTINGS.createChild('qoraiShields')
    if (r.SITE_SETTINGS_ADS) {
      delete r.SITE_SETTINGS_ADS
    } else {
      console.error(
        '[Settings] could not find expected route site_settings_ads')
    }
    if (r.SITE_SETTINGS_AUTO_VERIFY) {
      delete r.SITE_SETTINGS_AUTO_VERIFY
    } else {
      console.error(
        '[Settings] could not find expected route site_settings_auto_verify')
    }
  } else if (!isGuest) {
    console.error('[Settings] Routes: could not find SITE_SETTINGS page')
  }
  // Autofill route is moved to advanced,
  // otherwise its sections won't show up when opened.
  if (r.AUTOFILL && r.ADVANCED) {
    r.AUTOFILL.parent = r.ADVANCED
  } else if (!isGuest) {
    console.error(
      '[Settings] Could not move autofill route to advanced route', r)
  }
  if (loadTimeData.getBoolean('isEmailAliasesEnabled') && r.AUTOFILL) {
    r.EMAIL_ALIASES = r.AUTOFILL.createChild('/email-aliases')
  }
  // Delete performance menu - system menu includes it instead.
  if (r.PERFORMANCE) {
    delete r.PERFORMANCE
  }
  // Delete storage access
  if (r.SITE_SETTINGS_STORAGE_ACCESS) {
    delete r.SITE_SETTINGS_STORAGE_ACCESS
  }
  if (r.SYNC) {
    delete r.SYNC
  }
  // Delete /syncSetup/advanced
  if (r.SYNC_ADVANCED) {
    delete r.SYNC_ADVANCED
  }
}
