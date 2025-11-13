/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "ios/chrome/browser/net/model/ios_chrome_network_delegate.h"

#define IOSChromeNetworkDelegate IOSChromeNetworkDelegate_ChromiumImpl
#include <ios/chrome/browser/net/model/ios_chrome_network_delegate.cc>
#undef IOSChromeNetworkDelegate

#include "qorai/components/constants/qorai_services_key.h"
#include "qorai/components/constants/qorai_services_key_helper.h"
#include "qorai/components/constants/network_constants.h"
#include "qorai/components/static_redirect_helper/static_redirect_helper.h"

namespace {

void AddQoraiServicesKeyHeader(net::URLRequest* request) {
  if (qorai::ShouldAddQoraiServicesKeyHeader(request->url())) {
    request->SetExtraRequestHeaderByName(kQoraiServicesKeyHeader,
                                         BUILDFLAG(QORAI_SERVICES_KEY),
                                         true /* overrwrite */);
  }
}

}  // namespace

IOSChromeNetworkDelegate::~IOSChromeNetworkDelegate() = default;

int IOSChromeNetworkDelegate::OnBeforeURLRequest(
    net::URLRequest* request,
    net::CompletionOnceCallback callback,
    GURL* new_url) {
  ::AddQoraiServicesKeyHeader(request);
  qorai::StaticRedirectHelper(request->url(), new_url);
  return net::OK;
}
