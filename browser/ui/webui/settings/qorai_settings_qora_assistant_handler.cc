/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_settings_qora_assistant_handler.h"

#include <algorithm>
#include <vector>

#include "base/containers/contains.h"
#include "qorai/browser/ai_chat/ai_chat_service_factory.h"
#include "qorai/browser/ui/sidebar/sidebar_service_factory.h"
#include "qorai/components/ai_chat/core/browser/ai_chat_service.h"
#include "qorai/components/ai_chat/core/browser/model_validator.h"
#include "qorai/components/ai_chat/core/browser/utils.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/ai_chat/core/common/prefs.h"
#include "qorai/components/sidebar/browser/sidebar_item.h"
#include "qorai/components/sidebar/browser/sidebar_service.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/web_contents.h"

namespace {

const std::vector<sidebar::SidebarItem>::const_iterator FindAiChatSidebarItem(
    const std::vector<sidebar::SidebarItem>& items) {
  return std::ranges::find_if(items, [](const auto& item) {
    return item.built_in_item_type ==
           sidebar::SidebarItem::BuiltInItemType::kChatUI;
  });
}

bool ShowQoraAssistantIconVisibleIfNot(
    sidebar::SidebarService* sidebar_service) {
  const auto hidden_items = sidebar_service->GetHiddenDefaultSidebarItems();
  const auto item_hidden_iter = FindAiChatSidebarItem(hidden_items);

  if (item_hidden_iter != hidden_items.end()) {
    sidebar_service->AddItem(*item_hidden_iter);
    return true;
  }

  return false;
}

bool HideQoraAssistantIconIfNot(sidebar::SidebarService* sidebar_service) {
  const auto visible_items = sidebar_service->items();
  const auto item_visible_iter = FindAiChatSidebarItem(visible_items);

  if (item_visible_iter != visible_items.end()) {
    sidebar_service->RemoveItemAt(item_visible_iter - visible_items.begin());
    return true;
  }

  return false;
}

}  // namespace

namespace settings {

QoraiQoraAssistantHandler::QoraiQoraAssistantHandler() = default;

QoraiQoraAssistantHandler::~QoraiQoraAssistantHandler() = default;

void QoraiQoraAssistantHandler::RegisterMessages() {
  profile_ = Profile::FromWebUI(web_ui());

  web_ui()->RegisterMessageCallback(
      "toggleQoraIcon",
      base::BindRepeating(&QoraiQoraAssistantHandler::HandleToggleQoraIcon,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getQoraIconVisibility",
      base::BindRepeating(&QoraiQoraAssistantHandler::HandleGetQoraIconVisibility,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "resetQoraData",
      base::BindRepeating(&QoraiQoraAssistantHandler::HandleResetQoraData,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "validateModelEndpoint",
      base::BindRepeating(
          &QoraiQoraAssistantHandler::HandleValidateModelEndpoint,
          base::Unretained(this)));
}

void QoraiQoraAssistantHandler::OnJavascriptAllowed() {
  sidebar_service_observer_.Reset();
  sidebar_service_observer_.Observe(
      sidebar::SidebarServiceFactory::GetForProfile(profile_));
}

void QoraiQoraAssistantHandler::OnJavascriptDisallowed() {
  sidebar_service_observer_.Reset();
}

void QoraiQoraAssistantHandler::OnItemAdded(const sidebar::SidebarItem& item,
                                           size_t index) {
  if (item.built_in_item_type ==
      sidebar::SidebarItem::BuiltInItemType::kChatUI) {
    NotifyChatUiChanged(true);
  }
}

void QoraiQoraAssistantHandler::OnItemRemoved(const sidebar::SidebarItem& item,
                                             size_t index) {
  if (item.built_in_item_type ==
      sidebar::SidebarItem::BuiltInItemType::kChatUI) {
    NotifyChatUiChanged(false);
  }
}

void QoraiQoraAssistantHandler::NotifyChatUiChanged(const bool& is_qora_visible) {
  if (!IsJavascriptAllowed()) {
    return;
  }
  FireWebUIListener("settings-qorai-qora-assistant-changed", is_qora_visible);
}

void QoraiQoraAssistantHandler::HandleToggleQoraIcon(
    const base::Value::List& args) {
  auto* service = sidebar::SidebarServiceFactory::GetForProfile(profile_);

  AllowJavascript();
  if (!ShowQoraAssistantIconVisibleIfNot(service)) {
    HideQoraAssistantIconIfNot(service);
  }
}

void QoraiQoraAssistantHandler::HandleValidateModelEndpoint(
    const base::Value::List& args) {
  AllowJavascript();

  if (args.size() < 2 || !args[1].is_dict()) {
    // Expect the appropriate number and type of arguments, or reject
    RejectJavascriptCallback(args[0], base::Value("Invalid arguments"));
    return;
  }

  const base::Value::Dict& dict = args[1].GetDict();
  GURL endpoint(*dict.FindString("url"));

  base::Value::Dict response;

  const bool is_valid = ai_chat::ModelValidator::IsValidEndpoint(endpoint);

  response.Set("isValid", is_valid);
  response.Set("isValidAsPrivateEndpoint",
               ai_chat::ModelValidator::IsValidEndpoint(
                   endpoint, std::optional<bool>(true)));
  response.Set("isValidDueToPrivateIPsFeature",
               is_valid && ai_chat::features::IsAllowPrivateIPsEnabled() &&
                   !ai_chat::ModelValidator::IsValidEndpoint(
                       endpoint, std::optional<bool>(false)));

  ResolveJavascriptCallback(args[0], response);
}

void QoraiQoraAssistantHandler::HandleGetQoraIconVisibility(
    const base::Value::List& args) {
  auto* service = sidebar::SidebarServiceFactory::GetForProfile(profile_);
  const auto hidden_items = service->GetHiddenDefaultSidebarItems();
  AllowJavascript();
  ResolveJavascriptCallback(
      args[0], !base::Contains(hidden_items,
                               sidebar::SidebarItem::BuiltInItemType::kChatUI,
                               &sidebar::SidebarItem::built_in_item_type));
}

void QoraiQoraAssistantHandler::HandleResetQoraData(
    const base::Value::List& args) {
  auto* sidebar_service =
      sidebar::SidebarServiceFactory::GetForProfile(profile_);

  ShowQoraAssistantIconVisibleIfNot(sidebar_service);

  ai_chat::AIChatService* service =
      ai_chat::AIChatServiceFactory::GetForBrowserContext(profile_);
  if (!service) {
    return;
  }
  service->DeleteConversations();
  if (profile_) {
    ai_chat::SetUserOptedIn(profile_->GetPrefs(), false);
    ai_chat::prefs::DeleteAllMemoriesFromPrefs(*profile_->GetPrefs());
    ai_chat::prefs::ResetCustomizationsPref(*profile_->GetPrefs());
  }

  AllowJavascript();
}

}  // namespace settings
