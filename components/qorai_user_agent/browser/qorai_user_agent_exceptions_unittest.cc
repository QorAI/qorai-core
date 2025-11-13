/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_exceptions.h"

#include "base/files/file_util.h"
#include "base/files/scoped_temp_dir.h"
#include "base/task/current_thread.h"
#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_user_agent/common/features.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai_user_agent {

class QoraiUserAgentExceptionsUnitTest : public testing::Test {
 public:
  QoraiUserAgentExceptionsUnitTest() {}

 protected:
  base::test::TaskEnvironment task_environment_{
      base::test::TaskEnvironment::TimeSource::MOCK_TIME};
};

TEST_F(QoraiUserAgentExceptionsUnitTest, TestCanShowQoraiDomainsNotLoaded) {
  // QoraiUserAgentExceptions returns nullptr when feature is disabled.
  base::test::ScopedFeatureList features;
  features.InitAndEnableFeature(qorai_user_agent::features::kUseQoraiUserAgent);

  auto* qorai_user_agent_exceptions = QoraiUserAgentExceptions::GetInstance();
  // Excepted domains not loaded; default to true.
  GURL url = GURL("https://qorai.com");
  ASSERT_TRUE(qorai_user_agent_exceptions->CanShowQorai(url));
}

TEST_F(QoraiUserAgentExceptionsUnitTest, TestCanShowQoraiDomainsLoaded) {
  // QoraiUserAgentExceptions returns nullptr when feature is disabled.
  base::test::ScopedFeatureList features;
  features.InitAndEnableFeature(qorai_user_agent::features::kUseQoraiUserAgent);

  auto* qorai_user_agent_exceptions = QoraiUserAgentExceptions::GetInstance();

  // Load excepted domains to hide qorai
  const char* excepted_domains = R""""(
    qorai.com
    site.example
    )"""";
  base::ScopedTempDir temp_dir_;
  ASSERT_TRUE(temp_dir_.CreateUniqueTempDir());
  base::FilePath excepted_domains_path =
      temp_dir_.GetPath().AppendASCII("qorai-checks.txt");
  ASSERT_TRUE(base::WriteFile(excepted_domains_path, excepted_domains));
  qorai_user_agent_exceptions->OnComponentReady(temp_dir_.GetPath());
  // run for callback to OnExceptedDomainsLoaded
  base::test::RunUntil(
      [&]() { return qorai_user_agent_exceptions->is_ready_; });

  // Test excepted domains (hide we are Qorai)
  ASSERT_FALSE(
      qorai_user_agent_exceptions->CanShowQorai(GURL("https://qorai.com")));
  ASSERT_FALSE(qorai_user_agent_exceptions->CanShowQorai(
      GURL("https://qorai.com/privacy")));
  ASSERT_FALSE(
      qorai_user_agent_exceptions->CanShowQorai(GURL("https://site.example")));
  // Test other domains (show we are Qorai)
  ASSERT_TRUE(qorai_user_agent_exceptions->CanShowQorai(
      GURL("https://adifferentsite.example")));
  ASSERT_TRUE(
      qorai_user_agent_exceptions->CanShowQorai(GURL("https://youtube.com")));
  ASSERT_TRUE(
      qorai_user_agent_exceptions->CanShowQorai(GURL("https://github.io")));
  ASSERT_TRUE(
      qorai_user_agent_exceptions->CanShowQorai(GURL("https://github.com")));
}

}  // namespace qorai_user_agent
