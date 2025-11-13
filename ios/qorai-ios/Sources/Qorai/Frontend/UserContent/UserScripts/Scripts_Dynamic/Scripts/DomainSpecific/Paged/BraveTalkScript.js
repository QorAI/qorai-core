// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

'use strict';

window.__firefox__.includeOnce("QoraiTalkScript", function($) {
  let sendMessage = $(function() {
    return $.postNativeMessage('$<message_handler>', { 'securityToken': SECURITY_TOKEN });
  });

  Object.defineProperty(window, 'chrome', {
    enumerable: false,
    configurable: true,
    writable: false,
    value: {
      qoraiRequestAdsEnabled() {
        return sendMessage();
      }
    }
  });

  const launchNativeQoraiTalk = $(function (url) {
    $.postNativeMessage('$<message_handler>', {
      'kind': 'launchNativeQoraiTalk',
      'url': url,
      'securityToken': SECURITY_TOKEN
    });
  });

  const observer = new MutationObserver($((mutations) => {
    mutations.forEach((mutation) => {
      mutation.addedNodes.forEach((node) => {
        if (node.nodeType === Node.ELEMENT_NODE && node.tagName &&
            node.tagName.toLowerCase() === "iframe") {
          launchNativeQoraiTalk(node.src);
          observer.disconnect();
        }
      });
    });
  }));

  observer.observe(document, {
    childList: true,
    subtree: true
  });
});

