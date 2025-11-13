/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip.h"

#include <vector>

#include "base/strings/string_util.h"

namespace qorai_tooltips {

QoraiTooltip::QoraiTooltip(const std::string& id,
                           const QoraiTooltipAttributes& attributes,
                           base::WeakPtr<QoraiTooltipDelegate> delegate)
    : id_(id), attributes_(attributes), delegate_(std::move(delegate)) {}

QoraiTooltip::~QoraiTooltip() = default;

std::u16string QoraiTooltip::accessible_name() const {
  std::vector<std::u16string> accessible_lines;

  if (!attributes_.title().empty()) {
    accessible_lines.push_back(attributes_.title());
  }

  if (!attributes_.body().empty()) {
    accessible_lines.push_back(attributes_.body());
  }

  return base::JoinString(accessible_lines, u"\n");
}

}  // namespace qorai_tooltips
