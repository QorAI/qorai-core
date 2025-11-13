/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_UTIL_H_

#include <optional>
#include <string_view>

#include "qorai/components/qorai_ads/browser/component_updater/component_info.h"

namespace qorai_ads {

std::optional<ComponentInfo> GetComponent(std::string_view id);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_UTIL_H_
