// Copyright (c) 2024 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_VARIATIONS_SWITCHES_H_
#define QORAI_COMPONENTS_VARIATIONS_SWITCHES_H_

namespace variations::switches {

// If this flag is set to a qorai/qorai-variations pull request number, the
// browser will point "--variations-server-url" to a test seed URL from this
// pull request.
inline constexpr char kVariationsPR[] = "variations-pr";

}  // namespace variations::switches

#endif  // QORAI_COMPONENTS_VARIATIONS_SWITCHES_H_
