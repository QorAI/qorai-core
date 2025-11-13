/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/location_bar/qorai_location_bar_view.h"

#include <optional>
#include <utility>

#include "base/check.h"
#include "base/containers/contains.h"
#include "base/feature_list.h"
#include "qorai/app/vector_icons/vector_icons.h"
#include "qorai/browser/themes/qorai_theme_service.h"
#include "qorai/browser/ui/color/qorai_color_id.h"
#include "qorai/browser/ui/tabs/qorai_tab_prefs.h"
#include "qorai/browser/ui/tabs/features.h"
#include "qorai/browser/ui/views/qorai_actions/qorai_actions_container.h"
#include "qorai/browser/ui/views/qorai_news/qorai_news_action_icon_view.h"
#include "qorai/browser/ui/views/location_bar/qorai_search_conversion/promotion_button_controller.h"
#include "qorai/browser/ui/views/location_bar/qorai_search_conversion/promotion_button_view.h"
#include "qorai/browser/ui/views/playlist/playlist_action_icon_view.h"
#include "qorai/browser/ui/views/toolbar/qorai_toolbar_view.h"
#include "qorai/components/commander/common/buildflags/buildflags.h"
#include "qorai/grit/qorai_theme_resources.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/themes/theme_service_factory.h"
#include "chrome/browser/ui/layout_constants.h"
#include "chrome/browser/ui/omnibox/omnibox_edit_model.h"
#include "chrome/browser/ui/omnibox/omnibox_theme.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"
#include "chrome/browser/ui/views/location_bar/location_bar_view.h"
#include "chrome/browser/ui/views/omnibox/omnibox_view_views.h"
#include "chrome/browser/ui/views/page_action/page_action_icon_controller.h"
#include "chrome/grit/branded_strings.h"
#include "components/grit/qorai_components_strings.h"
#include "components/version_info/channel.h"
#include "content/public/browser/navigation_entry.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/compositor/layer.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/geometry/skia_conversions.h"
#include "ui/gfx/image/image_skia.h"
#include "ui/gfx/paint_vector_icon.h"
#include "ui/views/animation/ink_drop.h"
#include "ui/views/controls/highlight_path_generator.h"
#include "ui/views/view_utils.h"

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/browser/ui/views/location_bar/onion_location_view.h"
#endif

#if BUILDFLAG(ENABLE_COMMANDER)
#include "qorai/browser/ui/commander/commander_service_factory.h"
#include "qorai/components/commander/browser/commander_frontend_delegate.h"
#include "qorai/components/commander/common/features.h"
#endif

namespace {

class QoraiLocationBarViewFocusRingHighlightPathGenerator
    : public views::HighlightPathGenerator {
 public:
  QoraiLocationBarViewFocusRingHighlightPathGenerator() = default;
  QoraiLocationBarViewFocusRingHighlightPathGenerator(
      const QoraiLocationBarViewFocusRingHighlightPathGenerator&) = delete;
  QoraiLocationBarViewFocusRingHighlightPathGenerator& operator=(
      const QoraiLocationBarViewFocusRingHighlightPathGenerator&) = delete;

  // HighlightPathGenerator
  SkPath GetHighlightPath(const views::View* view) override {
    return static_cast<const QoraiLocationBarView*>(view)
        ->GetFocusRingHighlightPath();
  }
};

std::optional<QoraiColorIds> GetFocusRingColor(Profile* profile) {
  if (profile->IsGuestSession()) {
    // Don't update color.
    return std::nullopt;
  }

  return kColorLocationBarFocusRing;
}

}  // namespace

QoraiLocationBarView::QoraiLocationBarView(Browser* browser,
                                           Profile* profile,
                                           CommandUpdater* command_updater,
                                           Delegate* delegate,
                                           bool is_popup_mode)
    : LocationBarView(browser,
                      profile,
                      command_updater,
                      delegate,
                      is_popup_mode) {}

QoraiLocationBarView::~QoraiLocationBarView() = default;

