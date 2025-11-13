/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

namespace qorai_ads {

bool NotificationAdInfo::IsValid() const {
  return AdInfo::IsValid() && !title.empty() && !body.empty();
}

}  // namespace qorai_ads
