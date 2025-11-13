/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_wallet/qorai_wallet_tab_helper.h"

#include <string>
#include <utility>
#include <vector>

#include "base/check.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_provider_delegate_impl.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/cardano/cardano_provider_impl.h"
#include "qorai/components/qorai_wallet/browser/ethereum_provider_impl.h"
#include "qorai/components/qorai_wallet/browser/permission_utils.h"
#include "qorai/components/qorai_wallet/browser/solana_provider_impl.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "components/permissions/permission_request.h"
#include "components/permissions/permission_request_manager.h"
#include "components/permissions/request_type.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/global_routing_id.h"
#include "content/public/browser/web_contents.h"

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/qorai_wallet/wallet_bubble_manager_delegate.h"
#endif

namespace qorai_wallet {

namespace {

std::unique_ptr<QorAIWalletProviderDelegate> CreateDelegate(
    content::WebContents* web_contents,
    content::GlobalRenderFrameHostId host_id) {
  return std::make_unique<QorAIWalletProviderDelegateImpl>(web_contents,
                                                           host_id);
}

}  // namespace

QorAIWalletTabHelper::QorAIWalletTabHelper(content::WebContents* web_contents)
    : content::WebContentsUserData<QorAIWalletTabHelper>(*web_contents) {}

QorAIWalletTabHelper::~QorAIWalletTabHelper() {
#if !BUILDFLAG(IS_ANDROID)
  if (IsShowingBubble()) {
    CloseBubble();
  }
#endif  // !BUILDFLAG(IS_ANDROID)
}

// static
void QorAIWalletTabHelper::BindEthereumProvider(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<mojom::EthereumProvider> receiver) {
  auto* qorai_wallet_service = QorAIWalletServiceFactory::GetServiceForContext(
      frame_host->GetBrowserContext());
  if (!qorai_wallet_service) {
    return;
  }
  auto* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(
          frame_host->GetBrowserContext());
  if (!host_content_settings_map) {
    return;
  }

  content::WebContents* web_contents =
      content::WebContents::FromRenderFrameHost(frame_host);

  auto* prefs = user_prefs::UserPrefs::Get(web_contents->GetBrowserContext());
  if (!prefs) {
    return;
  }

  auto* tab_helper = QorAIWalletTabHelper::FromWebContents(web_contents);
  if (!tab_helper) {
    return;
  }
  tab_helper->ethereum_provider_receivers_.Add(
      std::make_unique<EthereumProviderImpl>(
          host_content_settings_map, qorai_wallet_service,
          std::make_unique<QorAIWalletProviderDelegateImpl>(
              web_contents, frame_host->GetGlobalId()),
          prefs),
      std::move(receiver));
}

// static
void QorAIWalletTabHelper::BindSolanaProvider(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<mojom::SolanaProvider> receiver) {
  auto* qorai_wallet_service = QorAIWalletServiceFactory::GetServiceForContext(
      frame_host->GetBrowserContext());
  if (!qorai_wallet_service) {
    return;
  }
  auto* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(
          frame_host->GetBrowserContext());
  if (!host_content_settings_map) {
    return;
  }
  content::WebContents* web_contents =
      content::WebContents::FromRenderFrameHost(frame_host);

  auto* tab_helper = QorAIWalletTabHelper::FromWebContents(web_contents);
  if (!tab_helper) {
    return;
  }

  tab_helper->solana_provider_receivers_.Add(
      std::make_unique<SolanaProviderImpl>(
          *host_content_settings_map, qorai_wallet_service,
          std::make_unique<QorAIWalletProviderDelegateImpl>(
              web_contents, frame_host->GetGlobalId())),
      std::move(receiver));
}

// static
void QorAIWalletTabHelper::BindCardanoProvider(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<mojom::CardanoProvider> receiver) {
  if (!IsCardanoDAppSupportEnabled()) {
    return;
  }
  auto* qorai_wallet_service = QorAIWalletServiceFactory::GetServiceForContext(
      frame_host->GetBrowserContext());
  if (!qorai_wallet_service) {
    return;
  }
  auto* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(
          frame_host->GetBrowserContext());
  if (!host_content_settings_map) {
    return;
  }
  content::WebContents* web_contents =
      content::WebContents::FromRenderFrameHost(frame_host);

  auto* tab_helper = QorAIWalletTabHelper::FromWebContents(web_contents);
  if (!tab_helper) {
    return;
  }

  tab_helper->cardano_provider_receivers_.Add(
      std::make_unique<CardanoProviderImpl>(
          *qorai_wallet_service,
          base::BindRepeating(&CreateDelegate, web_contents,
                              frame_host->GetGlobalId())),
      std::move(receiver));
}

void QorAIWalletTabHelper::AddSolanaConnectedAccount(
    const content::GlobalRenderFrameHostId& id,
    const std::string& account) {
  solana_connected_accounts_[id].insert(account);
}

void QorAIWalletTabHelper::RemoveSolanaConnectedAccount(
    const content::GlobalRenderFrameHostId& id,
    const std::string& account) {
  auto it = solana_connected_accounts_.find(id);
  if (it == solana_connected_accounts_.end()) {
    return;
  }
  it->second.erase(account);
}

bool QorAIWalletTabHelper::IsSolanaAccountConnected(
    const content::GlobalRenderFrameHostId& id,
    const std::string& account) {
  auto it = solana_connected_accounts_.find(id);
  return it == solana_connected_accounts_.end() ? false
                                                : it->second.contains(account);
}

void QorAIWalletTabHelper::ClearSolanaConnectedAccounts(
    const content::GlobalRenderFrameHostId& id) {
  solana_connected_accounts_.erase(id);
}

#if !BUILDFLAG(IS_ANDROID)
void QorAIWalletTabHelper::SetCloseOnDeactivate(bool close) {
  if (wallet_bubble_manager_delegate_) {
    wallet_bubble_manager_delegate_->CloseOnDeactivate(close);
  }
  close_on_deactivate_for_testing_ = close;
}

void QorAIWalletTabHelper::ShowBubble() {
  if (skip_delegate_for_testing_) {
    is_showing_bubble_for_testing_ = true;
    return;
  }
  auto bubble_url = GetBubbleURL();
  if (!bubble_url.is_valid()) {
    return;
  }
  wallet_bubble_manager_delegate_ =
      WalletBubbleManagerDelegate::MaybeCreate(&GetWebContents(), bubble_url);
  if (!wallet_bubble_manager_delegate_) {
    return;
  }
  wallet_bubble_manager_delegate_->ShowBubble();
  if (show_bubble_callback_for_testing_) {
    std::move(show_bubble_callback_for_testing_).Run();
  }
}

void QorAIWalletTabHelper::ShowApproveWalletBubble() {
  // If the Wallet page is open, then it will try to open the UI.
  // But the user may have already had the panel UI opened.
  // We want to avoid a hiding / showing of the panel in that case.
  if (IsShowingBubble()) {
    return;
  }
  wallet_bubble_manager_delegate_ = WalletBubbleManagerDelegate::MaybeCreate(
      &GetWebContents(), GetApproveBubbleURL());
  if (!wallet_bubble_manager_delegate_) {
    return;
  }
  wallet_bubble_manager_delegate_->ShowBubble();
}

void QorAIWalletTabHelper::CloseBubble() {
  if (skip_delegate_for_testing_) {
    is_showing_bubble_for_testing_ = false;
    return;
  }
  if (wallet_bubble_manager_delegate_) {
    wallet_bubble_manager_delegate_->CloseBubble();
  }
}

bool QorAIWalletTabHelper::IsShowingBubble() {
  if (skip_delegate_for_testing_) {
    return is_showing_bubble_for_testing_;
  }
  return wallet_bubble_manager_delegate_ &&
         wallet_bubble_manager_delegate_->IsShowingBubble();
}

bool QorAIWalletTabHelper::IsBubbleClosedForTesting() {
  return wallet_bubble_manager_delegate_ &&
         wallet_bubble_manager_delegate_->IsBubbleClosedForTesting();
}

GURL QorAIWalletTabHelper::GetBubbleURL() {
  auto* manager =
      permissions::PermissionRequestManager::FromWebContents(&GetWebContents());
  if (!manager) {
    return GURL();
  }

  GURL webui_url = GURL(kQorAIUIWalletPanelURL);

  // General panel UI if no pending ethereum permission request.
  // Only check the first entry because it will not be grouped with other
  // types.
  if (manager->Requests().empty() ||
      (manager->Requests()[0]->request_type() !=
           permissions::RequestType::kQorAIEthereum &&
       manager->Requests()[0]->request_type() !=
           permissions::RequestType::kQorAISolana &&
       manager->Requests()[0]->request_type() !=
           permissions::RequestType::kQorAICardano)) {
    return webui_url;
  }

  // Handle ConnectWithSite (ethereum permission) request.
  std::vector<std::string> accounts;
  url::Origin requesting_origin;
  for (const auto& request : manager->Requests()) {
    std::string account;
    if (!ParseRequestingOriginFromSubRequest(
            request->request_type(),
            url::Origin::Create(request->requesting_origin()),
            &requesting_origin, &account)) {
      continue;
    }
    accounts.push_back(account);
  }
  DCHECK(!accounts.empty());

  webui_url =
      GetConnectWithSiteWebUIURL(webui_url, accounts, requesting_origin);
  DCHECK(webui_url.is_valid());

  return webui_url;
}

content::WebContents* QorAIWalletTabHelper::GetBubbleWebContentsForTesting() {
  return wallet_bubble_manager_delegate_->GetWebContentsForTesting();
}

const std::vector<int32_t>& QorAIWalletTabHelper::GetPopupIdsForTesting() {
  return wallet_bubble_manager_delegate_->GetPopupIdsForTesting();
}

GURL QorAIWalletTabHelper::GetApproveBubbleURL() {
  GURL webui_url = GURL(kQorAIUIWalletPanelURL);
  GURL::Replacements replacements;
  const std::string ref = "approveTransaction";
  replacements.SetRefStr(ref);
  return webui_url.ReplaceComponents(replacements);
}

#endif  // !BUILDFLAG(IS_ANDROID)

WEB_CONTENTS_USER_DATA_KEY_IMPL(QorAIWalletTabHelper);

}  // namespace qorai_wallet
