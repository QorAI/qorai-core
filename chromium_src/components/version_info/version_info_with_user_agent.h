/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_VERSION_INFO_VERSION_INFO_WITH_USER_AGENT_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_VERSION_INFO_VERSION_INFO_WITH_USER_AGENT_H_

#include <string>

#include "qorai/components/version_info/version_info_values.h"

#define GetProductNameAndVersionForUserAgent \
  GetProductNameAndVersionForUserAgent_Unused

#include <components/version_info/version_info_with_user_agent.h>  // IWYU pragma: export
#undef GetProductNameAndVersionForUserAgent

namespace version_info {

constexpr std::string GetProductNameAndVersionForUserAgent() {
  return "Chrome/" + std::string(constants::kQoraiChromiumVersion);
}

}  // namespace version_info

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_VERSION_INFO_VERSION_INFO_WITH_USER_AGENT_H_
