/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_REWARDS_TEST_UTIL_REWARDS_BROWSERTEST_UTIL_H_
#define QORAI_BROWSER_QORAI_REWARDS_TEST_UTIL_REWARDS_BROWSERTEST_UTIL_H_

#include <optional>
#include <string>

#include "base/files/file_path.h"
#include "qorai/components/qorai_rewards/content/rewards_service_impl.h"
#include "net/test/embedded_test_server/embedded_test_server.h"
#include "url/gurl.h"

class Browser;
class Profile;

namespace qorai_rewards::test_util {

void GetTestDataDir(base::FilePath* test_data_dir);

GURL GetRewardsUrl();

GURL GetRewardsInternalsUrl();

GURL GetNewTabUrl();

void StartProcess(RewardsServiceImpl* rewards_service);

void StartProcessWithConnectedUser(Profile* profile);

GURL GetUrl(net::EmbeddedTestServer* https_server,
            const std::string& publisher_key,
            const std::string& path = "");

void ActivateTabAtIndex(Browser* browser, const int index);

std::string BalanceDoubleToString(double amount);

std::string GetUpholdExternalAddress();

std::string GetGeminiExternalAddress();

void NavigateToPublisherPage(Browser* browser,
                             net::EmbeddedTestServer* https_server,
                             const std::string& publisher_key,
                             const std::string& path = "");

void NavigateToPublisherAndWaitForUpdate(Browser* browser,
                                         net::EmbeddedTestServer* https_server,
                                         const std::string& publisher_key);

void WaitForEngineStop(RewardsServiceImpl* rewards_service);

void WaitForAutoContributeVisitTime();

void CreateRewardsWallet(RewardsServiceImpl* rewards_service,
                         const std::string& country = "US");

void SetOnboardingBypassed(Browser* browser, bool bypassed = true);

std::optional<std::string> EncryptPrefString(const std::string& value);

}  // namespace qorai_rewards::test_util

#endif  // QORAI_BROWSER_QORAI_REWARDS_TEST_UTIL_REWARDS_BROWSERTEST_UTIL_H_
