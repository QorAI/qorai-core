/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_BUILDER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_BUILDER_H_

#include "qorai/components/qorai_ads/core/internal/common/url/request_builder/url_request_builder_interface.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

class IssuersUrlRequestBuilder final : public UrlRequestBuilderInterface {
 public:
  mojom::UrlRequestInfoPtr Build() override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_BUILDER_H_
