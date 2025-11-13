/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINTS_SERVICE_TOKEN_H_
#define QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINTS_SERVICE_TOKEN_H_

#include "qorai/components/qorai_account/endpoint_client/is_endpoint.h"
#include "qorai/components/qorai_account/endpoint_client/request_types.h"
#include "qorai/components/qorai_account/endpoints/error.h"
#include "qorai/components/qorai_account/endpoints/host.h"
#include "qorai/components/qorai_account/endpoints/service_token_request.h"
#include "qorai/components/qorai_account/endpoints/service_token_response.h"
#include "url/gurl.h"

namespace qorai_account::endpoints {

struct ServiceToken {
  using Request = endpoint_client::POST<ServiceTokenRequest>;
  using Response = ServiceTokenResponse;
  using Error = Error;

  static GURL URL() { return Host().Resolve("/v2/auth/service_token"); }
};

static_assert(endpoint_client::IsEndpoint<ServiceToken>);

}  // namespace qorai_account::endpoints

#endif  // QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINTS_SERVICE_TOKEN_H_
