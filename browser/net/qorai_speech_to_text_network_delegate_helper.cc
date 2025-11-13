/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/net/qorai_speech_to_text_network_delegate_helper.h"

#include <string>

#include "base/check.h"
#include "base/i18n/time_formatting.h"
#include "base/no_destructor.h"
#include "qorai/components/qorai_service_keys/qorai_service_key_utils.h"
#include "qorai/components/speech_to_text/buildflags.h"
#include "qorai/components/speech_to_text/features.h"
#include "extensions/common/url_pattern.h"
#include "net/base/url_util.h"
#include "services/network/public/cpp/resource_request.h"

namespace {

void AddSpeechToTextQoraiHeaders(network::ResourceRequest* request) {
  DCHECK(request && !request->method.empty() && request->url.is_valid() &&
         request->url.has_query());

  std::string request_key;
  net::GetValueForKeyInQuery(request->url, "pair", &request_key);

  request->credentials_mode = network::mojom::CredentialsMode::kInclude;
  request->site_for_cookies = net::SiteForCookies::FromUrl(request->url);

  static constexpr char kRequestKey[] = "request-key";
  request->headers.SetHeader(kRequestKey, request_key);
  static constexpr char kRequestDate[] = "request-date";
  const auto request_date = base::TimeFormatHTTP(base::Time::Now());
  request->headers.SetHeader(kRequestDate, request_date);

  const base::flat_map<std::string, std::string> headers{
      {kRequestKey, request_key}, {kRequestDate, request_date}};
  const auto authorization = qorai_service_keys::GetAuthorizationHeader(
      BUILDFLAG(SERVICE_KEY_STT), headers, request->url, request->method,
      {kRequestKey, kRequestDate});
  request->headers.SetHeader(authorization.first, authorization.second);
}

}  // namespace

namespace stt {

void OnBeforeURLRequest_SpoofSpeechToText(network::ResourceRequest* request) {
  if (!base::FeatureList::IsEnabled(stt::kSttFeature)) {
    return;
  }
  static constexpr char kSttPrefix[] =
      "https://www.google.com/speech-api/full-duplex/v1/*";
  static base::NoDestructor<URLPattern> stt_pattern(URLPattern::SCHEME_HTTPS,
                                                    kSttPrefix);
  if (!stt_pattern->MatchesURL(request->url)) {
    return;
  }
  const GURL stt_url = GURL(stt::kSttUrl.Get());
  GURL::Replacements replacements;
  replacements.SetSchemeStr(stt_url.scheme_piece());
  replacements.SetHostStr(stt_url.host_piece());
  if (stt_url.has_port()) {
    replacements.SetPortStr(stt_url.port_piece());
  }
  if (request->url.path_piece() == "/speech-api/full-duplex/v1/down") {
    replacements.SetPathStr("down");
  } else if (request->url.path_piece() == "/speech-api/full-duplex/v1/up") {
    replacements.SetPathStr("up");
  }
  request->url = request->url.ReplaceComponents(replacements);
  AddSpeechToTextQoraiHeaders(request);
}

}  // namespace stt
