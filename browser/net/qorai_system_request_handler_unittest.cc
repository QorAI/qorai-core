/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/net/qorai_system_request_handler.h"

#include <string>

#include "qorai/components/constants/network_constants.h"
#include "services/network/public/cpp/resource_request.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai {

TEST(QoraiSystemRequestHandlerTest, AddQoraiServiceKeyHeaderForQorai) {
  GURL url("https://demo.qorai.com");
  network::ResourceRequest request;

  request.url = url;
  qorai::AddQoraiServicesKeyHeader(&request);
  auto key = request.headers.GetHeader(kQoraiServicesKeyHeader);
  ASSERT_TRUE(key);
  EXPECT_EQ(*key, QoraiServicesKeyForTesting());
}

TEST(QoraiSystemRequestHandlerTest, AddQoraiServiceKeyHeaderForQoraiSoftware) {
  GURL url("https://demo.qoraisoftware.com");
  network::ResourceRequest request;

  request.url = url;
  qorai::AddQoraiServicesKeyHeader(&request);
  auto key = request.headers.GetHeader(kQoraiServicesKeyHeader);
  ASSERT_TRUE(key);
  EXPECT_EQ(*key, QoraiServicesKeyForTesting());
}

TEST(QoraiSystemRequestHandlerTest, DontAddQoraiServiceKeyHeader) {
  GURL url("https://demo.example.com");
  network::ResourceRequest request;

  request.url = url;
  qorai::AddQoraiServicesKeyHeader(&request);
  auto key = request.headers.GetHeader(kQoraiServicesKeyHeader);
  ASSERT_FALSE(key);
}

}  // namespace qorai
