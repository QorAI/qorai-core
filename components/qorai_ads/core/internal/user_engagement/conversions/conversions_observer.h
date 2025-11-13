/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"

namespace qorai_ads {

struct ConversionInfo;

class ConversionsObserver : public base::CheckedObserver {
 public:
  // Invoked when an ad has converted.
  virtual void OnDidConvertAd(const ConversionInfo& conversion) {}

  // Invoked when an ad fails to convert.
  virtual void OnFailedToConvertAd(const std::string& creative_instance_id) {}
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_OBSERVER_H_
