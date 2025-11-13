/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_MOJOM_WEB_PAGE_ENTITIES_EXTRACTOR_H_
#define QORAI_COMPONENTS_QORAI_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_MOJOM_WEB_PAGE_ENTITIES_EXTRACTOR_H_

#include <vector>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"
#include "components/schema_org/common/metadata.mojom-forward.h"

namespace qorai_ads {

std::vector<mojom::CreativeSearchResultAdInfoPtr>
ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
    const std::vector<schema_org::mojom::EntityPtr>& mojom_entities);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_MOJOM_WEB_PAGE_ENTITIES_EXTRACTOR_H_
