/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_ANONYMOUS_SEARCH_URL_HOST_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_ANONYMOUS_SEARCH_URL_HOST_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/common/url/request_builder/host/hosts/url_host_interface.h"

namespace qorai_ads {

class AnonymousSearchUrlHost final : public UrlHostInterface {
 public:
  std::string Get() const override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_ANONYMOUS_SEARCH_URL_HOST_H_
