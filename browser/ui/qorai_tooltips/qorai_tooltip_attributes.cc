/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip_attributes.h"

namespace qorai_tooltips {

QoraiTooltipAttributes::QoraiTooltipAttributes(
    const std::u16string& title,
    const std::u16string& body,
    const std::u16string& ok_button_text,
    const std::u16string& cancel_button_text)
    : title_(title),
      body_(body),
      ok_button_text_(ok_button_text),
      cancel_button_text_(cancel_button_text) {
  if (!cancel_button_text.empty()) {
    cancel_button_enabled_ = true;
  }
}

QoraiTooltipAttributes::~QoraiTooltipAttributes() = default;

QoraiTooltipAttributes::QoraiTooltipAttributes(
    const QoraiTooltipAttributes& other) = default;

QoraiTooltipAttributes& QoraiTooltipAttributes::operator=(
    const QoraiTooltipAttributes& other) = default;

}  // namespace qorai_tooltips
