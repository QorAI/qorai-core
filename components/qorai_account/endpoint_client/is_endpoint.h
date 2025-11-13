/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_IS_ENDPOINT_H_
#define QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_IS_ENDPOINT_H_

#include <concepts>
#include <string_view>

#include "qorai/components/qorai_account/endpoint_client/is_request.h"
#include "qorai/components/qorai_account/endpoint_client/is_response_body.h"
#include "url/gurl.h"

namespace qorai_account::endpoint_client {

namespace detail {

// Concept that checks whether `T` defines a static, accessible member
// function `URL()` such that:
//   - `T::URL()` is a valid expression,
//      and that call yields `GURL`
//
// In short: models any type with a proper static `URL()` function
// whose result is a `GURL`.
template <typename T>
concept URL = requires {
  { T::URL() } -> std::same_as<GURL>;
};

}  // namespace detail

template <typename T>
concept IsEndpoint =
    requires {
      typename T::Request;
      typename T::Response;
      typename T::Error;
    } && detail::IsRequest<typename T::Request> &&
    detail::IsResponseBody<typename T::Response> &&
    detail::IsResponseBody<typename T::Error> && detail::URL<T>;

}  // namespace qorai_account::endpoint_client

#endif  // QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_IS_ENDPOINT_H_
