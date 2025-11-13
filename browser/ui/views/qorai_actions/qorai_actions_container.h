/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ACTIONS_QORAI_ACTIONS_CONTAINER_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ACTIONS_QORAI_ACTIONS_CONTAINER_H_

#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "chrome/browser/ui/browser.h"
#include "components/prefs/pref_member.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/gfx/skia_util.h"
#include "ui/views/view.h"

class QoraiActionViewController;
class QoraiActionsContainerTest;
class QoraiRewardsActionView;
class QoraiShieldsActionView;
class RewardsBrowserTest;

namespace policy {
FORWARD_DECLARE_TEST(QoraiRewardsPolicyTest, RewardsIconIsHidden);
}

namespace views {
class Button;
}

// This View contains all the built-in QoraiActions such as Shields and Payments
// TODO(petemill): consider splitting to separate model, like
// ToolbarActionsModel and ToolbarActionsBar
class QoraiActionsContainer : public views::View {
  METADATA_HEADER(QoraiActionsContainer, views::View)

 public:
  QoraiActionsContainer(BrowserWindowInterface* browser_window_interface,
                        Profile* profile);
  QoraiActionsContainer(const QoraiActionsContainer&) = delete;

  QoraiActionsContainer& operator=(const QoraiActionsContainer&) = delete;

  ~QoraiActionsContainer() override;

  void Init();
  void Update();
  void SetShouldHide(bool should_hide);

  // views::View:
  void ChildPreferredSizeChanged(views::View* child) override;

  QoraiShieldsActionView* GetShieldsActionView() { return shields_action_btn_; }

 private:
  FRIEND_TEST_ALL_PREFIXES(policy::QoraiRewardsPolicyTest, RewardsIconIsHidden);
  friend class ::QoraiActionsContainerTest;
  friend class ::RewardsBrowserTest;

  bool ShouldShowQoraiRewardsAction() const;
  void AddActionViewForRewards();
  void AddActionViewForShields();

  void UpdateVisibility();
  gfx::Size GetActionSize() const;

  // Qorai Rewards preferences change observers callback.
  void OnQoraiRewardsPreferencesChanged();

  bool should_hide_ = false;

  // The Browser this LocationBarView is in.  Note that at least
  // chromeos::SimpleWebViewDialog uses a LocationBarView outside any browser
  // window, so this may be NULL.
  raw_ptr<BrowserWindowInterface> browser_window_interface_ = nullptr;

  raw_ptr<QoraiShieldsActionView> shields_action_btn_ = nullptr;
  raw_ptr<QoraiRewardsActionView> rewards_action_btn_ = nullptr;

  // Listen for Qorai Rewards preferences changes.
  BooleanPrefMember show_qorai_rewards_button_;

  base::WeakPtrFactory<QoraiActionsContainer> weak_ptr_factory_{this};
};

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ACTIONS_QORAI_ACTIONS_CONTAINER_H_
