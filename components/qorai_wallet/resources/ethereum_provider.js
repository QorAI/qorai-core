// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

;(function () {
  if (!window.qoraiEthereum) {
    return
  }
  var EventEmitter = require('events')
  var QoraiWeb3ProviderEventEmitter = new EventEmitter()
  $Object.defineProperties(window.qoraiEthereum, {
    on: {
      value: QoraiWeb3ProviderEventEmitter.on,
      writable: false,
    },
    emit: {
      value: QoraiWeb3ProviderEventEmitter.emit,
      writable: false,
    },
    removeListener: {
      value: QoraiWeb3ProviderEventEmitter.removeListener,
      writable: false,
    },
    removeAllListeners: {
      value: QoraiWeb3ProviderEventEmitter.removeAllListeners,
      writable: false,
    },
  })
})()
