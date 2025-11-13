/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_EDUCATION_QORAI_EDUCATION_PAGE_DELEGATE_DESKTOP_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_EDUCATION_QORAI_EDUCATION_PAGE_DELEGATE_DESKTOP_H_

#include "base/memory/raw_ref.h"
#include "qorai/browser/ui/webui/qorai_browser_command/qorai_browser_command_handler.h"
#include "ui/base/window_open_disposition.h"
#include "url/gurl.h"

class BrowserWindowInterface;

namespace qorai_education {

// Handles browser-level requests from the Qorai Education WebUI.
class QoraiEducationPageDelegateDesktop
    : public QoraiBrowserCommandHandler::Delegate {
 public:
  explicit QoraiEducationPageDelegateDesktop(
      BrowserWindowInterface& window_interface);
  ~QoraiEducationPageDelegateDesktop() override;

  void OpenURL(const GURL& url, WindowOpenDisposition disposition) override;
  void OpenRewardsPanel() override;
  void OpenVPNPanel() override;
  void OpenAIChat() override;

 private:
  // The browser window interface for tab w/ qorai_education's WebUI.
  raw_ref<BrowserWindowInterface> window_interface_;
};

}  // namespace qorai_education

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_EDUCATION_QORAI_EDUCATION_PAGE_DELEGATE_DESKTOP_H_
