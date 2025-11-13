/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_USER_AGENT_BROWSER_QORAI_USER_AGENT_EXCEPTIONS_H_
#define QORAI_COMPONENTS_QORAI_USER_AGENT_BROWSER_QORAI_USER_AGENT_EXCEPTIONS_H_

#include <set>
#include <string>
#include <string_view>

#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "url/gurl.h"

namespace component_updater {
class ComponentUpdateService;
}  // namespace component_updater

namespace qorai_user_agent {

class QoraiUserAgentExceptions {
 public:
  QoraiUserAgentExceptions(const QoraiUserAgentExceptions&) = delete;
  QoraiUserAgentExceptions& operator=(const QoraiUserAgentExceptions&) = delete;
  ~QoraiUserAgentExceptions();
  static QoraiUserAgentExceptions* GetInstance();  // singleton

  void OnComponentReady(const base::FilePath&);
  bool CanShowQorai(const GURL& url);
  void SetIsReadyForTesting() { is_ready_ = true; }
  void AddToExceptedDomainsForTesting(std::string_view domain);

 private:
  FRIEND_TEST_ALL_PREFIXES(QoraiUserAgentExceptionsUnitTest,
                           TestCanShowQoraiDomainsLoaded);
  QoraiUserAgentExceptions();
  void OnExceptedDomainsLoaded(const std::string& contents);

  base::FilePath component_path_;
  std::set<std::string> excepted_domains_;
  bool is_ready_ = false;
  raw_ptr<component_updater::ComponentUpdateService> component_update_service_;
  base::WeakPtrFactory<QoraiUserAgentExceptions> weak_factory_{this};

  friend struct base::DefaultSingletonTraits<QoraiUserAgentExceptions>;
  friend class QoraiUserAgentExceptionsUnitTest;
};

}  // namespace qorai_user_agent

#endif  // QORAI_COMPONENTS_QORAI_USER_AGENT_BROWSER_QORAI_USER_AGENT_EXCEPTIONS_H_
