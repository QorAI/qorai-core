/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/catalog_permission_rule_test_util.h"

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"

namespace qorai_ads::test {

void ForceCatalogPermissionRule() {
  SetCatalogId(kCatalogId);
  SetCatalogVersion(1);
  SetCatalogPing(base::Hours(2));
  SetCatalogLastUpdated(Now());
}

}  // namespace qorai_ads::test
