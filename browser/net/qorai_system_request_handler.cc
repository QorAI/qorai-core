/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/net/qorai_system_request_handler.h"

#include "qorai/browser/net/qorai_block_safebrowsing_urls.h"
#include "qorai/browser/net/qorai_common_static_redirect_network_delegate_helper.h"
#include "qorai/browser/net/qorai_speech_to_text_network_delegate_helper.h"
#include "qorai/browser/net/qorai_static_redirect_network_delegate_helper.h"
#include "qorai/components/constants/qorai_services_key.h"
#include "qorai/components/constants/qorai_services_key_helper.h"
#include "qorai/components/constants/network_constants.h"
#include "extensions/common/url_pattern.h"
#include "services/network/public/cpp/resource_request.h"
#include "url/gurl.h"

namespace qorai {

std::string QoraiServicesKeyForTesting() {
  return BUILDFLAG(QORAI_SERVICES_KEY);
}

void AddQoraiServicesKeyHeader(network::ResourceRequest* url_request) {
  if (qorai::ShouldAddQoraiServicesKeyHeader(url_request->url)) {
    url_request->headers.SetHeaderIfMissing(kQoraiServicesKeyHeader,
                                            BUILDFLAG(QORAI_SERVICES_KEY));
  }
  return;
}

network::ResourceRequest OnBeforeSystemRequest(
    const network::ResourceRequest& url_request) {
  GURL new_url;
  qorai::OnBeforeURLRequest_BlockSafeBrowsingReportingURLs(url_request.url,
                                                           &new_url);
  qorai::OnBeforeURLRequest_StaticRedirectWorkForGURL(url_request.url,
                                                      &new_url);
  qorai::OnBeforeURLRequest_CommonStaticRedirectWorkForGURL(url_request.url,
                                                            &new_url);
  network::ResourceRequest patched_request = url_request;
  if (!new_url.is_empty()) {
    patched_request.url = new_url;
  }
  stt::OnBeforeURLRequest_SpoofSpeechToText(&patched_request);
  AddQoraiServicesKeyHeader(&patched_request);
  return patched_request;
}

}  // namespace qorai
