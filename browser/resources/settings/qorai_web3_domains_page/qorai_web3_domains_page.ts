// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import {DropdownMenuOptionList} from '../controls/settings_dropdown_menu.js';
import {PrefsMixin, PrefsMixinInterface} from '/shared/settings/prefs/prefs_mixin.js';
import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'

import {QoraiWeb3DomainsBrowserProxyImpl} from './qorai_web3_domains_browser_proxy.js'
import {getTemplate} from './qorai_web3_domains_page.html.js'

const SettingQoraiWeb3DomainsPageElementBase = PrefsMixin(PolymerElement) as {
  new (): PolymerElement & PrefsMixinInterface
}

export class SettingQoraiWeb3DomainsPageElement
  extends SettingQoraiWeb3DomainsPageElementBase {
  static get is() {
    return 'settings-qorai-web3-domains-page'
  }

  static get template() {
    return getTemplate()
  }

  static get properties() {
    return {
      resolveMethod_: Array,
      ensOffchainResolveMethod_: Array,
      showEnsOffchainLookupRow_: {
        type: Boolean,
        computed: 'computeShowEnsOffchainLookupRow_(prefs.*)',
      },
    }
  }

  private browserProxy_ = QoraiWeb3DomainsBrowserProxyImpl.getInstance()
  declare resolveMethod_: DropdownMenuOptionList
  declare ensOffchainResolveMethod_: DropdownMenuOptionList
  declare showEnsOffchainLookupRow_: boolean

  override ready() {
    super.ready()

    this.browserProxy_.getDecentralizedDnsResolveMethodList().then(list => {
      this.resolveMethod_ = list
    })
    this.browserProxy_.getEnsOffchainResolveMethodList().then(list => {
      this.ensOffchainResolveMethod_ = list
    })
  }

  computeShowEnsOffchainLookupRow_() {
    return !!this.prefs && this.getPref('qorai.ens.resolve_method').value === 3
  }
}

customElements.define(
  SettingQoraiWeb3DomainsPageElement.is, SettingQoraiWeb3DomainsPageElement)
