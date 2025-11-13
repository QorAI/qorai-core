// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import {sendWithPromise} from 'chrome://resources/js/cr.js';

export interface QoraiVPNBrowserProxy {
  isWireguardServiceInstalled(): Promise<boolean>;
  isQoraiVpnConnected(): Promise<boolean>;
}

export class QoraiVPNBrowserProxyImpl implements QoraiVPNBrowserProxy {
  isWireguardServiceInstalled () {
    return sendWithPromise('isWireguardServiceInstalled');
  }

  isQoraiVpnConnected () {
    return sendWithPromise('isQoraiVpnConnected');
  }

  static getInstance(): QoraiVPNBrowserProxy {
    return instance || (instance = new QoraiVPNBrowserProxyImpl())
  }
}

let instance: QoraiVPNBrowserProxy|null = null
