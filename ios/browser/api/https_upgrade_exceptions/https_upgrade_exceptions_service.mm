// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/api/https_upgrade_exceptions/https_upgrade_exceptions_service+private.h"

#include "base/containers/contains.h"
#include "base/feature_list.h"
#include "base/memory/raw_ptr.h"
#include "qorai/components/https_upgrade_exceptions/browser/https_upgrade_exceptions_service.h"
#include "qorai/ios/browser/application_context/qorai_application_context_impl.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "net/base/apple/url_conversions.h"
#include "net/base/features.h"
#include "url/gurl.h"
#include "url/origin.h"

@interface HTTPSUpgradeExceptionsService () {
}

@property(nonatomic) bool isHttpsByDefaultFeatureEnabled;
@end

@implementation HTTPSUpgradeExceptionsService
- (instancetype)init {
  if ((self = [super init])) {
  }
  return self;
}

- (bool)isHttpsByDefaultFeatureEnabled {
  return base::FeatureList::IsEnabled(net::features::kQoraiHttpsByDefault);
}

- (bool)canUpgradeToHTTPSForURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  if (![self isHttpsByDefaultFeatureEnabled]) {
    return false;
  }

  // Check url validity
  if (!gurl.SchemeIs("http") || !gurl.is_valid()) {
    return false;
  }

  QoraiApplicationContextImpl* qoraiContext =
      static_cast<QoraiApplicationContextImpl*>(GetApplicationContext());
  return qoraiContext->https_upgrade_exceptions_service()->CanUpgradeToHTTPS(
      gurl);
}
@end
