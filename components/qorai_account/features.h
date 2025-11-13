/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ACCOUNT_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_ACCOUNT_FEATURES_H_

#include "base/feature_list.h"

namespace qorai_account::features {

BASE_DECLARE_FEATURE(kQoraiAccount);

bool IsQoraiAccountEnabled();

}  // namespace qorai_account::features

#endif  // QORAI_COMPONENTS_QORAI_ACCOUNT_FEATURES_H_
