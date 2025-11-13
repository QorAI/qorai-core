/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_signal_history_info.h"

namespace qorai_ads {

PurchaseIntentSignalHistoryInfo::PurchaseIntentSignalHistoryInfo(base::Time at,
                                                                 int weight)
    : at(at), weight(weight) {}

}  // namespace qorai_ads
