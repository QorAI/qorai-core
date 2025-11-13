// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_WEB_VIEW_AUTOFILL_QORAI_WEB_VIEW_AUTOFILL_CLIENT_H_
#define QORAI_IOS_BROWSER_API_WEB_VIEW_AUTOFILL_QORAI_WEB_VIEW_AUTOFILL_CLIENT_H_

#include <memory>
#include <string>

#include "components/autofill/ios/browser/autofill_client_ios.h"
#include "ios/web_view/internal/autofill/web_view_autofill_client_ios.h"

namespace autofill {

// An autofill client for QoraiWebView's
//
// We create a Qorai subclass of the standard WebView autofill client to allow
// us to create one using Chrome Profile's rather than WebViewBrowserState and
// to ensure we implement GetAppLocale correcty using the main Chrome
// application context.
class QoraiWebViewAutofillClientIOS : public WebViewAutofillClientIOS {
 public:
  static std::unique_ptr<WebViewAutofillClientIOS> Create(
      web::WebState* web_state,
      id<CWVAutofillClientIOSBridge, AutofillDriverIOSBridge> bridge);

  using WebViewAutofillClientIOS::WebViewAutofillClientIOS;

  const std::string& GetAppLocale() const override;
};
}  // namespace autofill

#endif  // QORAI_IOS_BROWSER_API_WEB_VIEW_AUTOFILL_QORAI_WEB_VIEW_AUTOFILL_CLIENT_H_
