// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// based on //chrome/browser/ui/webui/whats_new/whats_new_ui.cc

#include "qorai/browser/ui/webui/qorai_education/qorai_education_page_ui.h"

#include <string>
#include <utility>
#include <vector>

#include "base/check.h"
#include "qorai/browser/ui/webui/qorai_browser_command/qorai_browser_command_handler.h"
#include "qorai/browser/ui/webui/qorai_education/qorai_education_handler.h"
#include "qorai/browser/ui/webui/qorai_education/qorai_education_page_delegate_desktop.h"
#include "qorai/browser/ui/webui/qorai_webui_source.h"
#include "qorai/components/qorai_education/education_urls.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/grit/qorai_education_resources.h"
#include "qorai/grit/qorai_education_resources_map.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/grit/branded_strings.h"
#include "chrome/grit/generated_resources.h"
#include "components/grit/qorai_components_strings.h"
#include "components/tabs/public/tab_interface.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"
#include "services/network/public/mojom/content_security_policy.mojom.h"
#include "ui/webui/webui_util.h"

namespace {

void CreateAndAddWhatsNewUIHtmlSource(content::WebUI* web_ui,
                                      Profile* profile) {
  content::WebUIDataSource* source =
      content::WebUIDataSource::CreateAndAdd(profile, kQoraiGettingStartedHost);
  webui::SetupWebUIDataSource(
      source, base::span<const webui::ResourcePath>(kQoraiEducationResources),
      IDR_QORAI_EDUCATION_QORAI_EDUCATION_HTML);

  AddBackgroundColorToSource(source, web_ui->GetWebContents());

  static constexpr webui::LocalizedString kStrings[] = {
      {"title", IDS_WELCOME_HEADER}};
  source->AddLocalizedStrings(kStrings);

  // Allow embedding of iframe content from allowed domains.
  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ChildSrc,
      "child-src chrome://webui-test https://browser-education.qorai.com;");
}

}  // namespace

QoraiEducationPageUI::QoraiEducationPageUI(content::WebUI* web_ui,
                                           const GURL& url)
    : ui::MojoWebUIController(web_ui, /*enable_chrome_send=*/true),
      page_factory_receiver_(this),
      browser_command_factory_receiver_(this),
      profile_(Profile::FromWebUI(web_ui)) {
  CreateAndAddWhatsNewUIHtmlSource(web_ui, profile_);
}

WEB_UI_CONTROLLER_TYPE_IMPL(QoraiEducationPageUI)

void QoraiEducationPageUI::BindInterface(
    mojo::PendingReceiver<qorai_education::mojom::PageHandlerFactory>
        receiver) {
  page_factory_receiver_.reset();
  page_factory_receiver_.Bind(std::move(receiver));
}

void QoraiEducationPageUI::CreatePageHandler(
    mojo::PendingRemote<qorai_education::mojom::Page> page,
    mojo::PendingReceiver<qorai_education::mojom::PageHandler> receiver) {
  DCHECK(page);

  auto* web_contents = web_ui()->GetWebContents();
  auto education_page_type = qorai_education::EducationPageTypeFromBrowserURL(
      web_contents->GetVisibleURL());

  page_handler_ = std::make_unique<QoraiEducationHandler>(
      std::move(receiver), std::move(page), *education_page_type);
}

void QoraiEducationPageUI::BindInterface(
    mojo::PendingReceiver<QoraiBrowserCommandHandlerFactory> pending_receiver) {
  if (browser_command_factory_receiver_.is_bound()) {
    browser_command_factory_receiver_.reset();
  }
  browser_command_factory_receiver_.Bind(std::move(pending_receiver));
}

void QoraiEducationPageUI::CreateBrowserCommandHandler(
    mojo::PendingReceiver<
        qorai_browser_command::mojom::QoraiBrowserCommandHandler>
        pending_handler) {
  std::vector<qorai_browser_command::mojom::Command> supported_commands = {};

  supported_commands.insert(
      supported_commands.end(),
      {qorai_browser_command::mojom::Command::kOpenRewardsOnboarding,
       qorai_browser_command::mojom::Command::kOpenWalletOnboarding,
       qorai_browser_command::mojom::Command::kOpenVPNOnboarding,
       qorai_browser_command::mojom::Command::kOpenAIChat});

  auto* web_contents = web_ui()->GetWebContents();
  auto* tab = tabs::TabInterface::GetFromContents(web_contents);
  CHECK(tab);

  command_handler_ = std::make_unique<QoraiBrowserCommandHandler>(
      std::move(pending_handler), profile_, supported_commands,
      std::make_unique<qorai_education::QoraiEducationPageDelegateDesktop>(
          *tab->GetBrowserWindowInterface()));
}

QoraiEducationPageUI::~QoraiEducationPageUI() = default;
