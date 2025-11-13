// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_QORAI_SCHEME_UTILS_H_
#define QORAI_BROWSER_UI_QORAI_SCHEME_UTILS_H_

#include <string>

namespace qorai_utils {
// Replaces the chrome:// scheme with qorai:// scheme in the given |url_string|.
bool ReplaceChromeToQoraiScheme(std::u16string& url_string);
}  // namespace qorai_utils

#endif  // QORAI_BROWSER_UI_QORAI_SCHEME_UTILS_H_
