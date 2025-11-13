// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_WEB_VIEW_PASSWORDS_QORAI_WEB_VIEW_PASSWORD_MANAGER_CLIENT_H_
#define QORAI_IOS_BROWSER_API_WEB_VIEW_PASSWORDS_QORAI_WEB_VIEW_PASSWORD_MANAGER_CLIENT_H_

#include "ios/web_view/internal/passwords/web_view_password_manager_client.h"

// An password manager client for QoraiWebView's
//
// We create a Qorai subclass of the standard WebView pasword manager client
// to allow to ensure we implement GetLocalStatePrefs correcty using the main
// Chrome application context.
class QoraiWebViewPasswordManagerClient
    : public ios_web_view::WebViewPasswordManagerClient {
 public:
  using WebViewPasswordManagerClient::WebViewPasswordManagerClient;

  // password_manager::PasswordManagerClient implementation.
  PrefService* GetLocalStatePrefs() const override;
};

#endif  // QORAI_IOS_BROWSER_API_WEB_VIEW_PASSWORDS_QORAI_WEB_VIEW_PASSWORD_MANAGER_CLIENT_H_
