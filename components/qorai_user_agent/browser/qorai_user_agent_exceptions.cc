/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_exceptions.h"

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "base/containers/contains.h"
#include "base/feature_list.h"
#include "base/files/file_path.h"
#include "base/strings/string_split.h"
#include "base/task/thread_pool.h"
#include "qorai/components/qorai_component_updater/browser/dat_file_util.h"
#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_component_installer.h"
#include "qorai/components/qorai_user_agent/common/features.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"

constexpr char kQoraiUserAgentExceptionsFile[] = "qorai-checks.txt";

namespace qorai_user_agent {

// static
QoraiUserAgentExceptions* QoraiUserAgentExceptions::GetInstance() {
  // Check if feature flag is enabled.
  if (!base::FeatureList::IsEnabled(
          qorai_user_agent::features::kUseQoraiUserAgent)) {
    return nullptr;
  }
  return base::Singleton<QoraiUserAgentExceptions>::get();
}

QoraiUserAgentExceptions::QoraiUserAgentExceptions() = default;

QoraiUserAgentExceptions::~QoraiUserAgentExceptions() {
  excepted_domains_.clear();
}

void QoraiUserAgentExceptions::OnExceptedDomainsLoaded(
    const std::string& contents) {
  if (contents.empty()) {
    // We don't have the file yet.
    return;
  }
  std::vector<std::string> lines = base::SplitString(
      contents, "\n", base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);
  excepted_domains_.insert(lines.begin(), lines.end());
  is_ready_ = true;
  return;
}

void QoraiUserAgentExceptions::OnComponentReady(const base::FilePath& path) {
  component_path_ = path;

  base::ThreadPool::PostTaskAndReplyWithResult(
      FROM_HERE, {base::MayBlock()},
      base::BindOnce(
          &qorai_component_updater::GetDATFileAsString,
          component_path_.AppendASCII(kQoraiUserAgentExceptionsFile)),
      base::BindOnce(&QoraiUserAgentExceptions::OnExceptedDomainsLoaded,
                     weak_factory_.GetWeakPtr()));
}

bool QoraiUserAgentExceptions::CanShowQorai(const GURL& url) {
  if (!is_ready_) {
    // We don't have the exceptions list loaded yet. To avoid breakage,
    // show Qorai for any website.
    return true;
  }

  std::string domain = net::registry_controlled_domains::GetDomainAndRegistry(
      url, net::registry_controlled_domains::INCLUDE_PRIVATE_REGISTRIES);

  // Show Qorai only if the domain is not on the exceptions list.
  return !base::Contains(excepted_domains_, domain);
}

void QoraiUserAgentExceptions::AddToExceptedDomainsForTesting(
    std::string_view domain) {
  excepted_domains_.insert(std::string(domain));
}

}  // namespace qorai_user_agent
