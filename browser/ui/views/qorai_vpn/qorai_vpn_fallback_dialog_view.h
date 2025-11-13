/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_VPN_QORAI_VPN_FALLBACK_DIALOG_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_VPN_QORAI_VPN_FALLBACK_DIALOG_VIEW_H_

#include "ui/views/window/dialog_delegate.h"

class Browser;
class PrefService;

namespace views {
class Checkbox;
}

namespace qorai_vpn {

class QoraiVpnFallbackDialogView : public views::DialogDelegateView {
  METADATA_HEADER(QoraiVpnFallbackDialogView, views::DialogDelegateView)
 public:

  static void Show(Browser* browser);

  QoraiVpnFallbackDialogView(const QoraiVpnFallbackDialogView&) = delete;
  QoraiVpnFallbackDialogView& operator=(const QoraiVpnFallbackDialogView&) =
      delete;

 private:
  explicit QoraiVpnFallbackDialogView(Browser* browser);
  ~QoraiVpnFallbackDialogView() override;

  void OnAccept();
  void OnClosing();

  // views::DialogDelegate overrides:
  ui::mojom::ModalType GetModalType() const override;
  bool ShouldShowCloseButton() const override;
  bool ShouldShowWindowTitle() const override;

  raw_ptr<Browser> browser_ = nullptr;
  raw_ptr<PrefService> prefs_ = nullptr;
  raw_ptr<views::Checkbox> dont_ask_again_checkbox_ = nullptr;
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_VPN_QORAI_VPN_FALLBACK_DIALOG_VIEW_H_
