/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/catalog_permission_rule.h"

#include "qorai/components/qorai_ads/core/internal/catalog/catalog_util.h"
#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"

namespace qorai_ads {

bool HasCatalogPermission() {
  if (!DoesCatalogExist()) {
    BLOG(2, "Catalog does not exist");
    return false;
  }

  if (HasCatalogExpired()) {
    BLOG(2, "Catalog has expired");
    return false;
  }

  return true;
}

}  // namespace qorai_ads
