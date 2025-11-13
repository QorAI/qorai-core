/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINTS_PASSWORD_FINALIZE_H_
#define QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINTS_PASSWORD_FINALIZE_H_

#include "qorai/components/qorai_account/endpoint_client/is_endpoint.h"
#include "qorai/components/qorai_account/endpoint_client/request_types.h"
#include "qorai/components/qorai_account/endpoints/error.h"
#include "qorai/components/qorai_account/endpoints/host.h"
#include "qorai/components/qorai_account/endpoints/password_finalize_request.h"
#include "qorai/components/qorai_account/endpoints/password_finalize_response.h"
#include "url/gurl.h"

namespace qorai_account::endpoints {

struct PasswordFinalize {
  using Request = endpoint_client::POST<PasswordFinalizeRequest>;
  using Response = PasswordFinalizeResponse;
  using Error = Error;

  static GURL URL() { return Host().Resolve("/v2/accounts/password/finalize"); }
};

static_assert(endpoint_client::IsEndpoint<PasswordFinalize>);

}  // namespace qorai_account::endpoints

#endif  // QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINTS_PASSWORD_FINALIZE_H_
