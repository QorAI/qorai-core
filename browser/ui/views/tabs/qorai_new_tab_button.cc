/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/tabs/qorai_new_tab_button.h"

#include <utility>

#include "qorai/browser/ui/tabs/features.h"
#include "qorai/components/vector_icons/vector_icons.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/gfx/paint_vector_icon.h"

using tabs::features::HorizontalTabsUpdateEnabled;

// static
gfx::Size QoraiNewTabButton::GetButtonSize() {
  if (!HorizontalTabsUpdateEnabled()) {
    return {24, 24};
  }
  return {28, 28};
}

gfx::Size QoraiNewTabButton::CalculatePreferredSize(
    const views::SizeBounds& available_size) const {
  // Overridden so that we use Qorai's custom button size
  gfx::Size size = GetButtonSize();
  const auto insets = GetInsets();
  size.Enlarge(insets.width(), insets.height());
  return size;
}

QoraiNewTabButton::QoraiNewTabButton(TabStripController* tab_strip_controller,
                                     PressedCallback callback,
                                     const gfx::VectorIcon& icon,
                                     Edge fixed_flat_edge,
                                     Edge animated_flat_edge,
                                     BrowserWindowInterface* browser)
    : NewTabButton(tab_strip_controller,
                   std::move(callback),
                   kQoraPlusAddIcon,
                   fixed_flat_edge,
                   animated_flat_edge,
                   browser) {}

QoraiNewTabButton::~QoraiNewTabButton() = default;

BEGIN_METADATA(QoraiNewTabButton)
END_METADATA
