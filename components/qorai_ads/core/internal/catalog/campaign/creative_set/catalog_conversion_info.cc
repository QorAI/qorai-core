/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/catalog/campaign/creative_set/catalog_conversion_info.h"

namespace qorai_ads {

CatalogConversionInfo::CatalogConversionInfo() = default;

CatalogConversionInfo::CatalogConversionInfo(
    const CatalogConversionInfo& other) = default;

CatalogConversionInfo& CatalogConversionInfo::operator=(
    const CatalogConversionInfo& other) = default;

CatalogConversionInfo::CatalogConversionInfo(
    CatalogConversionInfo&& other) noexcept = default;

CatalogConversionInfo& CatalogConversionInfo::operator=(
    CatalogConversionInfo&& other) noexcept = default;

CatalogConversionInfo::~CatalogConversionInfo() = default;

}  // namespace qorai_ads
