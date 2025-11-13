/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/url/request_builder/host/hosts/anonymous_url_host.h"

#include "qorai/components/qorai_ads/core/internal/global_state/global_state.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

namespace qorai_ads {

namespace {

constexpr char kProductionHost[] = "https://anonymous.ads.qorai.com";
constexpr char kStagingHost[] = "https://anonymous.ads.qoraisoftware.com";

}  // namespace

std::string AnonymousUrlHost::Get() const {
  const mojom::EnvironmentType mojom_environment_type =
      GlobalState::GetInstance()->Flags().environment_type;

  switch (mojom_environment_type) {
    case mojom::EnvironmentType::kProduction: {
      return kProductionHost;
    }

    case mojom::EnvironmentType::kStaging: {
      return kStagingHost;
    }
  }
}

}  // namespace qorai_ads
