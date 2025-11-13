// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#import "qorai/ios/browser/web/qorai_web_client.h"

#include "base/feature_list.h"
#include "base/functional/bind.h"
#include "base/ios/ns_error_util.h"
#include "base/strings/sys_string_conversions.h"
#include "qorai/components/constants/url_constants.h"
#include "qorai/ios/browser/api/web_view/qorai_web_view_internal.h"
#include "qorai/ios/browser/ui/web_view/features.h"
#include "qorai/ios/browser/web/qorai_web_main_parts.h"
#include "components/autofill/ios/browser/autofill_java_script_feature.h"
#include "components/autofill/ios/browser/suggestion_controller_java_script_feature.h"
#include "components/autofill/ios/form_util/form_handlers_java_script_feature.h"
#include "components/password_manager/ios/password_manager_java_script_feature.h"
#import "components/translate/ios/browser/translate_java_script_feature.h"
#include "ios/chrome/browser/shared/model/url/chrome_url_constants.h"
#include "ios/chrome/browser/web/model/chrome_web_client.h"
#import "ios/components/security_interstitials/ios_security_interstitial_java_script_feature.h"
#import "ios/components/security_interstitials/lookalikes/lookalike_url_error.h"
#import "ios/components/security_interstitials/safe_browsing/safe_browsing_error.h"
#include "ios/components/webui/web_ui_url_constants.h"
#import "ios/public/provider/chrome/browser/url_rewriters/url_rewriters_api.h"
#include "ios/web/common/url_scheme_util.h"
#include "ios/web/common/user_agent.h"
#import "ios/web/public/navigation/browser_url_rewriter.h"
#import "ios/web_view/internal/cwv_ssl_error_handler_internal.h"
#import "ios/web_view/internal/cwv_web_view_internal.h"
#import "ios/web_view/public/cwv_navigation_delegate.h"
#import "net/base/apple/url_conversions.h"
#include "url/gurl.h"

QoraiWebClient::QoraiWebClient() {}

QoraiWebClient::~QoraiWebClient() {}

std::unique_ptr<web::WebMainParts> QoraiWebClient::CreateWebMainParts() {
  return std::make_unique<QoraiWebMainParts>(
      *base::CommandLine::ForCurrentProcess());
}

std::string QoraiWebClient::GetUserAgent(web::UserAgentType type) const {
  if (!legacy_user_agent_.empty()) {
    return legacy_user_agent_;
  }
  return ChromeWebClient::GetUserAgent(type);
}

void QoraiWebClient::AddAdditionalSchemes(Schemes* schemes) const {
  ChromeWebClient::AddAdditionalSchemes(schemes);

  schemes->standard_schemes.push_back(kQoraiUIScheme);
  schemes->secure_schemes.push_back(kQoraiUIScheme);

  schemes->standard_schemes.push_back(kChromeUIUntrustedScheme);
  schemes->secure_schemes.push_back(kChromeUIUntrustedScheme);
}

bool QoraiWebClient::IsAppSpecificURL(const GURL& url) const {
  // temporarily add `internal://` scheme handling until those pages can be
  // ported to WebUI
  return ChromeWebClient::IsAppSpecificURL(url) ||
         url.SchemeIs(kQoraiUIScheme) ||
         url.SchemeIs(kChromeUIUntrustedScheme) || url.SchemeIs("internal");
}

bool WillHandleQoraiURLRedirect(GURL* url, web::BrowserState* browser_state) {
  if (url->SchemeIs(kQoraiUIScheme)) {
    GURL::Replacements replacements;
    replacements.SetSchemeStr(kChromeUIScheme);
    *url = url->ReplaceComponents(replacements);
  }
  return false;
}

