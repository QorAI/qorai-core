/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_account/features.h"

namespace qorai_account::features {

BASE_FEATURE(kQoraiAccount, base::FEATURE_DISABLED_BY_DEFAULT);

bool IsQoraiAccountEnabled() {
  return base::FeatureList::IsEnabled(kQoraiAccount);
}

}  // namespace qorai_account::features
