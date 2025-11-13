/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_sync/features.h"

#include "base/feature_list.h"

namespace qorai_sync::features {

BASE_FEATURE(kQoraiSync, base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE(kQoraiSyncDefaultPasswords,
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace qorai_sync::features
