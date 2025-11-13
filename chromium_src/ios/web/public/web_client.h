// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_IOS_WEB_PUBLIC_WEB_CLIENT_H_
#define QORAI_CHROMIUM_SRC_IOS_WEB_PUBLIC_WEB_CLIENT_H_

#import <Foundation/Foundation.h>

#include "ios/web/common/user_agent.h"

namespace web {
class WebState;
}

// Add methods to override in QoraiWebClient for QoraiCRWWKNavigationHandler
#define IsBrowserLockdownModeEnabled                                           \
  ShouldBlockJavaScript(web::WebState* web_state, NSURLRequest* request);      \
  virtual NSString* GetUserAgentForRequest(web::WebState* web_state,           \
                                           web::UserAgentType user_agent_type, \
                                           NSURLRequest* request);             \
  virtual bool ShouldBlockUniversalLinks(web::WebState* web_state,             \
                                         NSURLRequest* request);               \
  virtual bool IsBrowserLockdownModeEnabled
#include <ios/web/public/web_client.h>  // IWYU pragma: export
#undef IsBrowserLockdownModeEnabled

#endif  // QORAI_CHROMIUM_SRC_IOS_WEB_PUBLIC_WEB_CLIENT_H_
