/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_SEARCH_CONVERSION_PROMOTION_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_SEARCH_CONVERSION_PROMOTION_VIEW_H_

#include <memory>
#include <optional>
#include <string>

#include "base/memory/raw_ptr.h"
#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_search_conversion/types.h"
#include "chrome/browser/ui/views/omnibox/omnibox_mouse_enter_exit_handler.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/view.h"

class QoraiOmniboxResultView;
class PrefService;
class TemplateURLService;

namespace views {
class Background;
class Label;
}  // namespace views

class QoraiSearchConversionPromotionView : public views::View {
  METADATA_HEADER(QoraiSearchConversionPromotionView, views::View)
 public:
  QoraiSearchConversionPromotionView(QoraiOmniboxResultView* result_view,
                                     PrefService* local_state,
                                     PrefService* profile_prefs,
                                     TemplateURLService* template_url_service);
  QoraiSearchConversionPromotionView(
      const QoraiSearchConversionPromotionView&) = delete;
  QoraiSearchConversionPromotionView& operator=(
      const QoraiSearchConversionPromotionView&) = delete;
  ~QoraiSearchConversionPromotionView() override;

  void SetTypeAndInput(qorai_search_conversion::ConversionType type,
                       const std::u16string& input);
  void OnSelectionStateChanged(bool selected);

  // views::View overrides:
  gfx::Size CalculatePreferredSize(
      const views::SizeBounds& available_size) const override;
  void OnThemeChanged() override;

 private:
  void ConfigureForBannerType();
  void UpdateState();
  void UpdateHoverState();
  void OpenMatch();
  void SetQoraiAsDefault();
  void Dismiss();
  void MaybeLater();
  int GetBannerTypeTitleStringResourceId();
  int GetBannerTypeDescStringResourceId();
  SkColor GetCloseButtonColor() const;
  int GetOverallHorizontalMarginAroundDescription() const;
  std::unique_ptr<views::View> GetPrimaryButton();
  std::unique_ptr<views::View> GetSecondaryButton();
  void OnPrimaryButtonPressed();
  void OnSecondaryButtonPressed();
  std::optional<int> GetBackgroundGraphic() const;

  // true when this is for ddg conversion promotion.
  bool UseDDG() const;

  // false if we don't have sufficient space.
  // Only renders title & description in that situation.
  bool ShouldDrawGraphic() const;

  raw_ptr<QoraiOmniboxResultView> result_view_ = nullptr;

  // Children for button or banner type promotion.
  // Promotion view is implemented w/o using existing omnibox view controls
  // because our promotion view's layout, bg and text colors are slightly
  // different. |banner_type_container_| is for banner type.

  // Children for banner type promotion.
  raw_ptr<views::View> banner_type_container_ = nullptr;
  raw_ptr<views::Label> banner_type_description_ = nullptr;

  qorai_search_conversion::ConversionType type_ =
      qorai_search_conversion::ConversionType::kNone;
  bool selected_ = false;
  std::u16string input_;

  // Keeps track of mouse-enter and mouse-exit events of child Views.
  OmniboxMouseEnterExitHandler mouse_enter_exit_handler_;

  raw_ptr<PrefService> local_state_ = nullptr;
  raw_ptr<PrefService> profile_prefs_ = nullptr;
  raw_ref<TemplateURLService> template_url_service_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_SEARCH_CONVERSION_PROMOTION_VIEW_H_
