/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_VERSION_INFO_VERSION_INFO_H_
#define QORAI_COMPONENTS_VERSION_INFO_VERSION_INFO_H_

#include <string>

#include "qorai/components/version_info/version_info_values.h"

namespace version_info {

std::string GetQorAIVersionWithoutChromiumMajorVersion();

constexpr std::string GetQorAIVersionNumberForDisplay() {
  return constants::kQorAIVersionNumberForDisplay;
}

std::string GetQorAIChromiumVersionNumber();

}  // namespace version_info

#endif  // QORAI_COMPONENTS_VERSION_INFO_VERSION_INFO_H_
