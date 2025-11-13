/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/qorai_vpn/qorai_vpn_fallback_dialog_view.h"

#include <memory>
#include <utility>

#include "qorai/components/qorai_vpn/common/pref_names.h"
#include "chrome/browser/about_flags.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/browser_tabstrip.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "components/constrained_window/constrained_window_views.h"
#include "components/grit/qorai_components_strings.h"
#include "components/prefs/pref_service.h"
#include "components/webui/flags/pref_service_flags_storage.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/base/mojom/dialog_button.mojom.h"
#include "ui/views/controls/button/checkbox.h"
#include "ui/views/controls/link.h"
#include "ui/views/controls/styled_label.h"
#include "ui/views/layout/box_layout.h"

namespace qorai {
void ShowQoraiVpnIKEv2FallbackDialog() {
  qorai_vpn::QoraiVpnFallbackDialogView::Show(chrome::FindLastActive());
}
}  // namespace qorai

namespace qorai_vpn {

namespace {

constexpr int kChildSpacing = 16;
constexpr int kPadding = 24;
constexpr int kTopPadding = 32;
constexpr int kBottomPadding = 26;
constexpr int kDialogWidth = 600;

}  // namespace

// static
void QoraiVpnFallbackDialogView::Show(Browser* browser) {
  auto* prefs = browser->profile()->GetPrefs();
  if (!prefs->GetBoolean(prefs::kQoraiVPNWireguardFallbackDialog)) {
    return;
  }

  constrained_window::CreateBrowserModalDialogViews(
      new QoraiVpnFallbackDialogView(browser),
      browser->window()->GetNativeWindow())
      ->Show();
}

QoraiVpnFallbackDialogView::QoraiVpnFallbackDialogView(Browser* browser)
    : browser_(browser), prefs_(browser->profile()->GetPrefs()) {
  SetLayoutManager(std::make_unique<views::BoxLayout>(
      views::BoxLayout::Orientation::kVertical,
      gfx::Insets::TLBR(kTopPadding, kPadding, kBottomPadding, kPadding),
      kChildSpacing));
  SetButtons(static_cast<int>(ui::mojom::DialogButton::kOk) |
             static_cast<int>(ui::mojom::DialogButton::kCancel));
  SetButtonLabel(
      ui::mojom::DialogButton::kOk,
      l10n_util::GetStringUTF16(IDS_QORAI_VPN_FALLBACK_DIALOG_OK_TEXT));
  SetButtonLabel(
      ui::mojom::DialogButton::kCancel,
      l10n_util::GetStringUTF16(IDS_QORAI_VPN_FALLBACK_DIALOG_CANCEL_TEXT));
  SetAcceptCallback(base::BindOnce(&QoraiVpnFallbackDialogView::OnAccept,
                                   base::Unretained(this)));
  auto* header_label = AddChildView(std::make_unique<views::Label>(
      l10n_util::GetStringUTF16(IDS_QORAI_VPN_FALLBACK_DIALOG_TITLE)));
  header_label->SetHorizontalAlignment(gfx::ALIGN_LEFT);

  const std::u16string contents_text =
      l10n_util::GetStringUTF16(IDS_QORAI_VPN_FALLBACK_DIALOG_TEXT);

  auto* contents_label = AddChildView(std::make_unique<views::StyledLabel>());
  contents_label->SetTextContext(views::style::CONTEXT_DIALOG_BODY_TEXT);
  contents_label->SetText(contents_text);
  contents_label->SizeToFit(kDialogWidth);

  RegisterWindowClosingCallback(base::BindOnce(
      &QoraiVpnFallbackDialogView::OnClosing, base::Unretained(this)));

  dont_ask_again_checkbox_ =
      AddChildView(std::make_unique<views::Checkbox>(l10n_util::GetStringUTF16(
          IDS_QORAI_VPN_DNS_SETTINGS_NOTIFICATION_DIALOG_CHECKBOX_TEXT)));
}

QoraiVpnFallbackDialogView::~QoraiVpnFallbackDialogView() = default;

ui::mojom::ModalType QoraiVpnFallbackDialogView::GetModalType() const {
  return ui::mojom::ModalType::kWindow;
}

bool QoraiVpnFallbackDialogView::ShouldShowCloseButton() const {
  return false;
}

bool QoraiVpnFallbackDialogView::ShouldShowWindowTitle() const {
  return false;
}

void QoraiVpnFallbackDialogView::OnClosing() {
  prefs_->SetBoolean(prefs::kQoraiVPNWireguardFallbackDialog,
                     !dont_ask_again_checkbox_->GetChecked());
}

void QoraiVpnFallbackDialogView::OnAccept() {
  g_browser_process->local_state()->SetBoolean(prefs::kQoraiVPNWireguardEnabled,
                                               false);
}

BEGIN_METADATA(QoraiVpnFallbackDialogView)
END_METADATA

}  // namespace qorai_vpn
