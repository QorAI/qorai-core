/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// based on //chrome/browser/ui/webui/browser_command/browser_command_handler.cc

#include "qorai/browser/ui/webui/qorai_browser_command/qorai_browser_command_handler.h"

#include "base/containers/contains.h"
#include "qorai/browser/ai_chat/ai_chat_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/components/qorai_education/education_urls.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "chrome/browser/profiles/profile.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/vpn_utils.h"
#endif

namespace {

bool CanShowWalletOnboarding(Profile* profile) {
  return qorai_wallet::QoraiWalletServiceFactory::GetServiceForContext(
             profile) != nullptr;
}

bool CanShowRewardsOnboarding(Profile* profile) {
  return qorai_rewards::RewardsServiceFactory::GetForProfile(profile) !=
         nullptr;
}

bool CanShowVPNBubble(Profile* profile) {
#if BUILDFLAG(ENABLE_QORAI_VPN)
  return qorai_vpn::IsAllowedForContext(profile);
#else
  return false;
#endif
}

bool CanShowAIChat(Profile* profile) {
  return ai_chat::AIChatServiceFactory::GetForBrowserContext(profile) !=
         nullptr;
}

}  // namespace

QoraiBrowserCommandHandler::QoraiBrowserCommandHandler(
    mojo::PendingReceiver<
        qorai_browser_command::mojom::QoraiBrowserCommandHandler>
        pending_page_handler,
    Profile* profile,
    std::vector<qorai_browser_command::mojom::Command> supported_commands,
    std::unique_ptr<Delegate> delegate)
    : profile_(profile),
      supported_commands_(supported_commands),
      delegate_(std::move(delegate)),
      page_handler_(this, std::move(pending_page_handler)) {}

QoraiBrowserCommandHandler::~QoraiBrowserCommandHandler() = default;

void QoraiBrowserCommandHandler::CanExecuteCommand(
    qorai_browser_command::mojom::Command command_id,
    CanExecuteCommandCallback callback) {
  if (!base::Contains(supported_commands_, command_id)) {
    std::move(callback).Run(false);
    return;
  }

  bool can_execute = false;
  switch (command_id) {
    case qorai_browser_command::mojom::Command::kOpenWalletOnboarding:
      can_execute = CanShowWalletOnboarding(profile_);
      break;
    case qorai_browser_command::mojom::Command::kOpenRewardsOnboarding:
      can_execute = CanShowRewardsOnboarding(profile_);
      break;
    case qorai_browser_command::mojom::Command::kOpenVPNOnboarding:
      can_execute = CanShowVPNBubble(profile_);
      break;
    case qorai_browser_command::mojom::Command::kOpenAIChat:
      can_execute = CanShowAIChat(profile_);
      break;
  }
  std::move(callback).Run(can_execute);
}

void QoraiBrowserCommandHandler::ExecuteCommand(
    qorai_browser_command::mojom::Command command_id,
    ExecuteCommandCallback callback) {
  if (!base::Contains(supported_commands_, command_id)) {
    std::move(callback).Run(false);
    return;
  }

  switch (command_id) {
    case qorai_browser_command::mojom::Command::kOpenWalletOnboarding:
      delegate_->OpenURL(GURL(kQoraiUIWalletURL),
                         WindowOpenDisposition::NEW_FOREGROUND_TAB);
      break;
    case qorai_browser_command::mojom::Command::kOpenRewardsOnboarding:
      delegate_->OpenRewardsPanel();
      break;
    case qorai_browser_command::mojom::Command::kOpenVPNOnboarding:
#if BUILDFLAG(ENABLE_QORAI_VPN)
      delegate_->OpenVPNPanel();
      break;
#else
      std::move(callback).Run(false);
      return;
#endif
    case qorai_browser_command::mojom::Command::kOpenAIChat:
      delegate_->OpenAIChat();
      break;
  }

  std::move(callback).Run(true);
}
