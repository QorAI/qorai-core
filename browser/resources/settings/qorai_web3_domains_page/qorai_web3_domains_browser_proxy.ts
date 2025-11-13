// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import {DropdownMenuOptionList} from '../controls/settings_dropdown_menu.js';
import {sendWithPromise} from 'chrome://resources/js/cr.js'

import {loadTimeData} from '../i18n_setup.js';

export interface QoraiWeb3DomainsBrowserProxy {
  getDecentralizedDnsResolveMethodList(): Promise<DropdownMenuOptionList>
  getEnsOffchainResolveMethodList(): Promise<DropdownMenuOptionList>
}

export class QoraiWeb3DomainsBrowserProxyImpl
  implements QoraiWeb3DomainsBrowserProxy {
  getDecentralizedDnsResolveMethodList() {
    return sendWithPromise('getDecentralizedDnsResolveMethodList')
  }

  getEnsOffchainResolveMethodList() {
    return sendWithPromise('getEnsOffchainResolveMethodList')
  }

  static getInstance(): QoraiWeb3DomainsBrowserProxy {
    return instance || (instance = new QoraiWeb3DomainsBrowserProxyImpl())
  }
}

let instance: QoraiWeb3DomainsBrowserProxy|null = null
