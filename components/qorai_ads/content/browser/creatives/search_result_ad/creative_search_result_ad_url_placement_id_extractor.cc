/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_url_placement_id_extractor.h"

#include <optional>

#include "qorai/components/qorai_search/common/qorai_search_utils.h"
#include "net/base/url_util.h"
#include "url/gurl.h"

namespace qorai_ads {

namespace {

constexpr char kAllowedUrlPath[] = "/a/redirect";
constexpr char kPlacementIdQueryKey[] = "placement_id";

}  // namespace

std::optional<std::string> MaybeExtractCreativeAdPlacementIdFromUrl(
    const GURL& url) {
  if (!url.is_valid() || !url.SchemeIs(url::kHttpsScheme) ||
      url.path_piece() != kAllowedUrlPath || !url.has_query() ||
      !qorai_search::IsAllowedHost(url)) {
    return std::nullopt;
  }

  for (net::QueryIterator iter(url); !iter.IsAtEnd(); iter.Advance()) {
    if (iter.GetKey() == kPlacementIdQueryKey) {
      std::string placement_id{iter.GetValue()};
      if (placement_id.empty()) {
        return std::nullopt;
      }

      return placement_id;
    }
  }

  return std::nullopt;
}

}  // namespace qorai_ads
