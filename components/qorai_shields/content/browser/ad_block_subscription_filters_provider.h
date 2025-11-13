// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_FILTERS_PROVIDER_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_FILTERS_PROVIDER_H_

#include <string>

#include "base/functional/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/trace_event/trace_event.h"
#include "qorai/components/qorai_component_updater/browser/dat_file_util.h"
#include "qorai/components/qorai_shields/core/browser/ad_block_filters_provider.h"
#include "qorai/components/qorai_shields/core/browser/adblock/rs/src/lib.rs.h"
#include "third_party/rust/cxx/v1/cxx.h"

using qorai_component_updater::DATFileDataBuffer;

class PrefService;

namespace adblock {
struct FilterListMetadata;
}  // namespace adblock

namespace qorai_shields {

class AdBlockSubscriptionFiltersProvider : public AdBlockFiltersProvider {
 public:
  AdBlockSubscriptionFiltersProvider(
      PrefService* local_state,
      base::FilePath list_file,
      base::RepeatingCallback<void(const adblock::FilterListMetadata&)>
          on_metadata_retrieved);
  AdBlockSubscriptionFiltersProvider(
      const AdBlockSubscriptionFiltersProvider&) = delete;
  AdBlockSubscriptionFiltersProvider& operator=(
      const AdBlockSubscriptionFiltersProvider&) = delete;
  ~AdBlockSubscriptionFiltersProvider() override;

  void LoadFilterSet(
      base::OnceCallback<void(
          base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)>) override;

  void OnListAvailable();

 private:
  void OnDATFileDataReady(
      base::OnceCallback<
          void(base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)> cb,
      const perfetto::Flow& flow,
      const DATFileDataBuffer& dat_buf);

  std::string GetNameForDebugging() override;

 private:
  base::FilePath list_file_;

  base::RepeatingCallback<void(const adblock::FilterListMetadata&)>
      on_metadata_retrieved_;

  base::WeakPtrFactory<AdBlockSubscriptionFiltersProvider> weak_factory_{this};
};

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_FILTERS_PROVIDER_H_
