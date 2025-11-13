/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/url/request_builder/host/url_host_util.h"

#include <memory>

#include "base/check.h"
#include "qorai/components/qorai_ads/core/internal/common/url/request_builder/host/url_host_factory.h"
#include "qorai/components/qorai_ads/core/internal/common/url/request_builder/host/url_host_types.h"

namespace qorai_ads {

namespace {

std::string GetUrlHost(UrlHostType type) {
  std::unique_ptr<UrlHostInterface> url_host = UrlHostFactory::Build(type);
  CHECK(url_host);

  return url_host->Get();
}

}  // namespace

std::string GetStaticUrlHost() {
  return GetUrlHost(UrlHostType::kStatic);
}

std::string GetGeoUrlHost() {
  return GetUrlHost(UrlHostType::kGeo);
}

std::string GetNonAnonymousUrlHost() {
  return GetUrlHost(UrlHostType::kNonAnonymous);
}

std::string GetAnonymousUrlHost() {
  return GetUrlHost(UrlHostType::kAnonymous);
}

std::string GetAnonymousSearchUrlHost() {
  return GetUrlHost(UrlHostType::kAnonymousSearch);
}

}  // namespace qorai_ads
