/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_search/browser/qorai_search_fallback_host.h"

#include <utility>

#include "base/strings/string_number_conversions.h"
#include "qorai/components/qorai_search/browser/backup_results_service.h"
#include "net/base/url_util.h"

namespace {
// TODO(https://github.com/qorai/qorai-browser/issues/48713): This is a case of
// `-Wexit-time-destructors` violation and `[[clang::no_destroy]]` has been
// added in the meantime to fix the build error. Remove this attribute and
// provide a proper fix.
[[clang::no_destroy]] static GURL backup_provider_for_test;
}  // namespace

namespace qorai_search {

void QoraiSearchFallbackHost::SetBackupProviderForTest(
    const GURL& backup_provider) {
  backup_provider_for_test = backup_provider;
}

QoraiSearchFallbackHost::QoraiSearchFallbackHost(
    qorai_search::BackupResultsService* backup_results_service)
    : backup_results_service_(backup_results_service->GetWeakPtr()),
      weak_factory_(this) {}

QoraiSearchFallbackHost::~QoraiSearchFallbackHost() = default;

// [static]
GURL QoraiSearchFallbackHost::GetBackupResultURL(const GURL& baseURL,
                                                 const std::string& query,
                                                 const std::string& lang,
                                                 const std::string& country,
                                                 const std::string& geo,
                                                 bool filter_explicit_results,
                                                 int page_index) {
  GURL url = baseURL;
  url = net::AppendQueryParameter(url, "q", query);
  url =
      net::AppendQueryParameter(url, "start", base::NumberToString(page_index));
  if (!lang.empty()) {
    url = net::AppendQueryParameter(url, "hl", lang);
  }
  if (!country.empty()) {
    url = net::AppendQueryParameter(url, "gl", country);
  }
  if (filter_explicit_results) {
    url = net::AppendQueryParameter(url, "safe", "active");
  }
  return url;
}

void QoraiSearchFallbackHost::FetchBackupResults(
    const std::string& query,
    const std::string& lang,
    const std::string& country,
    const std::string& geo,
    bool filter_explicit_results,
    int page_index,
    const std::optional<std::string>& cookie_header_value,
    FetchBackupResultsCallback callback) {
  auto url = GURL("https://www.google.com/search");
  if (!backup_provider_for_test.is_empty()) {
    url = backup_provider_for_test;
  }
  url = GetBackupResultURL(url, query, lang, country, geo,
                           filter_explicit_results, page_index);

  net::HttpRequestHeaders headers;

  headers.SetHeaderIfMissing("x-geo", geo);
  if (cookie_header_value) {
    headers.SetHeader(net::HttpRequestHeaders::kCookie, *cookie_header_value);
  }

  if (!backup_results_service_) {
    OnResultsAvailable(std::move(callback), std::nullopt);
    return;
  }

  backup_results_service_->FetchBackupResults(
      url, headers,
      base::BindOnce(&QoraiSearchFallbackHost::OnResultsAvailable,
                     weak_factory_.GetWeakPtr(), std::move(callback)));
}

void QoraiSearchFallbackHost::OnResultsAvailable(
    QoraiSearchFallbackHost::FetchBackupResultsCallback callback,
    const std::optional<BackupResultsService::BackupResults> backup_results) {
  if (backup_results) {
    std::move(callback).Run(backup_results->html);
    return;
  }
  std::move(callback).Run("");
}

}  // namespace qorai_search
