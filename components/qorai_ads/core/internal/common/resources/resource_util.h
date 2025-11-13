/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_RESOURCES_RESOURCE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_RESOURCES_RESOURCE_UTIL_H_

#include <optional>
#include <string>

#include "base/functional/callback.h"

namespace qorai_ads {

template <typename T>
using LoadAndParseResourceComponentCallback =
    base::OnceCallback<void(std::optional<T>)>;

template <typename T>
void LoadAndParseResourceComponent(
    const std::string& id,
    int version,
    LoadAndParseResourceComponentCallback<T> callback);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_RESOURCES_RESOURCE_UTIL_H_
