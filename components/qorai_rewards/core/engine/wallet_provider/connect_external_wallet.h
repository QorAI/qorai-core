/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_CONNECT_EXTERNAL_WALLET_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_CONNECT_EXTERNAL_WALLET_H_

#include <string>

#include "base/containers/flat_map.h"
#include "base/memory/raw_ref.h"
#include "base/types/expected.h"
#include "qorai/components/qorai_rewards/core/engine/endpoints/common/post_connect.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace wallet_provider {

class ConnectExternalWallet {
 public:
  explicit ConnectExternalWallet(RewardsEngine& engine);

  virtual ~ConnectExternalWallet();

  std::string GenerateLoginURL();

  void Run(const base::flat_map<std::string, std::string>& query_parameters,
           ConnectExternalWalletCallback);

  struct OAuthInfo {
    std::string one_time_string;
    std::string code_verifier;
    std::string code;
  };

  void SetOAuthStateForTesting(const OAuthInfo& oauth_info) {
    oauth_info_ = oauth_info;
  }

  const OAuthInfo& GetOAuthStateForTesting() const { return oauth_info_; }

 protected:
  virtual const char* WalletType() const = 0;

  virtual std::string GetOAuthLoginURL() const = 0;

  virtual void Authorize(ConnectExternalWalletCallback) = 0;

  void OnConnect(ConnectExternalWalletCallback,
                 std::string&& token,
                 std::string&& address,
                 endpoints::PostConnect::Result&&) const;

  const raw_ref<RewardsEngine> engine_;
  OAuthInfo oauth_info_;

 private:
  base::expected<std::string, mojom::ConnectExternalWalletResult> GetCode(
      const base::flat_map<std::string, std::string>& query_parameters,
      const std::string& current_one_time_string) const;
};

}  // namespace wallet_provider
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_CONNECT_EXTERNAL_WALLET_H_
