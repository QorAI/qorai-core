// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_AD_BLOCK_LIST_P3A_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_AD_BLOCK_LIST_P3A_H_

#include <string>
#include <vector>

#include "base/containers/flat_set.h"
#include "base/memory/raw_ptr.h"

class PrefService;

namespace qorai_shields {

class FilterListCatalogEntry;

inline constexpr char kFilterListUsageHistogramName[] =
    "Qorai.Shields.FilterLists";

class AdBlockListP3A {
 public:
  explicit AdBlockListP3A(PrefService* local_state);
  ~AdBlockListP3A();

  AdBlockListP3A(const AdBlockListP3A&) = delete;
  AdBlockListP3A& operator=(const AdBlockListP3A&) = delete;

  void ReportFilterListUsage();

  void OnFilterListCatalogLoaded(
      const std::vector<FilterListCatalogEntry>& entries);

 private:
  raw_ptr<PrefService> local_state_;
  base::flat_set<std::string> default_filter_list_uuids_;
};

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_AD_BLOCK_LIST_P3A_H_
