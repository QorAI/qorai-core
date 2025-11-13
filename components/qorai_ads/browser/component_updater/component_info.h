/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_INFO_H_

#include <string_view>

namespace qorai_ads {

struct ComponentInfo {
  std::string_view public_key_base64;
  std::string_view id;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_COMPONENT_INFO_H_
