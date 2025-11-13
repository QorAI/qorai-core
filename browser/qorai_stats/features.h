/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_STATS_FEATURES_H_
#define QORAI_BROWSER_QORAI_STATS_FEATURES_H_

#include "base/feature_list.h"

namespace qorai_stats {
namespace features {

// See https://github.com/qorai/qorai-browser/issues/42111 for more info.
BASE_DECLARE_FEATURE(kHeadlessRefcode);

bool IsHeadlessClientRefcodeEnabled();

}  // namespace features
}  // namespace qorai_stats

#endif  // QORAI_BROWSER_QORAI_STATS_FEATURES_H_
