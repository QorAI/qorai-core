/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_WITH_HEADERS_H_
#define QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_WITH_HEADERS_H_

#include "qorai/components/qorai_account/endpoint_client/is_request.h"
#include "net/http/http_request_headers.h"

namespace qorai_account::endpoint_client {

// Wrapper that extends an IsRequest type T
// with an additional net::HttpRequestHeaders member.
template <detail::IsRequest T>
struct WithHeaders : T {
  net::HttpRequestHeaders headers;
};

}  // namespace qorai_account::endpoint_client

#endif  // QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_WITH_HEADERS_H_
