/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/conversion_user_data.h"

#include <optional>
#include <utility>

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/conversion_user_data_constants.h"
#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/conversion_user_data_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversion/conversion_info.h"

namespace qorai_ads {

base::Value::Dict BuildConversionUserData(const ConversionInfo& conversion) {
  base::Value::List list;

  // Conversion.
  list.Append(BuildConversionActionTypeUserData(conversion));

  // Verifiable conversion.
  if (std::optional<base::Value::Dict> verifiable_conversion_user_data =
          MaybeBuildVerifiableConversionUserData(conversion)) {
    list.Append(std::move(*verifiable_conversion_user_data));
  }

  return base::Value::Dict().Set(kConversionKey, std::move(list));
}

}  // namespace qorai_ads
