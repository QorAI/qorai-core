/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/net/qorai_user_agent_network_delegate_helper.h"

#include <memory>
#include <string>

#include "base/strings/string_util.h"
#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_exceptions.h"
#include "net/base/net_errors.h"
#include "net/http/http_request_headers.h"

namespace qorai {

namespace {

constexpr char kHeaderSecCHUA[] = "Sec-CH-UA";
constexpr char kHeaderSecCHUAFullVersionList[] = "Sec-CH-UA-Full-Version-List";
constexpr char kQoraiBrand[] = "\"Qorai\"";
constexpr char kGoogleChromeBrand[] = "\"Google Chrome\"";

void ReplaceQoraiWithGoogleChromeInHeader(net::HttpRequestHeaders* headers,
                                          const char* header_name) {
  std::optional<std::string> header_value = headers->GetHeader(header_name);
  if (header_value) {
    std::string value = header_value.value();
    base::ReplaceFirstSubstringAfterOffset(&value, /*start_offset=*/0,
                                           kQoraiBrand, kGoogleChromeBrand);
    headers->SetHeader(header_name, value);
  }
}

}  // namespace

int OnBeforeStartTransaction_UserAgentWork(
    net::HttpRequestHeaders* headers,
    const ResponseCallback& next_callback,
    std::shared_ptr<QoraiRequestInfo> ctx) {
  if (ctx) {
    auto* exceptions =
        qorai_user_agent::QoraiUserAgentExceptions::GetInstance();
    if (exceptions) {
      bool show_qorai = exceptions->CanShowQorai(ctx->tab_origin);
      if (!show_qorai) {
        ReplaceQoraiWithGoogleChromeInHeader(headers, kHeaderSecCHUA);
        ReplaceQoraiWithGoogleChromeInHeader(headers,
                                             kHeaderSecCHUAFullVersionList);
      }
    }
  }
  return net::OK;
}

}  // namespace qorai
