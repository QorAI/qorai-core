/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_TOOLTIPS_QORAI_TOOLTIP_POPUP_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_TOOLTIPS_QORAI_TOOLTIP_POPUP_H_

#include <cstdint>
#include <memory>
#include <string>

#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "base/scoped_observation.h"
#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip.h"
#include "qorai/browser/ui/views/qorai_tooltips/qorai_tooltip_view.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/display/display_observer.h"
#include "ui/gfx/shadow_util.h"
#include "ui/gfx/shadow_value.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/widget/widget_delegate.h"
#include "ui/views/widget/widget_observer.h"

class QoraiTooltipsTest;
FORWARD_DECLARE_TEST(QoraiTooltipsTest, OkButtonPressed);
FORWARD_DECLARE_TEST(QoraiTooltipsTest, CancelButtonPressed);

namespace gfx {
class Point;
class Rect;
class Size;
}  // namespace gfx

namespace views {
class Widget;
}  // namespace views

namespace qorai_tooltips {

class QoraiTooltipView;

// Provides a generalized interface for displaying user-actionable tooltips on
// the desktop window.
//
// Usage example:
//   auto tooltip = std::make_unique<qorai_tooltips::QoraiTooltip>(
//       "id", qorai_tooltips::QoraiTooltipAttributes(u"Title", u"Body", u"OK"),
//       this);
//   auto popup = std::make_unique<qorai_tooltips::QoraiTooltipPopup>(
//       std::move(tooltip));
//   popup->Show();
//   ...
//   popup->Close();
//
// This creates and show a tooltip with the given attributes/controls. Button
// presseses will forward to the delegate (set via the QoraiTooltip
// constructor). Finally, the tooltip is closed.
class QoraiTooltipPopup : public views::WidgetDelegateView,
                          public views::WidgetObserver,
                          public display::DisplayObserver {
  METADATA_HEADER(QoraiTooltipPopup, views::WidgetDelegateView)
 public:
  explicit QoraiTooltipPopup(std::unique_ptr<QoraiTooltip> tooltip);
  ~QoraiTooltipPopup() override;

  QoraiTooltipPopup(const QoraiTooltipPopup&) = delete;
  QoraiTooltipPopup& operator=(const QoraiTooltipPopup&) = delete;

  // Show the tooltip popup view
  void Show();

  // Close the tooltip popup view
  void Close();

  // Close the widget
  void CloseWidget();

  // User pressed the Ok button
  void OnOkButtonPressed();

  // User pressed the Cancel button
  void OnCancelButtonPressed();

  gfx::Rect CalculateBounds(bool use_default_origin);

  void set_normalized_display_coordinates(double x, double y);

  void set_display_work_area_insets(int x, int y);

  views::Button* ok_button_for_testing() const {
    return tooltip_view_ ? tooltip_view_->ok_button_for_testing() : nullptr;
  }

  views::Button* cancel_button_for_testing() const {
    return tooltip_view_ ? tooltip_view_->cancel_button_for_testing() : nullptr;
  }

  // display::DisplayObserver:
  void OnDisplaysRemoved(const display::Displays& old_displays) override;
  void OnDisplayMetricsChanged(const display::Display& display,
                               uint32_t changed_metrics) override;

  // views::WidgetDelegateView:
  void OnDisplayChanged() override;
  void OnWorkAreaChanged() override;
  void OnPaintBackground(gfx::Canvas* canvas) override;
  void OnThemeChanged() override;

  // views::WidgetObserver:
  void OnWidgetCreated(views::Widget* widget) override;
  void OnWidgetDestroyed(views::Widget* widget) override;
  void OnWidgetBoundsChanged(views::Widget* widget,
                             const gfx::Rect& new_bounds) override;

 private:
  FRIEND_TEST_ALL_PREFIXES(::QoraiTooltipsTest, OkButtonPressed);
  FRIEND_TEST_ALL_PREFIXES(::QoraiTooltipsTest, CancelButtonPressed);
  friend class ::QoraiTooltipsTest;
  void CreatePopup();

  gfx::Point GetDefaultOriginForSize(const gfx::Size& size);

  void RecomputeAlignment();

  const gfx::ShadowDetails& GetShadowDetails() const;
  gfx::Insets GetShadowMargin() const;

  void CreateWidgetView();
  void CloseWidgetView();

  bool IsWidgetValid() const;

  std::unique_ptr<views::Widget> widget_;
  std::unique_ptr<QoraiTooltip> tooltip_;

  raw_ptr<QoraiTooltipView> tooltip_view_ = nullptr;

  gfx::Point widget_origin_ = {0, 0};

  double normalized_display_coordinate_x_ = 1.0;
  double normalized_display_coordinate_y_ = 0.0;

  int display_work_area_inset_x_ = -13;
  int display_work_area_inset_y_ = 18;

  base::ScopedObservation<views::Widget, views::WidgetObserver>
      widget_observation_{this};
};

}  // namespace qorai_tooltips

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_TOOLTIPS_QORAI_TOOLTIP_POPUP_H_
