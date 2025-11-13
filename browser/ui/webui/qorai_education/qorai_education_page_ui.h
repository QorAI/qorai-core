// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// based on //chrome/browser/ui/webui/whats_new/whats_new_ui.h

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_EDUCATION_QORAI_EDUCATION_PAGE_UI_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_EDUCATION_QORAI_EDUCATION_PAGE_UI_H_

#include <memory>

#include "qorai/browser/ui/webui/qorai_browser_command/qorai_browser_command_handler.h"
#include "qorai/browser/ui/webui/qorai_education/qorai_education.mojom.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/ui/webui/resources/js/qorai_browser_command/qorai_browser_command.mojom.h"
#include "content/public/browser/webui_config.h"
#include "content/public/common/url_constants.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "ui/webui/mojo_web_ui_controller.h"
#include "url/gurl.h"

namespace content {
class WebUI;
}

class QoraiEducationHandler;
class QoraiEducationPageUI;

class QoraiEducationPageUIConfig
    : public content::DefaultWebUIConfig<QoraiEducationPageUI> {
 public:
  QoraiEducationPageUIConfig()
      : DefaultWebUIConfig(content::kChromeUIScheme, kQoraiGettingStartedHost) {
  }
};

// The Web UI controller for the Qorai product education page, which displays
// production education website content in an iframe.
class QoraiEducationPageUI
    : public ui::MojoWebUIController,
      public qorai_browser_command::mojom::QoraiBrowserCommandHandlerFactory,
      public qorai_education::mojom::PageHandlerFactory {
 public:
  QoraiEducationPageUI(content::WebUI* web_ui, const GURL& url);
  ~QoraiEducationPageUI() override;

  // Instantiates the implementor of the
  // qorai_education::mojom::PageHandlerFactory mojo interface.
  void BindInterface(
      mojo::PendingReceiver<qorai_education::mojom::PageHandlerFactory>
          receiver);

  // Instantiates the implementor of the
  // browser_command::mojom::QoraiBrowserCommandHandler mojo interface.
  void BindInterface(
      mojo::PendingReceiver<
          qorai_browser_command::mojom::QoraiBrowserCommandHandlerFactory>
          pending_receiver);

  QoraiEducationPageUI(const QoraiEducationPageUI&) = delete;
  QoraiEducationPageUI& operator=(const QoraiEducationPageUI&) = delete;

 private:
  // qorai_education::mojom::PageHandlerFactory:
  void CreatePageHandler(
      mojo::PendingRemote<qorai_education::mojom::Page> page,
      mojo::PendingReceiver<qorai_education::mojom::PageHandler> receiver)
      override;

  std::unique_ptr<QoraiEducationHandler> page_handler_;
  mojo::Receiver<qorai_education::mojom::PageHandlerFactory>
      page_factory_receiver_{this};

  // qorai_browser_command::mojom::QoraiBrowserCommandHandlerFactory:
  void CreateBrowserCommandHandler(
      mojo::PendingReceiver<
          qorai_browser_command::mojom::QoraiBrowserCommandHandler> handler)
      override;

  std::unique_ptr<QoraiBrowserCommandHandler> command_handler_;
  mojo::Receiver<
      qorai_browser_command::mojom::QoraiBrowserCommandHandlerFactory>
      browser_command_factory_receiver_;
  raw_ptr<Profile> profile_;

  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_EDUCATION_QORAI_EDUCATION_PAGE_UI_H_
