/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_AD_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_AD_INFO_H_

#include <string>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "url/gurl.h"

namespace qorai_ads {

struct AdInfo {
  AdInfo();

  AdInfo(const AdInfo&);
  AdInfo& operator=(const AdInfo&);

  AdInfo(AdInfo&&) noexcept;
  AdInfo& operator=(AdInfo&&) noexcept;

  ~AdInfo();

  bool operator==(const AdInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  mojom::AdType type = mojom::AdType::kUndefined;
  std::string placement_id;
  std::string creative_instance_id;
  std::string creative_set_id;
  std::string campaign_id;
  std::string advertiser_id;
  std::string segment;
  GURL target_url;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_AD_INFO_H_
