/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_REWARDS_EXTENSION_REWARDS_SERVICE_OBSERVER_H_
#define QORAI_BROWSER_QORAI_REWARDS_EXTENSION_REWARDS_SERVICE_OBSERVER_H_

#include <memory>
#include <string>
#include <vector>

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_rewards/content/rewards_service_observer.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

class Profile;

namespace qorai_rewards {

class RewardsService;

class ExtensionRewardsServiceObserver : public RewardsServiceObserver {
 public:
  explicit ExtensionRewardsServiceObserver(Profile* profile);

  ExtensionRewardsServiceObserver(const ExtensionRewardsServiceObserver&) =
      delete;

  ExtensionRewardsServiceObserver& operator=(
      const ExtensionRewardsServiceObserver&) = delete;

  ~ExtensionRewardsServiceObserver() override;

  // RewardsServiceObserver:
  void OnRewardsInitialized(RewardsService* rewards_service) override;

  void OnRewardsWalletCreated() override;

  void OnTermsOfServiceUpdateAccepted() override;

  void OnPublisherListNormalized(
      RewardsService* rewards_service,
      std::vector<qorai_rewards::mojom::PublisherInfoPtr> list) override;

  void OnExcludedSitesChanged(RewardsService* rewards_service,
                              std::string publisher_key,
                              bool excluded) override;

  void OnRecurringTipSaved(RewardsService* rewards_service,
                           bool success) override;

  void OnRecurringTipRemoved(RewardsService* rewards_service,
                             bool success) override;

  void OnReconcileComplete(
      RewardsService* rewards_service,
      const qorai_rewards::mojom::Result result,
      const std::string& contribution_id,
      const double amount,
      const qorai_rewards::mojom::RewardsType type,
      const qorai_rewards::mojom::ContributionProcessor processor) override;

  void OnExternalWalletConnected() override;

  void OnExternalWalletLoggedOut() override;

  void OnExternalWalletDisconnected() override;

  void OnCompleteReset(const bool success) override;

  void OnPanelPublisherInfo(RewardsService* rewards_service,
                            const qorai_rewards::mojom::Result result,
                            const qorai_rewards::mojom::PublisherInfo* info,
                            uint64_t windowId) override;

 private:
  raw_ptr<Profile> profile_ = nullptr;
};

}  // namespace qorai_rewards

#endif  // QORAI_BROWSER_QORAI_REWARDS_EXTENSION_REWARDS_SERVICE_OBSERVER_H_
