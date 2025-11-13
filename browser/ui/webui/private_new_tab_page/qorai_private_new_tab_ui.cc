// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/private_new_tab_page/qorai_private_new_tab_ui.h"

#include <utility>

#include "qorai/browser/ui/webui/qorai_webui_source.h"
#include "qorai/browser/ui/webui/private_new_tab_page/qorai_private_new_tab_page_handler.h"
#include "qorai/components/qorai_private_new_tab/resources/page/grit/qorai_private_new_tab_generated_map.h"
#include "qorai/components/qorai_private_new_tab_ui/common/constants.h"
#include "qorai/components/qorai_private_new_tab_ui/common/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "components/grit/qorai_components_resources.h"
#include "components/prefs/pref_service.h"
#include "components/strings/grit/components_strings.h"
#include "content/public/browser/web_ui_data_source.h"
#include "ui/base/l10n/l10n_util.h"

bool QoraiPrivateNewTabUIConfig::IsWebUIEnabled(
    content::BrowserContext* browser_context) {
  Profile* profile = Profile::FromBrowserContext(browser_context);
  return profile->IsIncognitoProfile() || profile->IsTor() ||
         profile->IsGuestSession();
}

QoraiPrivateNewTabUI::QoraiPrivateNewTabUI(content::WebUI* web_ui)
    : ui::MojoWebUIController(web_ui, false) {
  Profile* profile = Profile::FromWebUI(web_ui);

  web_ui->OverrideTitle(l10n_util::GetStringUTF16(IDS_NEW_INCOGNITO_TAB_TITLE));

  content::WebUIDataSource* source = CreateAndAddWebUIDataSource(
      web_ui, chrome::kChromeUINewTabHost, kQoraiPrivateNewTabGenerated,
      IDR_QORAI_PRIVATE_NEW_TAB_HTML);

  for (const auto& str : qorai_private_new_tab::kLocalizedStrings) {
    std::u16string l10n_str = l10n_util::GetStringUTF16(str.id);
    source->AddString(str.name, l10n_str);
  }

  source->AddBoolean("isWindowTor", profile->IsTor());

  AddBackgroundColorToSource(source, web_ui->GetWebContents());
}

QoraiPrivateNewTabUI::~QoraiPrivateNewTabUI() = default;

void QoraiPrivateNewTabUI::BindInterface(
    mojo::PendingReceiver<qorai_private_new_tab::mojom::PageHandler> receiver) {
  private_tab_page_handler_ = std::make_unique<QoraiPrivateNewTabPageHandler>(
      Profile::FromWebUI(web_ui()), web_ui()->GetWebContents(),
      std::move(receiver));
}

WEB_UI_CONTROLLER_TYPE_IMPL(QoraiPrivateNewTabUI)
