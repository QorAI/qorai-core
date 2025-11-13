// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_QORAI_SEARCH_DEFAULT_HOST_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_QORAI_SEARCH_DEFAULT_HOST_H_

#include <string>

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_search/common/qorai_search_default.mojom.h"

class TemplateURLService;
class TemplateURL;
class PrefService;
class PrefRegistrySimple;

namespace qorai_search {

class QoraiSearchDefaultHost final
    : public qorai_search::mojom::QoraiSearchDefault {
 public:
  static void RegisterProfilePrefs(PrefRegistrySimple* registry);

  QoraiSearchDefaultHost(const QoraiSearchDefaultHost&) = delete;
  QoraiSearchDefaultHost& operator=(const QoraiSearchDefaultHost&) = delete;

  QoraiSearchDefaultHost(const std::string& host,
                         TemplateURLService* template_url_service,
                         PrefService* prefs);
  ~QoraiSearchDefaultHost() override;

  // qorai_search::mojom::QoraiSearchDefault:
  void SetCanAlwaysSetDefault() override;
  void GetCanSetDefaultSearchProvider(
      GetCanSetDefaultSearchProviderCallback callback) override;
  void SetIsDefaultSearchProvider() override;

 private:
  bool CanSetDefaultSearchProvider(TemplateURL* provider, bool is_historic);
  uint64_t GetMaxDailyCanAskCount();
  uint64_t GetMaxTotalCanAskCount();

  bool can_always_set_default_ = false;
  bool can_set_default_ = false;
  const std::string host_;
  raw_ptr<TemplateURLService> template_url_service_ = nullptr;
  raw_ptr<PrefService> prefs_ = nullptr;
};

}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_QORAI_SEARCH_DEFAULT_HOST_H_
