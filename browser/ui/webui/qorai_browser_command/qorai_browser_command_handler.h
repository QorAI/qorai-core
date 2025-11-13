/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// based on //chrome/browser/ui/webui/browser_command/browser_command_handler.h

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_BROWSER_COMMAND_QORAI_BROWSER_COMMAND_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_BROWSER_COMMAND_QORAI_BROWSER_COMMAND_HANDLER_H_

#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "qorai/ui/webui/resources/js/qorai_browser_command/qorai_browser_command.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "ui/base/window_open_disposition.h"
#include "url/gurl.h"

class Profile;

class QoraiBrowserCommandHandler
    : public qorai_browser_command::mojom::QoraiBrowserCommandHandler {
 public:
  // Handles platform-specific browser-level education tasks.
  class Delegate {
   public:
    virtual ~Delegate() = default;
    virtual void OpenURL(const GURL& url,
                         WindowOpenDisposition disposition) = 0;
    virtual void OpenRewardsPanel() = 0;
    virtual void OpenVPNPanel() = 0;
    virtual void OpenAIChat() = 0;
  };

  QoraiBrowserCommandHandler(
      mojo::PendingReceiver<
          qorai_browser_command::mojom::QoraiBrowserCommandHandler>
          pending_page_handler,
      Profile* profile,
      std::vector<qorai_browser_command::mojom::Command> supported_commands,
      std::unique_ptr<Delegate> delegate);

  ~QoraiBrowserCommandHandler() override;

  // qorai_browser_command::mojom::QoraiBrowserCommandHandler:
  void CanExecuteCommand(qorai_browser_command::mojom::Command command_id,
                         CanExecuteCommandCallback callback) override;
  void ExecuteCommand(qorai_browser_command::mojom::Command command_id,
                      ExecuteCommandCallback callback) override;

 private:
  raw_ptr<Profile> profile_;
  std::vector<qorai_browser_command::mojom::Command> supported_commands_;
  std::unique_ptr<Delegate> delegate_;
  mojo::Receiver<qorai_browser_command::mojom::QoraiBrowserCommandHandler>
      page_handler_;
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_BROWSER_COMMAND_QORAI_BROWSER_COMMAND_HANDLER_H_
