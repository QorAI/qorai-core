/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_TOOLTIPS_QORAI_TOOLTIP_LABEL_BUTTON_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_TOOLTIPS_QORAI_TOOLTIP_LABEL_BUTTON_H_

#include <string>

#include "ui/views/controls/button/label_button.h"

namespace qorai_tooltips {

class QoraiTooltipLabelButton : public views::LabelButton {
 public:
  // Creates a QoraiTooltipLabelButton with pressed events sent to |callback|
  // and label |text|. |button_context| is a value from
  // views::style::TextContext and determines the appearance of |text|.
  explicit QoraiTooltipLabelButton(
      PressedCallback callback = PressedCallback(),
      const std::u16string& text = std::u16string(),
      int button_context = views::style::CONTEXT_BUTTON);
  ~QoraiTooltipLabelButton() override;

  QoraiTooltipLabelButton(const QoraiTooltipLabelButton&) = delete;
  QoraiTooltipLabelButton& operator=(const QoraiTooltipLabelButton&) = delete;

  // views::LabelButton:
  ui::Cursor GetCursor(const ui::MouseEvent& event) override;
};

}  // namespace qorai_tooltips

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_TOOLTIPS_QORAI_TOOLTIP_LABEL_BUTTON_H_
