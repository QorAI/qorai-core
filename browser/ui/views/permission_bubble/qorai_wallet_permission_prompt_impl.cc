/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/permission_bubble/qorai_wallet_permission_prompt_impl.h"

#include <optional>

#include "base/check.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_tab_helper.h"
#include "components/permissions/permission_uma_util.h"

QoraiWalletPermissionPromptImpl::QoraiWalletPermissionPromptImpl(
    Browser* browser,
    content::WebContents* web_contents,
    Delegate& delegate)
    : web_contents_(web_contents),
      delegate_(delegate),
      permission_requested_time_(base::TimeTicks::Now()) {
  DCHECK(web_contents_);
  ShowBubble();
}

QoraiWalletPermissionPromptImpl::~QoraiWalletPermissionPromptImpl() {
  qorai_wallet::QoraiWalletTabHelper::FromWebContents(web_contents_)
      ->CloseBubble();
}

void QoraiWalletPermissionPromptImpl::ShowBubble() {
  qorai_wallet::QoraiWalletTabHelper::FromWebContents(web_contents_)
      ->ShowBubble();
}

bool QoraiWalletPermissionPromptImpl::UpdateAnchor() {
  // Don't recreate the view for every BrowserView::Layout() which would cause
  // QoraiWalletPermissionPromptImpl being destoryed which leads to bubble
  // dismissed unintentionally.
  return true;
}

permissions::PermissionPrompt::TabSwitchingBehavior
QoraiWalletPermissionPromptImpl::GetTabSwitchingBehavior() {
  return permissions::PermissionPrompt::TabSwitchingBehavior::
      kDestroyPromptButKeepRequestPending;
}

permissions::PermissionPromptDisposition
QoraiWalletPermissionPromptImpl::GetPromptDisposition() const {
  return permissions::PermissionPromptDisposition::ANCHORED_BUBBLE;
}

bool QoraiWalletPermissionPromptImpl::IsAskPrompt() const {
  return true;
}

std::optional<gfx::Rect>
QoraiWalletPermissionPromptImpl::GetViewBoundsInScreen() const {
  return std::nullopt;
}

bool QoraiWalletPermissionPromptImpl::ShouldFinalizeRequestAfterDecided()
    const {
  return true;
}

std::vector<permissions::ElementAnchoredBubbleVariant>
QoraiWalletPermissionPromptImpl::GetPromptVariants() const {
  return {};
}

std::optional<permissions::feature_params::PermissionElementPromptPosition>
QoraiWalletPermissionPromptImpl::GetPromptPosition() const {
  return std::nullopt;
}
