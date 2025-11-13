// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

'use strict';

window.__firefox__.includeOnce("QoraiSearchScript", function($) {
  let sendMessage = $(function(method_id) {
    return $.postNativeMessage('$<message_handler>', { 'securityToken': SECURITY_TOKEN, 'method_id': method_id});
  });

  Object.defineProperty(window, 'qorai', {
    enumerable: false,
    configurable: false,
    writable: false,
    value: {
      getCanSetDefaultSearchProvider() {
        return sendMessage(1);
      },

      setIsDefaultSearchProvider() {
        return sendMessage(2);
      }
    }
  });
});
