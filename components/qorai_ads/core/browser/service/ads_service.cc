/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/browser/service/ads_service.h"

#include <utility>

#include "base/check.h"

namespace qorai_ads {

AdsService::AdsService(std::unique_ptr<Delegate> delegate)
    : delegate_(std::move(delegate)) {}

AdsService::~AdsService() = default;

void AdsService::AddObserver(AdsServiceObserver* const observer) {
  CHECK(observer);

  observers_.AddObserver(observer);
}

void AdsService::RemoveObserver(AdsServiceObserver* const observer) {
  CHECK(observer);

  observers_.RemoveObserver(observer);
}

}  // namespace qorai_ads
