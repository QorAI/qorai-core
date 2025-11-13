/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_clicked.h"

#include <utility>

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_events.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"

namespace qorai_ads {

void NewTabPageAdEventClicked::FireEvent(const NewTabPageAdInfo& ad,
                                         ResultCallback callback) {
  RecordAdEvent(ad, mojom::ConfirmationType::kClicked, std::move(callback));
}

}  // namespace qorai_ads
