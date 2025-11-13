/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/qorai_actions/qorai_actions_container.h"

#include <memory>
#include <utility>

#include "base/feature_list.h"
#include "qorai/browser/qorai_rewards/rewards_util.h"
#include "qorai/browser/ui/views/qorai_actions/qorai_rewards_action_view.h"
#include "qorai/browser/ui/views/qorai_actions/qorai_shields_action_view.h"
#include "qorai/browser/ui/views/rounded_separator.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/constants/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/layout_constants.h"
#include "components/prefs/pref_service.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/views/layout/box_layout.h"
#include "ui/views/view.h"

QoraiActionsContainer::QoraiActionsContainer(
    BrowserWindowInterface* browser_window_interface,
    Profile* profile)
    : browser_window_interface_(browser_window_interface) {}

QoraiActionsContainer::~QoraiActionsContainer() = default;

void QoraiActionsContainer::Init() {
  // automatic layout
  auto vertical_container_layout = std::make_unique<views::BoxLayout>(
      views::BoxLayout::Orientation::kHorizontal);
  vertical_container_layout->set_main_axis_alignment(
      views::BoxLayout::MainAxisAlignment::kCenter);
  vertical_container_layout->set_cross_axis_alignment(
      views::BoxLayout::CrossAxisAlignment::kCenter);
  SetLayoutManager(std::move(vertical_container_layout));

  // children
  RoundedSeparator* qorai_button_separator_ = new RoundedSeparator();
  // TODO(petemill): theme color
  qorai_button_separator_->SetColor(SkColorSetRGB(0xb2, 0xb5, 0xb7));
  constexpr int kSeparatorMargin = 3;
  constexpr int kSeparatorWidth = 1;
  qorai_button_separator_->SetPreferredSize(
      gfx::Size(kSeparatorWidth + kSeparatorMargin * 2,
                GetLayoutConstant(LOCATION_BAR_ICON_SIZE)));
  // separator left & right margin
  qorai_button_separator_->SetBorder(views::CreateEmptyBorder(
      gfx::Insets::TLBR(0, kSeparatorMargin, 0, kSeparatorMargin)));
  // Just in case the extensions load before this function does (not likely!)
  // make sure separator is at index 0
  AddChildViewAt(qorai_button_separator_, 0);
  AddActionViewForShields();
  AddActionViewForRewards();

  // React to Qorai Rewards preferences changes.
  show_qorai_rewards_button_.Init(
      qorai_rewards::prefs::kShowLocationBarButton,
      browser_window_interface_->GetProfile()->GetPrefs(),
      base::BindRepeating(
          &QoraiActionsContainer::OnQoraiRewardsPreferencesChanged,
          base::Unretained(this)));
}

bool QoraiActionsContainer::ShouldShowQoraiRewardsAction() const {
  if (!qorai_rewards::IsSupportedForProfile(
          browser_window_interface_->GetProfile())) {
    return false;
  }
  const PrefService* prefs =
      browser_window_interface_->GetProfile()->GetPrefs();
  return prefs->GetBoolean(qorai_rewards::prefs::kShowLocationBarButton);
}

void QoraiActionsContainer::AddActionViewForShields() {
  shields_action_btn_ = AddChildViewAt(
      std::make_unique<QoraiShieldsActionView>(browser_window_interface_), 1);
  shields_action_btn_->SetPreferredSize(GetActionSize());
  shields_action_btn_->Init();
}

void QoraiActionsContainer::AddActionViewForRewards() {
  auto button =
      std::make_unique<QoraiRewardsActionView>(browser_window_interface_);
  rewards_action_btn_ = AddChildViewAt(std::move(button), 2);
  rewards_action_btn_->SetPreferredSize(GetActionSize());
  rewards_action_btn_->SetVisible(ShouldShowQoraiRewardsAction());
  rewards_action_btn_->Update();
}

void QoraiActionsContainer::Update() {
  if (shields_action_btn_) {
    shields_action_btn_->Update();
  }

  if (rewards_action_btn_) {
    rewards_action_btn_->Update();
  }

  UpdateVisibility();
  DeprecatedLayoutImmediately();
}

void QoraiActionsContainer::UpdateVisibility() {
  bool can_show = false;

  if (shields_action_btn_) {
    can_show = shields_action_btn_->GetVisible();
  }

  if (rewards_action_btn_) {
    can_show = can_show || rewards_action_btn_->GetVisible();
  }

  // If no buttons are visible, then we want to hide this view so that the
  // separator is not displayed.
  SetVisible(!should_hide_ && can_show);
}

gfx::Size QoraiActionsContainer::GetActionSize() const {
  return {34, GetLayoutConstant(LOCATION_BAR_HEIGHT) -
                  2 * GetLayoutConstant(LOCATION_BAR_ELEMENT_PADDING)};
}

void QoraiActionsContainer::SetShouldHide(bool should_hide) {
  should_hide_ = should_hide;
  Update();
}

void QoraiActionsContainer::ChildPreferredSizeChanged(views::View* child) {
  PreferredSizeChanged();
}

// Qorai Rewards preferences change observers callback
void QoraiActionsContainer::OnQoraiRewardsPreferencesChanged() {
  if (rewards_action_btn_) {
    rewards_action_btn_->SetVisible(ShouldShowQoraiRewardsAction());
  }
}

BEGIN_METADATA(QoraiActionsContainer)
END_METADATA
