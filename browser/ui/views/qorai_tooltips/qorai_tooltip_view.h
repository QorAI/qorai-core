/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_TOOLTIPS_QORAI_TOOLTIP_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_TOOLTIPS_QORAI_TOOLTIP_VIEW_H_

#include "base/memory/raw_ptr.h"
#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip.h"
#include "qorai/browser/ui/views/qorai_tooltips/qorai_tooltip_label_button.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/views/view.h"

namespace gfx {
class Canvas;
class Point;
}  // namespace gfx

namespace views {
class ImageView;
class Label;
class LabelButton;
class View;
}  // namespace views

namespace qorai_tooltips {

class QoraiTooltipPopup;

class QoraiTooltipView : public views::View {
  METADATA_HEADER(QoraiTooltipView, views::View)
 public:

  QoraiTooltipView(QoraiTooltipPopup* tooltip_popup,
                   const QoraiTooltipAttributes& tooltip_attributes);
  ~QoraiTooltipView() override;

  QoraiTooltipView(const QoraiTooltipView&) = delete;
  QoraiTooltipView& operator=(const QoraiTooltipView&) = delete;

  views::Button* ok_button_for_testing() const { return ok_button_; }
  views::Button* cancel_button_for_testing() const { return cancel_button_; }

  // views::InkDropHostView:
  bool OnMousePressed(const ui::MouseEvent& event) override;
  bool OnMouseDragged(const ui::MouseEvent& event) override;
  void OnMouseReleased(const ui::MouseEvent& event) override;
  void OnDeviceScaleFactorChanged(float old_device_scale_factor,
                                  float new_device_scale_factor) override;
  void OnThemeChanged() override;

 private:
  void CreateView();

  void Close();

  views::View* CreateHeaderView();

  views::ImageView* CreateIconView();

  views::Label* CreateTitleLabel();

  views::View* CreateButtonView();

  QoraiTooltipLabelButton* CreateOkButton();
  void OnOkButtonPressed();

  QoraiTooltipLabelButton* CreateCancelButton();
  void OnCancelButtonPressed();

  views::View* CreateBodyView();
  views::Label* CreateBodyLabel();

  void UpdateTitleLabelColors();
  void UpdateBodyLabelColors();
  void UpdateOkButtonColors();
  void UpdateCancelButtonColors();

  raw_ptr<QoraiTooltipPopup> tooltip_popup_;
  QoraiTooltipAttributes tooltip_attributes_;

  gfx::Point initial_mouse_pressed_location_;
  bool is_dragging_ = false;

  bool is_closing_ = false;

  raw_ptr<views::Label> title_label_ = nullptr;
  raw_ptr<views::Label> body_label_ = nullptr;

  raw_ptr<views::LabelButton> ok_button_ = nullptr;
  raw_ptr<views::LabelButton> cancel_button_ = nullptr;
};

}  // namespace qorai_tooltips

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_TOOLTIPS_QORAI_TOOLTIP_VIEW_H_
