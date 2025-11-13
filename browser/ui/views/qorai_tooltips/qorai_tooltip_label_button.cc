/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/qorai_tooltips/qorai_tooltip_label_button.h"

#include <utility>

#include "ui/base/cursor/cursor.h"

namespace qorai_tooltips {

QoraiTooltipLabelButton::QoraiTooltipLabelButton(PressedCallback callback,
                                                 const std::u16string& text,
                                                 int button_context)
    : LabelButton(std::move(callback), text, button_context) {}

QoraiTooltipLabelButton::~QoraiTooltipLabelButton() = default;

ui::Cursor QoraiTooltipLabelButton::GetCursor(const ui::MouseEvent& event) {
  if (!GetEnabled())
    return ui::Cursor();
  return ui::mojom::CursorType::kHand;
}

}  // namespace qorai_tooltips
