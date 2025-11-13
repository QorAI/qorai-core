// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_AD_BLOCK_SERVICE_HELPER_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_AD_BLOCK_SERVICE_HELPER_H_

#include <optional>
#include <string>

namespace qorai_shields {

void MergeCspDirectiveInto(std::optional<std::string> from,
                           std::optional<std::string>* into);

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_AD_BLOCK_SERVICE_HELPER_H_
