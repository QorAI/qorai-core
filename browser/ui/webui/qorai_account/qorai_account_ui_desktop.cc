/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/qorai_account/qorai_account_ui_desktop.h"

#include <memory>
#include <string>

#include "base/check.h"
#include "base/check_deref.h"
#include "base/functional/bind.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/qorai_account/pref_names.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/web_ui.h"
#include "content/public/common/url_constants.h"
#include "ui/compositor/layer.h"
#include "ui/gfx/geometry/rounded_corners_f.h"
#include "ui/gfx/geometry/size.h"
#include "ui/views/widget/widget.h"
#include "ui/web_dialogs/web_dialog_delegate.h"
#include "ui/webui/webui_util.h"
#include "url/gurl.h"

namespace {

constexpr float kDialogBorderRadius = 16;
constexpr int kDialogWidth = 500;
constexpr gfx::Size kDialogMinSize(kDialogWidth, 336);
constexpr gfx::Size kDialogMaxSize(kDialogWidth, 794);

class QoraiAccountDialogDelegate : public ui::WebDialogDelegate {
 public:
  QoraiAccountDialogDelegate() {
    set_delete_on_close(false);
    set_dialog_content_url(GURL(kQoraiAccountURL));
    set_show_dialog_title(false);
  }
};

}  // namespace

QoraiAccountUIDesktop::QoraiAccountUIDesktop(content::WebUI* web_ui)
    : QoraiAccountUIBase(Profile::FromWebUI(web_ui),
                         base::BindOnce(&webui::SetupWebUIDataSource)),
      ConstrainedWebDialogUI(web_ui) {
  auto* pref_service = CHECK_DEREF(Profile::FromWebUI(web_ui)).GetPrefs();
  CHECK(pref_service);

  pref_verification_token_.Init(
      qorai_account::prefs::kVerificationToken, pref_service,
      base::BindRepeating(&QoraiAccountUIDesktop::OnVerificationTokenChanged,
                          base::Unretained(this)));
}

QoraiAccountUIDesktop::~QoraiAccountUIDesktop() = default;

void QoraiAccountUIDesktop::OnVerificationTokenChanged() {
  if (pref_verification_token_.GetValue().empty()) {
    return;
  }

  auto* constrained_delegate = GetConstrainedDelegate();
  auto* web_dialog_delegate = constrained_delegate
                                  ? constrained_delegate->GetWebDialogDelegate()
                                  : nullptr;
  if (!web_dialog_delegate) {
    return;
  }

  web_dialog_delegate->OnDialogClosed("");
  constrained_delegate->OnDialogCloseFromWebUI();
}

WEB_UI_CONTROLLER_TYPE_IMPL(QoraiAccountUIDesktop)

QoraiAccountUIDesktopConfig::QoraiAccountUIDesktopConfig()
    : DefaultWebUIConfig(content::kChromeUIScheme, kQoraiAccountHost) {
  CHECK(qorai_account::features::IsQoraiAccountEnabled());
}

void ShowQoraiAccountDialog(content::WebUI* web_ui) {
  DCHECK(web_ui);
  auto* delegate = ShowConstrainedWebDialogWithAutoResize(
      Profile::FromWebUI(web_ui),
      std::make_unique<QoraiAccountDialogDelegate>(), web_ui->GetWebContents(),
      kDialogMinSize, kDialogMaxSize);

  DCHECK(delegate);
  auto* widget =
      views::Widget::GetWidgetForNativeWindow(delegate->GetNativeDialog());
  if (!widget) {
    return;
  }

  if (auto* layer = widget->GetLayer()) {
    layer->SetRoundedCornerRadius(gfx::RoundedCornersF(kDialogBorderRadius));
  }
}
