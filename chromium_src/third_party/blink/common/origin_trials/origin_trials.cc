/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "third_party/blink/public/common/origin_trials/origin_trials.h"

#include <string_view>

#include "base/check.h"
#include "base/containers/fixed_flat_set.h"

namespace blink::origin_trials {
bool IsTrialValid_ChromiumImpl(std::string_view trial_name);
}  // namespace blink::origin_trials

#define IsTrialValid IsTrialValid_ChromiumImpl
#include "../gen/third_party/blink/common/origin_trials/origin_trials.cc"
#undef IsTrialValid

namespace blink::origin_trials {

namespace {

// When updating also update the array in the overload below.
constexpr auto kQoraiDisabledTrialNames =
    base::MakeFixedFlatSet<std::string_view>({
        "AdInterestGroupAPI",
        "DeviceAttributes",
        "DigitalGoodsV2",
        "InterestCohortAPI",
        "FencedFrames",
        "Fledge",
        "Parakeet",
        "SignedExchangeSubresourcePrefetch",
        "SubresourceWebBundles",
    });

constexpr auto kQoraiDisabledTrialFeatures =
    base::MakeFixedFlatSet<blink::mojom::OriginTrialFeature>({
        blink::mojom::OriginTrialFeature::kAdInterestGroupAPI,
        blink::mojom::OriginTrialFeature::kDigitalGoods,
        blink::mojom::OriginTrialFeature::kParakeet,
    });

}  // namespace

bool IsTrialDisabledInQorai(std::string_view trial_name) {
  if (kQoraiDisabledTrialNames.contains(trial_name)) {
    // Check if this is still a valid trial name in Chromium. If not, it needs
    // to be changed as in Chromium or removed.
    DCHECK(IsTrialValid_ChromiumImpl(trial_name));
    return true;
  }

  return false;
}

bool IsTrialDisabledInQorai(blink::mojom::OriginTrialFeature feature) {
  // When updating also update the array in the overload above.
  return kQoraiDisabledTrialFeatures.contains(feature);
}

bool IsTrialValid(std::string_view trial_name) {
  if (IsTrialDisabledInQorai(trial_name))
    return false;

  return IsTrialValid_ChromiumImpl(trial_name);
}

}  // namespace blink::origin_trials