void QoraiLocationBarView::Init() {
  // base method calls Update and Layout
  LocationBarView::Init();
  // Change focus ring highlight path
  views::FocusRing* focus_ring = views::FocusRing::Get(this);
  if (focus_ring) {
    focus_ring->SetPathGenerator(
        std::make_unique<
            QoraiLocationBarViewFocusRingHighlightPathGenerator>());
    if (const auto color_id = GetFocusRingColor(profile())) {
      focus_ring->SetColorId(color_id.value());
    }
  }

  if (!browser_->profile()->IsOffTheRecord()) {
    qorai_news_action_icon_view_ =
        AddChildView(std::make_unique<QoraiNewsActionIconView>(
            browser_->profile(), this, this));
    qorai_news_action_icon_view_->SetVisible(false);
    views::InkDrop::Get(qorai_news_action_icon_view_)
        ->SetVisibleOpacity(GetPageActionInkDropVisibleOpacity());
  }
#if BUILDFLAG(ENABLE_TOR)
  onion_location_view_ = AddChildView(
      std::make_unique<OnionLocationView>(browser_->profile(), this, this));
#endif

  if (PromotionButtonController::PromotionEnabled(profile()->GetPrefs())) {
    promotion_button_ = AddChildView(std::make_unique<PromotionButtonView>());
    promotion_controller_ = std::make_unique<PromotionButtonController>(
        promotion_button_, omnibox_view_, browser());
  }

  // qorai action buttons
  qorai_actions_ = AddChildView(
      std::make_unique<QoraiActionsContainer>(browser_, profile()));
  qorai_actions_->Init();
  // Call Update again to cause a Layout
  Update(nullptr);

  // Stop slide animation for all content settings views icon.
  for (ContentSettingImageView* content_setting_view : content_setting_views_) {
    content_setting_view->disable_animation();
  }
}

void QoraiLocationBarView::ShowPlaylistBubble(
    playlist::PlaylistBubblesController::BubbleType type) {
  if (auto* playlist_action_icon_view = GetPlaylistActionIconView()) {
    playlist_action_icon_view->ShowPlaylistBubble(type);
  }
}

PlaylistActionIconView* QoraiLocationBarView::GetPlaylistActionIconView() {
  auto* playlist_action_icon_view =
      page_action_icon_controller()->GetPlaylistActionIconView();
  if (!playlist_action_icon_view) {
    return nullptr;
  }

  return views::AsViewClass<PlaylistActionIconView>(playlist_action_icon_view);
}

void QoraiLocationBarView::Update(content::WebContents* contents) {
  // base Init calls update before our Init is run, so our children
  // may not be initialized yet
  if (qorai_actions_) {
    qorai_actions_->Update();
  }

#if BUILDFLAG(ENABLE_TOR)
  if (onion_location_view_) {
    onion_location_view_->Update();
  }
#endif

  if (qorai_news_action_icon_view_) {
    qorai_news_action_icon_view_->Update();
  }

  LocationBarView::Update(contents);
}

void QoraiLocationBarView::OnOmniboxBlurred() {
#if BUILDFLAG(ENABLE_COMMANDER)
  if (base::FeatureList::IsEnabled(features::kQoraiCommander)) {
    if (auto* commander_service =
            commander::CommanderServiceFactory::GetForBrowserContext(
                profile_)) {
      commander_service->Hide();
    }
  }
#endif
  LocationBarView::OnOmniboxBlurred();
}

void QoraiLocationBarView::Layout(PassKey) {
  if (ignore_layout_) {
    return;
  }

  LayoutSuperclass<LocationBarView>(this);
}

void QoraiLocationBarView::OnVisibleBoundsChanged() {
  if (ignore_layout_) {
    return;
  }

  LocationBarView::OnVisibleBoundsChanged();
}

void QoraiLocationBarView::OnChanged() {
  auto hide_page_actions = ShouldHidePageActionIcons();
  if (qorai_actions_) {
    qorai_actions_->SetShouldHide(hide_page_actions);
  }
#if BUILDFLAG(ENABLE_TOR)
  if (onion_location_view_) {
    onion_location_view_->Update();
  }
#endif

  if (qorai_news_action_icon_view_) {
    qorai_news_action_icon_view_->Update();
  }

  if (promotion_controller_) {
    const bool show_button =
        promotion_controller_->ShouldShowSearchPromotionButton() &&
        !ShouldChipOverrideLocationIcon() && !ShouldShowKeywordBubble();
    promotion_controller_->Show(show_button);
  }

  // OnChanged calls Layout
  LocationBarView::OnChanged();
}

std::vector<views::View*> QoraiLocationBarView::GetRightMostTrailingViews() {
  std::vector<views::View*> views;
  if (qorai_news_action_icon_view_) {
    views.push_back(qorai_news_action_icon_view_);
  }

  if (qorai_actions_) {
    views.push_back(qorai_actions_);
  }

  return views;
}

std::vector<views::View*> QoraiLocationBarView::GetLeftMostTrailingViews() {
  std::vector<views::View*> views;
#if BUILDFLAG(ENABLE_TOR)
  if (onion_location_view_) {
    views.push_back(onion_location_view_);
  }
#endif
  return views;
}

