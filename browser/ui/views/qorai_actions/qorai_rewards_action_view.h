// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ACTIONS_QORAI_REWARDS_ACTION_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ACTIONS_QORAI_REWARDS_ACTION_VIEW_H_

#include <memory>
#include <string>
#include <utility>

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "qorai/browser/qorai_rewards/rewards_tab_helper.h"
#include "qorai/browser/ui/qorai_rewards/rewards_panel_coordinator.h"
#include "qorai/components/qorai_rewards/content/rewards_notification_service.h"
#include "qorai/components/qorai_rewards/content/rewards_notification_service_observer.h"
#include "qorai/components/qorai_rewards/content/rewards_service.h"
#include "qorai/components/qorai_rewards/content/rewards_service_observer.h"
#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"
#include "chrome/browser/ui/views/toolbar/toolbar_button.h"
#include "components/prefs/pref_change_registrar.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/gfx/geometry/skia_conversions.h"
#include "ui/views/widget/widget_observer.h"

class Profile;
class TabStripModel;
class WebUIBubbleManager;

// A button that lives in the actions container and opens the Rewards panel. The
// button has an associated context menu and can be hidden by user settings.
class QoraiRewardsActionView
    : public ToolbarButton,
      public views::WidgetObserver,
      public TabStripModelObserver,
      public qorai_rewards::RewardsTabHelper::Observer,
      public qorai_rewards::RewardsPanelCoordinator::Observer,
      public qorai_rewards::RewardsServiceObserver,
      public qorai_rewards::RewardsNotificationServiceObserver {
  METADATA_HEADER(QoraiRewardsActionView, ToolbarButton)
 public:
  explicit QoraiRewardsActionView(
      BrowserWindowInterface* browser_window_interface);

  ~QoraiRewardsActionView() override;

  QoraiRewardsActionView(const QoraiRewardsActionView&) = delete;
  QoraiRewardsActionView& operator=(const QoraiRewardsActionView&) = delete;

  void Update();

  void ClosePanelForTesting();

  // views::View:
  gfx::Rect GetAnchorBoundsInScreen() const override;

  // views::LabelButton:
  std::unique_ptr<views::LabelButtonBorder> CreateDefaultBorder()
      const override;
  void OnThemeChanged() override;

  // views::WidgetObserver:
  void OnWidgetDestroying(views::Widget* widget) override;

  // TabStripModelObserver:
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;

  // qorai_rewards::RewardsTabHelper::Observer:
  void OnPublisherForTabUpdated(const std::string& publisher_id) override;

  // qorai_rewards::RewardsPanelCoordinator::Observer:
  void OnRewardsPanelRequested() override;

  // qorai_rewards::RewardsServiceObserver:
  void OnPublisherRegistryUpdated() override;

  void OnPublisherUpdated(const std::string& publisher_id) override;

  // qorai_rewards::RewardsNotificationServiceObserver:
  void OnNotificationAdded(
      qorai_rewards::RewardsNotificationService* service,
      const qorai_rewards::RewardsNotificationService::RewardsNotification&
          notification) override;

  void OnNotificationDeleted(
      qorai_rewards::RewardsNotificationService* service,
      const qorai_rewards::RewardsNotificationService::RewardsNotification&
          notification) override;

 private:
  void OnButtonPressed();
  void OnPreferencesChanged(const std::string& key);
  content::WebContents* GetActiveWebContents();
  qorai_rewards::RewardsService* GetRewardsService();
  qorai_rewards::RewardsNotificationService* GetNotificationService();
  bool IsPanelOpen();
  void ToggleRewardsPanel();
  gfx::ImageSkia GetRewardsIcon();
  std::pair<std::string, SkColor> GetBadgeTextAndBackground();
  size_t GetRewardsNotificationCount();
  bool UpdatePublisherStatus();
  void IsPublisherRegisteredCallback(const std::string& publisher_id,
                                     bool is_registered);
  void UpdateTabHelper(content::WebContents* web_contents);

  using WidgetObservation =
      base::ScopedObservation<views::Widget, views::WidgetObserver>;

  using RewardsObservation =
      base::ScopedObservation<qorai_rewards::RewardsService,
                              qorai_rewards::RewardsServiceObserver>;

  using NotificationServiceObservation = base::ScopedObservation<
      qorai_rewards::RewardsNotificationService,
      qorai_rewards::RewardsNotificationServiceObserver>;

  raw_ptr<BrowserWindowInterface> browser_window_interface_ = nullptr;
  raw_ptr<qorai_rewards::RewardsPanelCoordinator> panel_coordinator_ = nullptr;
  raw_ptr<qorai_rewards::RewardsTabHelper> tab_helper_ = nullptr;
  std::unique_ptr<WebUIBubbleManager> bubble_manager_;
  PrefChangeRegistrar pref_change_registrar_;
  std::pair<std::string, bool> publisher_registered_;
  qorai_rewards::RewardsTabHelper::Observation tab_helper_observation_{this};
  qorai_rewards::RewardsPanelCoordinator::Observation panel_observation_{this};
  WidgetObservation bubble_observation_{this};
  RewardsObservation rewards_service_observation_{this};
  NotificationServiceObservation notification_service_observation_{this};
  base::WeakPtrFactory<QoraiRewardsActionView> weak_factory_{this};
};

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ACTIONS_QORAI_REWARDS_ACTION_VIEW_H_
