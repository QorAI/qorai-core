// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

window.__firefox__.includeOnce("PlaylistFolderSharingScript", function($) {
  let sendMessage = $(function(pageUrl) {
    $.postNativeMessage('$<message_handler>', {
      "securityToken": SECURITY_TOKEN,
      "pageUrl": pageUrl
    });
  });

  if (!window.qorai) {
    window.qorai = {};
  }

  if (!window.qorai.playlist) {
    window.qorai.playlist = {};
    window.qorai.playlist.open = $(function(pageUrl) {
      sendMessage(pageUrl);
    });
  }
});