views::View* QoraiLocationBarView::GetSearchPromotionButton() const {
  return promotion_button_;
}

void QoraiLocationBarView::RefreshBackground() {
  LocationBarView::RefreshBackground();

  if (shadow_) {
    const bool show_shadow =
        IsMouseHovered() && !omnibox_view_->model()->is_caret_visible();
    shadow_->SetVisible(show_shadow);
    return;
  }
}

gfx::Size QoraiLocationBarView::CalculatePreferredSize(
    const views::SizeBounds& available_size) const {
  gfx::Size min_size = LocationBarView::CalculatePreferredSize(available_size);
  if (qorai_actions_ && qorai_actions_->GetVisible()) {
    const int qorai_actions_min = qorai_actions_->GetMinimumSize().width();
    const int extra_width =
        qorai_actions_min + GetLayoutConstant(LOCATION_BAR_ELEMENT_PADDING);
    min_size.Enlarge(extra_width, 0);
  }
  if (qorai_news_action_icon_view_ &&
      qorai_news_action_icon_view_->GetVisible()) {
    const int extra_width =
        GetLayoutConstant(LOCATION_BAR_ELEMENT_PADDING) +
        qorai_news_action_icon_view_->GetMinimumSize().width();
    min_size.Enlarge(extra_width, 0);
  }
#if BUILDFLAG(ENABLE_TOR)
  if (onion_location_view_ && onion_location_view_->GetVisible()) {
    const int extra_width = GetLayoutConstant(LOCATION_BAR_ELEMENT_PADDING) +
                            onion_location_view_->GetMinimumSize().width();
    min_size.Enlarge(extra_width, 0);
  }
#endif

  return min_size;
}

void QoraiLocationBarView::OnThemeChanged() {
  LocationBarView::OnThemeChanged();

  if (!IsInitialized()) {
    return;
  }

  Update(nullptr);
  SetupShadow();
}

void QoraiLocationBarView::AddedToWidget() {
  SetupShadow();
}

void QoraiLocationBarView::ChildVisibilityChanged(views::View* child) {
  LocationBarView::ChildVisibilityChanged(child);
  // Normally, PageActionIcons are in a container which is always visible, only
  // the size changes when an icon is shown or hidden. The LocationBarView
  // does not listen to ChildVisibilityChanged events so we must make we Layout
  // and re-caculate trailing decorator positions when a child changes.
  if (base::Contains(GetLeftMostTrailingViews(), child) ||
      base::Contains(GetRightMostTrailingViews(), child)) {
    DeprecatedLayoutImmediately();
    SchedulePaint();
  }
}

void QoraiLocationBarView::SetupShadow() {
  const auto* const color_provider = GetColorProvider();
  if (!color_provider) {
    return;
  }

  const int radius = GetBorderRadius();
  ViewShadow::ShadowParameters shadow{
      .offset_x = 0,
      .offset_y = 1,
      .blur_radius = radius,
      .shadow_color = color_provider->GetColor(kColorLocationBarHoveredShadow)};

  shadow_ = std::make_unique<ViewShadow>(this, radius, shadow);
}

int QoraiLocationBarView::GetBorderRadius() const {
  return ChromeLayoutProvider::Get()->GetCornerRadiusMetric(
      views::Emphasis::kMaximum, size());
}

void QoraiLocationBarView::FocusLocation(bool is_user_initiated) {
  if (base::FeatureList::IsEnabled(tabs::features::kQoraiSharedPinnedTabs) &&
      browser_->profile()->GetPrefs()->GetBoolean(
          qorai_tabs::kSharedPinnedTab)) {
    // When updating dummy contents, this could be called even when the widget
    // is inactive. We shouldn't focus the omnibox in that case.
    if (auto* widget = GetWidget(); !widget || !widget->IsActive()) {
      return;
    }
  }

  omnibox_view_->SetFocus(is_user_initiated);
}

SkPath QoraiLocationBarView::GetFocusRingHighlightPath() const {
  const SkScalar radius = GetBorderRadius();
  return SkPath().addRoundRect(gfx::RectToSkRect(GetLocalBounds()), radius,
                               radius);
}

ContentSettingImageView*
QoraiLocationBarView::GetContentSettingsImageViewForTesting(size_t idx) {
  DCHECK(idx < content_setting_views_.size());
  return content_setting_views_[idx];
}

BEGIN_METADATA(QoraiLocationBarView)
END_METADATA
