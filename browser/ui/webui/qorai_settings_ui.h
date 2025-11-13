/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_SETTINGS_UI_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_SETTINGS_UI_H_

#include <memory>

#include "qorai/components/ai_chat/core/common/mojom/customization_settings.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/settings_helper.mojom.h"
#include "qorai/components/qorai_account/mojom/qorai_account_settings_handler.mojom.h"
#include "qorai/components/qorai_origin/common/mojom/qorai_origin_settings.mojom.h"
#include "qorai/components/commands/common/commands.mojom.h"
#include "qorai/components/containers/buildflags/buildflags.h"
#include "qorai/components/email_aliases/email_aliases.mojom.h"
#include "build/buildflag.h"
#include "chrome/browser/ui/webui/settings/settings_ui.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

#if BUILDFLAG(ENABLE_CONTAINERS)
#include "qorai/components/containers/core/mojom/containers.mojom.h"
#endif

class QoraiSettingsUI;

namespace qorai_account {
class QoraiAccountSettingsHandler;
}

namespace content {
class WebUIDataSource;
}

class Profile;

class QoraiSettingsUIConfig
    : public content::DefaultWebUIConfig<QoraiSettingsUI> {
 public:
  QoraiSettingsUIConfig()
      : DefaultWebUIConfig(content::kChromeUIScheme,
                           chrome::kChromeUISettingsHost) {}
};

class QoraiSettingsUI : public settings::SettingsUI {
 public:
  explicit QoraiSettingsUI(content::WebUI* web_ui);
  QoraiSettingsUI(const QoraiSettingsUI&) = delete;
  QoraiSettingsUI& operator=(const QoraiSettingsUI&) = delete;
  ~QoraiSettingsUI() override;

  static void AddResources(content::WebUIDataSource* html_source,
                           Profile* profile);
  static bool& ShouldExposeElementsForTesting();

  void BindInterface(
      mojo::PendingReceiver<commands::mojom::CommandsService> pending_receiver);
  void BindInterface(mojo::PendingReceiver<ai_chat::mojom::AIChatSettingsHelper>
                         pending_receiver);
  void BindInterface(
      mojo::PendingReceiver<ai_chat::mojom::CustomizationSettingsHandler>
          pending_receiver);
  void BindInterface(
      mojo::PendingReceiver<qorai_account::mojom::QoraiAccountSettingsHandler>
          pending_receiver);

#if BUILDFLAG(ENABLE_CONTAINERS)
  void BindInterface(
      mojo::PendingReceiver<containers::mojom::ContainersSettingsHandler>
          pending_receiver);
#endif

  void BindInterface(
      mojo::PendingReceiver<email_aliases::mojom::EmailAliasesService>
          pending_receiver);

  void BindInterface(
      mojo::PendingReceiver<qorai_origin::mojom::QoraiOriginSettingsHandler>
          pending_receiver);

 private:
  std::unique_ptr<qorai_account::QoraiAccountSettingsHandler>
      qorai_account_settings_handler_;
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_SETTINGS_UI_H_
