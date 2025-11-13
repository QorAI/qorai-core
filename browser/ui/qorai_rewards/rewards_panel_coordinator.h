/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_REWARDS_REWARDS_PANEL_COORDINATOR_H_
#define QORAI_BROWSER_UI_QORAI_REWARDS_REWARDS_PANEL_COORDINATOR_H_

#include "base/observer_list.h"
#include "base/scoped_observation.h"
#include "url/gurl.h"

class BrowserWindowInterface;

namespace qorai_rewards {

// Provides a browser-scoped communication channel for components that need to
// display the Rewards panel and components responsible for showing the Rewards
// panel.
class RewardsPanelCoordinator {
 public:
  explicit RewardsPanelCoordinator(
      BrowserWindowInterface* browser_window_interface);

  RewardsPanelCoordinator(const RewardsPanelCoordinator&) = delete;
  RewardsPanelCoordinator& operator=(const RewardsPanelCoordinator&) = delete;

  ~RewardsPanelCoordinator();

  static bool IsRewardsPanelURLForTesting(const GURL& url);

  // Opens the Rewards panel with the default view.
  bool OpenRewardsPanel();

  class Observer : public base::CheckedObserver {
   public:
    // Called when an application component requests that the Rewards panel be
    // opened.
    virtual void OnRewardsPanelRequested() {}
  };

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);
  using Observation =
      base::ScopedObservation<RewardsPanelCoordinator, Observer>;

 private:
  raw_ptr<BrowserWindowInterface> browser_window_interface_ = nullptr;
  base::ObserverList<Observer> observers_;
};

}  // namespace qorai_rewards

#endif  // QORAI_BROWSER_UI_QORAI_REWARDS_REWARDS_PANEL_COORDINATOR_H_
