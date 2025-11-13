/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_MAYBE_STRIP_WITH_HEADERS_H_
#define QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_MAYBE_STRIP_WITH_HEADERS_H_

#include <type_traits>

#include "qorai/components/qorai_account/endpoint_client/is_request.h"
#include "qorai/components/qorai_account/endpoint_client/with_headers.h"

namespace qorai_account::endpoint_client::detail {

// Primary template: leaves types unchanged unless
// matched by the partial specialization below.
template <typename T>
struct MaybeStripWithHeadersImpl : std::type_identity<T> {};

// Partial specialization: strips WithHeaders<> if
// the inner T satisfies IsRequest.
template <IsRequest T>
struct MaybeStripWithHeadersImpl<WithHeaders<T>> : std::type_identity<T> {};

// Alias: a type with WithHeaders<> removed if
// its MaybeStripWithHeadersImpl specialization applies.
template <typename T>
using MaybeStripWithHeaders = typename MaybeStripWithHeadersImpl<T>::type;

}  // namespace qorai_account::endpoint_client::detail

#endif  // QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_MAYBE_STRIP_WITH_HEADERS_H_
