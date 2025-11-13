/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_user_model_info.h"

#include <utility>

namespace qorai_ads {

LatentInterestUserModelInfo::LatentInterestUserModelInfo() = default;

LatentInterestUserModelInfo::LatentInterestUserModelInfo(SegmentList segments)
    : segments(std::move(segments)) {}

LatentInterestUserModelInfo::LatentInterestUserModelInfo(
    const LatentInterestUserModelInfo& other) = default;

LatentInterestUserModelInfo& LatentInterestUserModelInfo::operator=(
    const LatentInterestUserModelInfo& other) = default;

LatentInterestUserModelInfo::LatentInterestUserModelInfo(
    LatentInterestUserModelInfo&& other) noexcept = default;

LatentInterestUserModelInfo& LatentInterestUserModelInfo::operator=(
    LatentInterestUserModelInfo&& other) noexcept = default;

LatentInterestUserModelInfo::~LatentInterestUserModelInfo() = default;

}  // namespace qorai_ads
