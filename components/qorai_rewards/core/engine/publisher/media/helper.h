/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_PUBLISHER_MEDIA_HELPER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_PUBLISHER_MEDIA_HELPER_H_

#include <string>

namespace qorai_rewards::internal {

std::string GetMediaKey(const std::string& mediaId, const std::string& type);

std::string ExtractData(const std::string& data,
                        const std::string& match_after,
                        const std::string& match_until);

}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_PUBLISHER_MEDIA_HELPER_H_
