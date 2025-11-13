/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_funnel_keyphrase_info.h"

namespace qorai_ads {

PurchaseIntentFunnelKeyphraseInfo::PurchaseIntentFunnelKeyphraseInfo() =
    default;

PurchaseIntentFunnelKeyphraseInfo::PurchaseIntentFunnelKeyphraseInfo(
    PurchaseIntentFunnelKeyphraseInfo&& other) noexcept = default;

PurchaseIntentFunnelKeyphraseInfo& PurchaseIntentFunnelKeyphraseInfo::operator=(
    PurchaseIntentFunnelKeyphraseInfo&& other) noexcept = default;

PurchaseIntentFunnelKeyphraseInfo::~PurchaseIntentFunnelKeyphraseInfo() =
    default;

}  // namespace qorai_ads
