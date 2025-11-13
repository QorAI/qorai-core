/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SETTINGS_QORA_ASSISTANT_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SETTINGS_QORA_ASSISTANT_HANDLER_H_

#include "base/memory/raw_ptr.h"
#include "base/scoped_observation.h"
#include "qorai/components/sidebar/browser/sidebar_service.h"
#include "chrome/browser/ui/webui/settings/settings_page_ui_handler.h"

class Profile;

namespace settings {

class QoraiQoraAssistantHandler : public settings::SettingsPageUIHandler,
                                 public sidebar::SidebarService::Observer {
 public:
  QoraiQoraAssistantHandler();
  ~QoraiQoraAssistantHandler() override;

  QoraiQoraAssistantHandler(const QoraiQoraAssistantHandler&) = delete;
  QoraiQoraAssistantHandler& operator=(const QoraiQoraAssistantHandler&) = delete;

 private:
  // SettingsPageUIHandler overrides:
  void RegisterMessages() override;
  void OnJavascriptAllowed() override;
  void OnJavascriptDisallowed() override;

  // sidebar::SidebarService::Observer overrides
  void OnItemAdded(const sidebar::SidebarItem& item, size_t index) override;
  void OnItemRemoved(const sidebar::SidebarItem& item, size_t index) override;

  void NotifyChatUiChanged(const bool& isQoraVisible);

  void HandleValidateModelEndpoint(const base::Value::List& args);
  void HandleToggleQoraIcon(const base::Value::List& args);
  void HandleGetQoraIconVisibility(const base::Value::List& args);
  void HandleResetQoraData(const base::Value::List& args);

  raw_ptr<Profile> profile_ = nullptr;
  base::ScopedObservation<sidebar::SidebarService,
                          sidebar::SidebarService::Observer>
      sidebar_service_observer_{this};
};

}  // namespace settings

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SETTINGS_QORA_ASSISTANT_HANDLER_H_
