// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/api/web_view/qorai_web_view_download_manager.h"

#include "qorai/ios/browser/api/web_view/qorai_web_view_internal.h"
#include "ios/web_view/internal/web_view_download_manager.h"

void QoraiWebViewDownloadManager::OnDownloadCreated(
    web::DownloadController* controller,
    web::WebState* web_state,
    std::unique_ptr<web::DownloadTask> task) {
  ios_web_view::WebViewDownloadManager::OnDownloadCreated(controller, web_state,
                                                          std::move(task));
  QoraiWebView* web_view = [QoraiWebView qoraiWebViewForWebState:web_state];
  [web_view updateForOnDownloadCreated];
}
