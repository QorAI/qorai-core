/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_REQUEST_H_
#define QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_REQUEST_H_

#include <string_view>

#include "qorai/components/qorai_account/endpoint_client/is_request_body.h"
#include "net/http/http_request_headers.h"
#include "net/traffic_annotation/network_traffic_annotation.h"

namespace qorai_account::endpoint_client::detail {

// HTTP methods
enum class Method {
  kConnect,
  kDelete,
  kGet,
  kHead,
  kOptions,
  kPatch,
  kPost,
  kPut,
  kTrace,
  kTrack
};

// Wrapper that binds an IsRequestBody to a specific HTTP method.
// Inherits from T to expose its ToValue() interface, and
// adds a static Method() accessor returning the canonical HTTP method string.
template <IsRequestBody T, Method M>
struct Request : T {
  static constexpr std::string_view Method() {
    if constexpr (M == Method::kConnect) {
      return net::HttpRequestHeaders::kConnectMethod;
    } else if constexpr (M == Method::kDelete) {
      return net::HttpRequestHeaders::kDeleteMethod;
    } else if constexpr (M == Method::kGet) {
      return net::HttpRequestHeaders::kGetMethod;
    } else if constexpr (M == Method::kHead) {
      return net::HttpRequestHeaders::kHeadMethod;
    } else if constexpr (M == Method::kOptions) {
      return net::HttpRequestHeaders::kOptionsMethod;
    } else if constexpr (M == Method::kPatch) {
      return net::HttpRequestHeaders::kPatchMethod;
    } else if constexpr (M == Method::kPost) {
      return net::HttpRequestHeaders::kPostMethod;
    } else if constexpr (M == Method::kPut) {
      return net::HttpRequestHeaders::kPutMethod;
    } else if constexpr (M == Method::kTrace) {
      return net::HttpRequestHeaders::kTraceMethod;
    } else if constexpr (M == Method::kTrack) {
      return net::HttpRequestHeaders::kTrackMethod;
    } else {
      static_assert(false, "Unhandled Method enumerator!");
    }
  }

  net::MutableNetworkTrafficAnnotationTag network_traffic_annotation_tag;
};

}  // namespace qorai_account::endpoint_client::detail

#endif  // QORAI_COMPONENTS_QORAI_ACCOUNT_ENDPOINT_CLIENT_REQUEST_H_
