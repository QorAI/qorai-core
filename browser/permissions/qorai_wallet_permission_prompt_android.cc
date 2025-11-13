/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/permissions/qorai_wallet_permission_prompt_android.h"

#include <utility>

#include "qorai/browser/permissions/qorai_dapp_permission_prompt_dialog_controller_android.h"
#include "qorai/components/qorai_wallet/browser/permission_utils.h"
#include "qorai/components/permissions/contexts/qorai_wallet_permission_context.h"
#include "components/permissions/android/permission_prompt/permission_prompt_android.h"
#include "content/public/browser/web_contents.h"

QoraiWalletPermissionPrompt::QoraiWalletPermissionPrompt(
    content::WebContents* web_contents,
    std::unique_ptr<Delegate> delegate,
    qorai_wallet::mojom::CoinType coin_type)
    : web_contents_(web_contents), delegate_(std::move(delegate)) {
  dialog_controller_ =
      std::make_unique<QoraiDappPermissionPromptDialogController>(
          this, web_contents_, coin_type);
  dialog_controller_->ShowDialog();
}

QoraiWalletPermissionPrompt::~QoraiWalletPermissionPrompt() {}

void QoraiWalletPermissionPrompt::ConnectToSite(
    const std::vector<std::string>& accounts,
    int permission_lifetime_option) {
  has_interacted_with_dialog_ = true;
  dialog_controller_.reset();
  // TODO(SergeyZhukovsky): Use the real option that the user chooses, using
  // `kForever` here is for landing new API changes separately.
  permissions::QoraiWalletPermissionContext::AcceptOrCancel(
      accounts, qorai_wallet::mojom::PermissionLifetimeOption::kForever,
      web_contents_);
}

void QoraiWalletPermissionPrompt::CancelConnectToSite() {
  has_interacted_with_dialog_ = true;
  dialog_controller_.reset();
  permissions::QoraiWalletPermissionContext::Cancel(web_contents_);
}

void QoraiWalletPermissionPrompt::OnDialogDismissed() {
  if (!dialog_controller_) {
    // Dismissed by clicking on dialog buttons.
    return;
  }
  dialog_controller_.reset();
  // If |has_interacted_with_dialog_| is true, |ConnectToSite| or
  // |CancelConnectToSite| should be recorded instead.
  if (!has_interacted_with_dialog_) {
    permissions::QoraiWalletPermissionContext::Cancel(web_contents_);
  }
}

void QoraiWalletPermissionPrompt::Delegate::Closing() {
  if (!permission_prompt_) {
    return;
  }
  permission_prompt_->Closing();
}

QoraiWalletPermissionPrompt::Delegate::~Delegate() {
  Closing();
}

QoraiWalletPermissionPrompt::Delegate::Delegate() {}

QoraiWalletPermissionPrompt::Delegate::Delegate(
    const base::WeakPtr<permissions::PermissionPromptAndroid>&
        permission_prompt)
    : permission_prompt_(permission_prompt) {}
