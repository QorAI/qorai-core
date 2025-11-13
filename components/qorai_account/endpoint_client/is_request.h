/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_IS_REQUEST_H_
#define QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_IS_REQUEST_H_

#include "qorai/components/qorai_account/endpoint_client/is_request_body.h"
#include "qorai/components/qorai_account/endpoint_client/request.h"

namespace qorai_account::endpoint_client::detail {

// Primary template: a type does not satisfy IsRequest unless
// matched by the partial specialization below.
template <typename>
inline constexpr bool kIsRequest = false;

// Partial specialization: Request<T, M> satisfies IsRequest if
// T satisfies IsRequestBody.
template <IsRequestBody T, Method M>
inline constexpr bool kIsRequest<Request<T, M>> = true;

// Concept: a type satisfies IsRequest if
// its kIsRequest specialization evaluates to true.
template <typename T>
concept IsRequest = kIsRequest<T>;

}  // namespace qorai_account::endpoint_client::detail

#endif  // QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_IS_REQUEST_H_
