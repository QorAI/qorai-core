/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_INFO_H_

#include <optional>
#include <string>
#include <vector>

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "url/gurl.h"

namespace qorai_ads {

struct AdEventInfo final {
  AdEventInfo();

  AdEventInfo(const AdEventInfo&);
  AdEventInfo& operator=(const AdEventInfo&);

  AdEventInfo(AdEventInfo&&) noexcept;
  AdEventInfo& operator=(AdEventInfo&&) noexcept;

  ~AdEventInfo();

  bool operator==(const AdEventInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  mojom::AdType type = mojom::AdType::kUndefined;
  mojom::ConfirmationType confirmation_type =
      mojom::ConfirmationType::kUndefined;
  std::string placement_id;
  std::string creative_instance_id;
  std::string creative_set_id;
  std::string campaign_id;
  std::string advertiser_id;
  std::string segment;
  GURL target_url;
  std::optional<base::Time> created_at;
};

using AdEventList = std::vector<AdEventInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_INFO_H_
