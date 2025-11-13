/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_TOOLTIPS_QORAI_TOOLTIP_POPUP_HANDLER_H_
#define QORAI_BROWSER_UI_QORAI_TOOLTIPS_QORAI_TOOLTIP_POPUP_HANDLER_H_

#include <memory>
#include <string>

namespace qorai_tooltips {

class QoraiTooltip;

class QoraiTooltipPopupHandler {
 public:
  QoraiTooltipPopupHandler();
  ~QoraiTooltipPopupHandler();

  QoraiTooltipPopupHandler(const QoraiTooltipPopupHandler&) = delete;
  QoraiTooltipPopupHandler& operator=(const QoraiTooltipPopupHandler&) = delete;

  // Show the |tooltip|.
  static void Show(std::unique_ptr<QoraiTooltip> tooltip);

  // Close the tooltip with the associated |tooltip_id|.
  static void Close(const std::string& tooltip_id);

  // Destroy the tooltip with the associated |tooltip_id|.
  static void Destroy(const std::string& tooltip_id);
};

}  // namespace qorai_tooltips

#endif  // QORAI_BROWSER_UI_QORAI_TOOLTIPS_QORAI_TOOLTIP_POPUP_HANDLER_H_
