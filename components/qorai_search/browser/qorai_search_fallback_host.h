/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_QORAI_SEARCH_FALLBACK_HOST_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_QORAI_SEARCH_FALLBACK_HOST_H_

#include <memory>
#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_search/browser/backup_results_service.h"
#include "qorai/components/qorai_search/common/qorai_search_fallback.mojom.h"
#include "url/gurl.h"

namespace qorai_search {

class QoraiSearchFallbackHost final
    : public qorai_search::mojom::QoraiSearchFallback {
 public:
  QoraiSearchFallbackHost(const QoraiSearchFallbackHost&) = delete;
  QoraiSearchFallbackHost& operator=(const QoraiSearchFallbackHost&) = delete;
  explicit QoraiSearchFallbackHost(
      qorai_search::BackupResultsService* backup_results_service);
  ~QoraiSearchFallbackHost() override;

  void FetchBackupResults(const std::string& query_string,
                          const std::string& lang,
                          const std::string& country,
                          const std::string& geo,
                          bool filter_explicit_results,
                          int page_index,
                          const std::optional<std::string>& cookie_header_value,
                          FetchBackupResultsCallback callback) override;

  static GURL GetBackupResultURL(const GURL& baseURL,
                                 const std::string& query,
                                 const std::string& lang,
                                 const std::string& country,
                                 const std::string& geo,
                                 bool filter_explicit_results,
                                 int page_index);
  static void SetBackupProviderForTest(const GURL&);

 private:
  void OnResultsAvailable(
      QoraiSearchFallbackHost::FetchBackupResultsCallback callback,
      const std::optional<BackupResultsService::BackupResults> backup_results);
  base::WeakPtr<BackupResultsService> backup_results_service_;
  base::WeakPtrFactory<QoraiSearchFallbackHost> weak_factory_;
};

}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_QORAI_SEARCH_FALLBACK_HOST_H_
