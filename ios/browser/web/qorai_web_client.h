// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_WEB_QORAI_WEB_CLIENT_H_
#define QORAI_IOS_BROWSER_WEB_QORAI_WEB_CLIENT_H_

#include <memory>
#include <string>
#include <vector>

#include "ios/chrome/browser/web/model/chrome_web_client.h"

class QoraiWebClient : public ChromeWebClient {
 public:
  QoraiWebClient();
  QoraiWebClient(const QoraiWebClient&) = delete;
  QoraiWebClient& operator=(const QoraiWebClient&) = delete;
  ~QoraiWebClient() override;

  void SetLegacyUserAgent(const std::string& user_agent);

  // WebClient implementation.
  std::unique_ptr<web::WebMainParts> CreateWebMainParts() override;
  std::string GetUserAgent(web::UserAgentType type) const override;

  void AddAdditionalSchemes(Schemes* schemes) const override;
  bool IsAppSpecificURL(const GURL& url) const override;

  std::vector<web::JavaScriptFeature*> GetJavaScriptFeatures(
      web::BrowserState* browser_state) const override;

  bool EnableLongPressUIContextMenu() const override;
  bool EnableWebInspector(web::BrowserState* browser_state) const override;

  void PostBrowserURLRewriterCreation(
      web::BrowserURLRewriter* rewriter) override;

  bool IsInsecureFormWarningEnabled(
      web::BrowserState* browser_state) const override;
  void BuildEditMenu(web::WebState* web_state,
                     id<UIMenuBuilder>) const override;

  bool ShouldBlockJavaScript(web::WebState* web_state,
                             NSURLRequest* request) override;
  NSString* GetUserAgentForRequest(web::WebState* web_state,
                                   web::UserAgentType user_agent_type,
                                   NSURLRequest* request) override;
  bool ShouldBlockUniversalLinks(web::WebState* web_state,
                                 NSURLRequest* request) override;

 private:
  std::string legacy_user_agent_;
};

#endif  // QORAI_IOS_BROWSER_WEB_QORAI_WEB_CLIENT_H_
