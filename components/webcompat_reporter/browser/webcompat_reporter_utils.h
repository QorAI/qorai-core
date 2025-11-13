// Copyright (c) 2024 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_WEBCOMPAT_REPORTER_BROWSER_WEBCOMPAT_REPORTER_UTILS_H_
#define QORAI_COMPONENTS_WEBCOMPAT_REPORTER_BROWSER_WEBCOMPAT_REPORTER_UTILS_H_

#include <string>

namespace webcompat_reporter {

bool SendComponentVersionInReport(std::string_view component_id);

std::string BoolToString(bool value);

}  // namespace webcompat_reporter

#endif  // QORAI_COMPONENTS_WEBCOMPAT_REPORTER_BROWSER_WEBCOMPAT_REPORTER_UTILS_H_
