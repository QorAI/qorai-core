/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/confirmations/confirmation_info.h"

namespace qorai_ads {

ConfirmationInfo::ConfirmationInfo() = default;

ConfirmationInfo::ConfirmationInfo(const ConfirmationInfo& other) = default;

ConfirmationInfo& ConfirmationInfo::operator=(const ConfirmationInfo& other) =
    default;

ConfirmationInfo::ConfirmationInfo(ConfirmationInfo&& other) noexcept = default;

ConfirmationInfo& ConfirmationInfo::operator=(
    ConfirmationInfo&& other) noexcept = default;

ConfirmationInfo::~ConfirmationInfo() = default;

}  // namespace qorai_ads
