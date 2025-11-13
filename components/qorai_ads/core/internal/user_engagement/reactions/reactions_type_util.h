/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_TYPE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_TYPE_UTIL_H_

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

mojom::ReactionType ToggleLikedReactionType(
    mojom::ReactionType mojom_reaction_type);

mojom::ReactionType ToggleDislikedReactionType(
    mojom::ReactionType mojom_reaction_type);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_TYPE_UTIL_H_
