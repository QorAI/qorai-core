/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_LOCATION_BAR_QORAI_LOCATION_BAR_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_LOCATION_BAR_QORAI_LOCATION_BAR_VIEW_H_

#include <memory>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/types/pass_key.h"
#include "qorai/browser/ui/views/qorai_news/qorai_news_action_icon_view.h"
#include "qorai/browser/ui/views/playlist/playlist_bubbles_controller.h"
#include "qorai/browser/ui/views/toolbar/qorai_toolbar_view.h"
#include "qorai/browser/ui/views/view_shadow.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "chrome/browser/ui/views/location_bar/location_bar_view.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiActionsContainer;
class QoraiActionsContainerTest;
class PromotionButtonController;
class PromotionButtonView;
class PlaylistActionIconView;
class RewardsBrowserTest;
class SkPath;

#if BUILDFLAG(ENABLE_TOR)
class OnionLocationView;
#endif

namespace playlist {
FORWARD_DECLARE_TEST(PlaylistBrowserTest, AddItemsToList);
FORWARD_DECLARE_TEST(PlaylistBrowserTest, UIHiddenWhenDisabled);
FORWARD_DECLARE_TEST(PlaylistBrowserTestWithSitesUsingMediaSource,
                     MediaShouldBeExtractedFromBackground_SucceedInExtracting);
FORWARD_DECLARE_TEST(PlaylistBrowserTestWithSitesUsingMediaSource,
                     MediaShouldBeExtractedFromBackground_FailToExtract);
FORWARD_DECLARE_TEST(
    PlaylistBrowserTestWithSitesUsingMediaSource,
    MediaShouldBeExtractedFromBackground_DynamicallyAddedMedia);
}  // namespace playlist

namespace policy {
FORWARD_DECLARE_TEST(QoraiRewardsPolicyTest, RewardsIconIsHidden);
}

// The purposes of this subclass are to:
// - Add the QoraiActionsContainer to the location bar
class QoraiLocationBarView : public LocationBarView {
  METADATA_HEADER(QoraiLocationBarView, LocationBarView)
 public:
  QoraiLocationBarView(Browser* browser,
                       Profile* profile,
                       CommandUpdater* command_updater,
                       Delegate* delegate,
                       bool is_popup_mode);
  ~QoraiLocationBarView() override;

  QoraiLocationBarView(const QoraiLocationBarView&) = delete;
  QoraiLocationBarView& operator=(const QoraiLocationBarView&) = delete;

  void Init() override;
  void Update(content::WebContents* contents) override;
  void OnChanged() override;
  QoraiActionsContainer* GetQoraiActionsContainer() { return qorai_actions_; }
#if BUILDFLAG(ENABLE_TOR)
  OnionLocationView* GetOnionLocationView() { return onion_location_view_; }
#endif

  // LocationBarView:
  // Views that locates at right side of upstream's trailing views.
  std::vector<views::View*> GetRightMostTrailingViews() override;
  // Views that locates at left side of upstream's trailing views.
  std::vector<views::View*> GetLeftMostTrailingViews() override;
  views::View* GetSearchPromotionButton() const override;
  void RefreshBackground() override;
  void OnOmniboxBlurred() override;
  void Layout(PassKey) override;
  void OnVisibleBoundsChanged() override;

  // views::View:
  gfx::Size CalculatePreferredSize(
      const views::SizeBounds& available_size) const override;
  void OnThemeChanged() override;
  void ChildVisibilityChanged(views::View* child) override;
  void AddedToWidget() override;
  int GetBorderRadius() const override;
  void FocusLocation(bool is_user_initiated) override;

  SkPath GetFocusRingHighlightPath() const;
  ContentSettingImageView* GetContentSettingsImageViewForTesting(size_t idx);
  QoraiActionsContainer* qorai_actions_contatiner_view() {
    return qorai_actions_;
  }

  void ShowPlaylistBubble(
      playlist::PlaylistBubblesController::BubbleType type =
          playlist::PlaylistBubblesController::BubbleType::kInfer);

  void set_ignore_layout(base::PassKey<QoraiToolbarView::LayoutGuard>,
                         bool ignore) {
    ignore_layout_ = ignore;
  }

 private:
  FRIEND_TEST_ALL_PREFIXES(playlist::PlaylistBrowserTest, AddItemsToList);
  FRIEND_TEST_ALL_PREFIXES(playlist::PlaylistBrowserTest, UIHiddenWhenDisabled);
  FRIEND_TEST_ALL_PREFIXES(
      playlist::PlaylistBrowserTestWithSitesUsingMediaSource,
      MediaShouldBeExtractedFromBackground_SucceedInExtracting);
  FRIEND_TEST_ALL_PREFIXES(
      playlist::PlaylistBrowserTestWithSitesUsingMediaSource,
      MediaShouldBeExtractedFromBackground_FailToExtract);
  FRIEND_TEST_ALL_PREFIXES(
      playlist::PlaylistBrowserTestWithSitesUsingMediaSource,
      MediaShouldBeExtractedFromBackground_DynamicallyAddedMedia);
  FRIEND_TEST_ALL_PREFIXES(policy::QoraiRewardsPolicyTest, RewardsIconIsHidden);
  FRIEND_TEST_ALL_PREFIXES(QoraiLocationBarViewBrowserTest,
                           SearchConversionButtonTest);
  friend class ::QoraiActionsContainerTest;
  friend class ::RewardsBrowserTest;

  PlaylistActionIconView* GetPlaylistActionIconView();
  void SetupShadow();

  // Prevent layout with invalid rect.
  // It also could make omnibox popup have wrong position.
  // See the comments of QoraiToolbarView::Layout().
  bool ignore_layout_ = false;
  std::unique_ptr<ViewShadow> shadow_;
  raw_ptr<QoraiActionsContainer> qorai_actions_ = nullptr;
  raw_ptr<QoraiNewsActionIconView> qorai_news_action_icon_view_ = nullptr;
  std::unique_ptr<PromotionButtonController> promotion_controller_;
  raw_ptr<PromotionButtonView> promotion_button_ = nullptr;
#if BUILDFLAG(ENABLE_TOR)
  raw_ptr<OnionLocationView> onion_location_view_ = nullptr;
#endif
};

#endif  // QORAI_BROWSER_UI_VIEWS_LOCATION_BAR_QORAI_LOCATION_BAR_VIEW_H_
