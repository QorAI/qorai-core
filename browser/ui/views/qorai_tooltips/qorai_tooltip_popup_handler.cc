/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip_popup_handler.h"

#include <map>
#include <string>

#include "base/check.h"
#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip.h"
#include "qorai/browser/ui/views/qorai_tooltips/qorai_tooltip_popup.h"

namespace {

// TODO(https://github.com/qorai/qorai-browser/issues/48713): This is a case of
// `-Wexit-time-destructors` violation and `[[clang::no_destroy]]` has been
// added in the meantime to fix the build error. Remove this attribute and
// provide a proper fix.
[[clang::no_destroy]] std::map<
    std::string,
    qorai_tooltips::QoraiTooltipPopup* /* NOT OWNED */> tooltip_popups_;

}  // namespace

namespace qorai_tooltips {

QoraiTooltipPopupHandler::QoraiTooltipPopupHandler() = default;

QoraiTooltipPopupHandler::~QoraiTooltipPopupHandler() = default;

// static
void QoraiTooltipPopupHandler::Show(std::unique_ptr<QoraiTooltip> tooltip) {
  DCHECK(tooltip);

  const std::string tooltip_id = tooltip->id();
  if (!tooltip_popups_[tooltip_id]) {
    tooltip_popups_[tooltip_id] = new QoraiTooltipPopup(std::move(tooltip));
    tooltip_popups_[tooltip_id]->Show();
  }
}

// static
void QoraiTooltipPopupHandler::Close(const std::string& tooltip_id) {
  DCHECK(!tooltip_id.empty());

  if (!tooltip_popups_[tooltip_id]) {
    return;
  }

  tooltip_popups_[tooltip_id]->Close();
}

// static
void QoraiTooltipPopupHandler::Destroy(const std::string& tooltip_id) {
  DCHECK(!tooltip_id.empty());

  // Note: The pointed-to QoraiTooltipPopup members are deallocated by their
  // containing Widgets
  tooltip_popups_.erase(tooltip_id);
}

}  // namespace qorai_tooltips