std::vector<web::JavaScriptFeature*> QoraiWebClient::GetJavaScriptFeatures(
    web::BrowserState* browser_state) const {
  // Add any JavaScriptFeature's from Chromium or Qorai as needed
  std::vector<web::JavaScriptFeature*> features;
  features.push_back(
      security_interstitials::IOSSecurityInterstitialJavaScriptFeature::
          GetInstance());
  if (base::FeatureList::IsEnabled(
          qorai::features::kUseChromiumWebViewsAutofill)) {
    features.push_back(
        password_manager::PasswordManagerJavaScriptFeature::GetInstance());
    features.push_back(autofill::AutofillJavaScriptFeature::GetInstance());
    features.push_back(autofill::FormHandlersJavaScriptFeature::GetInstance());
    features.push_back(
        autofill::SuggestionControllerJavaScriptFeature::GetInstance());
  }
  return features;
}

void QoraiWebClient::PostBrowserURLRewriterCreation(
    web::BrowserURLRewriter* rewriter) {
  rewriter->AddURLRewriter(&WillHandleQoraiURLRedirect);
  ChromeWebClient::PostBrowserURLRewriterCreation(rewriter);
}

bool QoraiWebClient::EnableLongPressUIContextMenu() const {
  return CWVWebView.chromeContextMenuEnabled;
}

bool QoraiWebClient::EnableWebInspector(
    web::BrowserState* browser_state) const {
  return CWVWebView.webInspectorEnabled;
}

void QoraiWebClient::SetLegacyUserAgent(const std::string& user_agent) {
  legacy_user_agent_ = user_agent;
}

bool QoraiWebClient::IsInsecureFormWarningEnabled(
    web::BrowserState* browser_state) const {
  // TODO: Remove when qorai/qorai-browser#46667 is implemented
  return false;
}

void QoraiWebClient::BuildEditMenu(web::WebState* web_state,
                                   id<UIMenuBuilder> builder) const {
  QoraiWebView* webView = [QoraiWebView qoraiWebViewForWebState:web_state];
  if (!webView) {
    return;
  }
  id<QoraiWebViewUIDelegate> uiDelegate = webView.UIDelegate;

  if ([uiDelegate respondsToSelector:@selector(webView:
                                         buildEditMenuWithBuilder:)]) {
    return [uiDelegate webView:webView buildEditMenuWithBuilder:builder];
  }
}

bool QoraiWebClient::ShouldBlockJavaScript(web::WebState* webState,
                                           NSURLRequest* request) {
  if (!web::UrlHasWebScheme(request.URL)) {
    return false;
  }
  QoraiWebView* webView = [QoraiWebView qoraiWebViewForWebState:webState];
  if (!webView) {
    return false;
  }
  id<QoraiWebViewNavigationDelegate> navigationDelegate =
      webView.navigationDelegate;

  if ([navigationDelegate respondsToSelector:@selector
                          (webView:shouldBlockJavaScriptForRequest:)]) {
    return [navigationDelegate webView:webView
        shouldBlockJavaScriptForRequest:request];
  }
  return false;
}

bool QoraiWebClient::ShouldBlockUniversalLinks(web::WebState* webState,
                                               NSURLRequest* request) {
  QoraiWebView* webView = [QoraiWebView qoraiWebViewForWebState:webState];
  if (!webView) {
    return false;
  }
  id<QoraiWebViewNavigationDelegate> navigationDelegate =
      webView.navigationDelegate;

  if ([navigationDelegate respondsToSelector:@selector
                          (webView:shouldBlockUniversalLinksForRequest:)]) {
    return [navigationDelegate webView:webView
        shouldBlockUniversalLinksForRequest:request];
  }
  return false;
}

NSString* QoraiWebClient::GetUserAgentForRequest(
    web::WebState* webState,
    web::UserAgentType userAgentType,
    NSURLRequest* request) {
  QoraiWebView* webView = [QoraiWebView qoraiWebViewForWebState:webState];
  if (!webView) {
    return nil;
  }

  id<QoraiWebViewNavigationDelegate> navigationDelegate =
      webView.navigationDelegate;
  if ([navigationDelegate respondsToSelector:@selector
                          (webView:userAgentForUserAgentType:request:)]) {
    return [navigationDelegate
                          webView:webView
        userAgentForUserAgentType:static_cast<CWVUserAgentType>(userAgentType)
                          request:request];
  }
  return nil;
}
