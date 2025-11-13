/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CLIENT_LEGACY_CLIENT_MIGRATION_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CLIENT_LEGACY_CLIENT_MIGRATION_H_

#include "qorai/components/qorai_ads/core/public/ads_callback.h"

namespace qorai_ads {

void MigrateClientState(InitializeCallback callback);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CLIENT_LEGACY_CLIENT_MIGRATION_H_
