// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_exceptions.h"

#include "base/containers/contains.h"
#include "base/feature_list.h"
#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_user_agent/common/features.h"
#include "qorai/ios/browser/api/qorai_user_agent/qorai_user_agent_exceptions_ios+private.h"
#include "qorai/ios/browser/application_context/qorai_application_context_impl.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "net/base/apple/url_conversions.h"
#include "net/base/features.h"
#include "url/gurl.h"
#include "url/origin.h"

@interface QoraiUserAgentExceptionsIOS () {
  raw_ptr<qorai_user_agent::QoraiUserAgentExceptions>
      _qoraiUserAgentExceptions;  // NOT OWNED
}

@end

@implementation QoraiUserAgentExceptionsIOS
- (instancetype)initWithQoraiUserAgentExceptions:
    (qorai_user_agent::QoraiUserAgentExceptions*)qoraiUserAgentExceptions {
  if ((self = [super init])) {
    _qoraiUserAgentExceptions = qoraiUserAgentExceptions;
  }
  return self;
}

- (bool)canShowQorai:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  if (!base::FeatureList::IsEnabled(
          qorai_user_agent::features::kUseQoraiUserAgent) ||
      !gurl.is_valid()) {
    return true;
  }

  return _qoraiUserAgentExceptions->CanShowQorai(gurl);
}
@end
