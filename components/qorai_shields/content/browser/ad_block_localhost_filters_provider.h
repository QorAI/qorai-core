// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_LOCALHOST_FILTERS_PROVIDER_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_LOCALHOST_FILTERS_PROVIDER_H_

#include <string>

#include "base/functional/callback.h"
#include "base/memory/raw_ptr.h"
#include "base/sequence_checker.h"
#include "qorai/components/qorai_component_updater/browser/dat_file_util.h"
#include "qorai/components/qorai_shields/core/browser/ad_block_filters_provider.h"
#include "qorai/components/qorai_shields/core/browser/adblock/rs/src/lib.rs.h"
#include "third_party/rust/cxx/v1/cxx.h"

using qorai_component_updater::DATFileDataBuffer;

namespace qorai_shields {

class AdBlockLocalhostFiltersProvider : public AdBlockFiltersProvider {
 public:
  AdBlockLocalhostFiltersProvider();
  ~AdBlockLocalhostFiltersProvider() override;
  AdBlockLocalhostFiltersProvider(const AdBlockLocalhostFiltersProvider&) =
      delete;
  AdBlockLocalhostFiltersProvider& operator=(
      const AdBlockLocalhostFiltersProvider&) = delete;

  std::string GetLocalhostFilters();
  bool UpdateLocalhostFilters(const std::string& localhost_filters);

  // AdBlockFiltersProvider
  void LoadFilterSet(
      base::OnceCallback<void(
          base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)>) override;

  std::string GetNameForDebugging() override;

 private:
  SEQUENCE_CHECKER(sequence_checker_);
};

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_LOCALHOST_FILTERS_PROVIDER_H_
