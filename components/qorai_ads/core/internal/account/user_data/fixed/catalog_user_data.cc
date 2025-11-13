/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/catalog_user_data.h"

#include "qorai/components/qorai_ads/core/internal/catalog/catalog_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings.h"

namespace qorai_ads {

namespace {

constexpr char kCatalogKey[] = "catalog";
constexpr char kIdKey[] = "id";

}  // namespace

base::Value::Dict BuildCatalogUserData() {
  if (!UserHasJoinedQoraiRewards()) {
    return {};
  }

  return base::Value::Dict().Set(
      kCatalogKey, base::Value::List().Append(
                       base::Value::Dict().Set(kIdKey, GetCatalogId())));
}

}  // namespace qorai_ads
