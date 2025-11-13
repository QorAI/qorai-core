// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/qorai_wallet/panel_handler/wallet_panel_handler.h"

#include <utility>

#include "base/check.h"
#include "base/functional/callback.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_tab_helper.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/browser/permission_utils.h"
#include "qorai/components/permissions/contexts/qorai_wallet_permission_context.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/web_contents.h"

// It's safe to bind the active webcontents when panel is created because
// the panel will not be shared across tabs.
WalletPanelHandler::WalletPanelHandler(
    mojo::PendingReceiver<qorai_wallet::mojom::PanelHandler> receiver,
    TopChromeWebUIController* webui_controller,
    content::WebContents* active_web_contents,
    PanelCloseOnDeactivationCallback close_on_deactivation)
    : receiver_(this, std::move(receiver)),
      webui_controller_(webui_controller),
      active_web_contents_(active_web_contents),
      close_on_deactivation_(std::move(close_on_deactivation)) {
  DCHECK(active_web_contents_);
}

WalletPanelHandler::~WalletPanelHandler() = default;

void WalletPanelHandler::ShowUI() {
  auto embedder = webui_controller_->embedder();
  if (embedder) {
    embedder->ShowUI();
  }
}

void WalletPanelHandler::CloseUI() {
  auto embedder = webui_controller_->embedder();
  if (embedder) {
    embedder->CloseUI();
  }
}

void WalletPanelHandler::ConnectToSite(
    const std::vector<std::string>& accounts,
    qorai_wallet::mojom::PermissionLifetimeOption option) {
  permissions::QoraiWalletPermissionContext::AcceptOrCancel(
      accounts, option, active_web_contents_);
}

void WalletPanelHandler::CancelConnectToSite() {
  permissions::QoraiWalletPermissionContext::Cancel(active_web_contents_);
}

void WalletPanelHandler::SetCloseOnDeactivate(bool close) {
  if (close_on_deactivation_) {
    close_on_deactivation_.Run(close);
  }
}

void WalletPanelHandler::Focus() {
  webui_controller_->web_ui()->GetWebContents()->Focus();
}

void WalletPanelHandler::IsSolanaAccountConnected(
    const std::string& account,
    IsSolanaAccountConnectedCallback callback) {
  content::RenderFrameHost* rfh = nullptr;
  if (!(rfh = active_web_contents_->GetFocusedFrame())) {
    std::move(callback).Run(false);
    return;
  }

  auto* tab_helper =
      qorai_wallet::QoraiWalletTabHelper::FromWebContents(active_web_contents_);
  if (!tab_helper) {
    std::move(callback).Run(false);
    return;
  }

  std::move(callback).Run(
      tab_helper->IsSolanaAccountConnected(rfh->GetGlobalId(), account));
}

void WalletPanelHandler::RequestPermission(
    qorai_wallet::mojom::AccountIdPtr account_id,
    RequestPermissionCallback callback) {
  content::RenderFrameHost* rfh = nullptr;
  if (!(rfh = active_web_contents_->GetFocusedFrame())) {
    std::move(callback).Run(false);
    return;
  }

  auto request_type =
      qorai_wallet::CoinTypeToPermissionRequestType(account_id->coin);
  auto permission = qorai_wallet::CoinTypeToPermissionType(account_id->coin);
  if (!request_type || !permission) {
    std::move(callback).Run(false);
    return;
  }

  if (permissions::QoraiWalletPermissionContext::HasRequestsInProgress(
          rfh, *request_type)) {
    std::move(callback).Run(false);
    return;
  }

  permissions::QoraiWalletPermissionContext::RequestPermissions(
      *permission, rfh,
      {qorai_wallet::GetAccountPermissionIdentifier(account_id)},
      base::BindOnce(
          [](RequestPermissionCallback cb,
             const std::vector<content::PermissionResult>& responses) {
            if (responses.empty() || responses.size() != 1u) {
              std::move(cb).Run(false);
            } else {
              std::move(cb).Run(true);
            }
          },
          std::move(callback)));
}
