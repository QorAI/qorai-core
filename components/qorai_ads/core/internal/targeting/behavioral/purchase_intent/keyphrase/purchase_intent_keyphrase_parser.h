/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_KEYPHRASE_PURCHASE_INTENT_KEYPHRASE_PARSER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_KEYPHRASE_PURCHASE_INTENT_KEYPHRASE_PARSER_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/keyphrase/purchase_intent_keyphrase_alias.h"

namespace qorai_ads {

KeywordList ParseKeyphrase(const std::string& keyphrase);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_KEYPHRASE_PURCHASE_INTENT_KEYPHRASE_PARSER_H_
