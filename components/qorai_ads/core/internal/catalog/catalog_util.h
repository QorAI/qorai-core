/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CATALOG_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CATALOG_UTIL_H_

#include <string>

#include "qorai/components/qorai_ads/core/public/ads_callback.h"

namespace base {
class Time;
class TimeDelta;
}  // namespace base

namespace qorai_ads {

struct CatalogInfo;

void SaveCatalog(const CatalogInfo& catalog, ResultCallback callback);
void ResetCatalog(ResultCallback callback);

std::string GetCatalogId();
void SetCatalogId(const std::string& id);

int GetCatalogVersion();
void SetCatalogVersion(int version);

base::TimeDelta GetCatalogPing();
void SetCatalogPing(base::TimeDelta ping);

base::Time GetCatalogLastUpdated();
void SetCatalogLastUpdated(base::Time last_updated_at);

bool DoesCatalogExist();
bool HasCatalogChanged(const std::string& catalog_id);
bool HasCatalogExpired();

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CATALOG_UTIL_H_
