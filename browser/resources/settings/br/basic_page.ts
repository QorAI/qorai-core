// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import '../qorai_appearance_page/sidebar.js'
import '../qorai_appearance_page/tabs.js'
import '../qorai_content_page/content.js'
import '../qorai_content_page/playlist.js'
// <if expr="enable_speedreader">
import '../qorai_content_page/speedreader.js'
// </if>
import '../qorai_data_collection_page/qorai_data_collection_page.js'
import '../qorai_default_extensions_page/qorai_default_extensions_page.js'
import '../qorai_new_tab_page/qorai_new_tab_page.js'
import '../qorai_origin_page/qorai_origin_page.js'
import '../qorai_search_engines_page/qorai_search_engines_page.js'
import '../qorai_sync_page/qorai_sync_page_index.js'
import '../qorai_sync_page/qorai_sync_manage_devices_page.js'
// <if expr="enable_tor">
import '../qorai_tor_page/qorai_tor_subpage.js'
// </if>
import '../qorai_wallet_page/qorai_wallet_page.js'
import '../qorai_web3_domains_page/qorai_web3_domains_page.js'
import '../default_qorai_shields_page/default_qorai_shields_page.js'
import '../getting_started_page/getting_started.js'
import '../social_blocking_page/social_blocking_page.js'
import '../qorai_qora_assistant_page/qorai_qora_assistant_page.js'
import '../qorai_qora_assistant_page/model_list_section.js'
import '../qorai_qora_assistant_page/personalization.js'

// <if expr="enable_containers">
import '../qorai_content_page/containers.js'
// </if>

import {
  html,
  RegisterStyleOverride,
  RegisterPolymerTemplateModifications
} from 'chrome://resources/qorai/polymer_overriding.js'


RegisterStyleOverride(
  'settings-basic-page',
  html`
    <style>
      :host {
        min-width: 544px !important;
      }
    </style>
  ` as HTMLTemplateElement
)

