/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_PERMISSION_BUBBLE_QORAI_WALLET_PERMISSION_PROMPT_IMPL_H_
#define QORAI_BROWSER_UI_VIEWS_PERMISSION_BUBBLE_QORAI_WALLET_PERMISSION_PROMPT_IMPL_H_

#include <optional>
#include <vector>

#include "base/memory/raw_ptr.h"
#include "base/time/time.h"
#include "components/permissions/permission_prompt.h"

class Browser;

class QoraiWalletPermissionPromptImpl : public permissions::PermissionPrompt {
 public:
  QoraiWalletPermissionPromptImpl(Browser* browser,
                                  content::WebContents* web_contents,
                                  Delegate& delegate);
  ~QoraiWalletPermissionPromptImpl() override;

  QoraiWalletPermissionPromptImpl(const QoraiWalletPermissionPromptImpl&) =
      delete;
  QoraiWalletPermissionPromptImpl& operator=(
      const QoraiWalletPermissionPromptImpl&) = delete;

  // permissions::PermissionPrompt:
  bool UpdateAnchor() override;
  TabSwitchingBehavior GetTabSwitchingBehavior() override;
  permissions::PermissionPromptDisposition GetPromptDisposition()
      const override;
  bool IsAskPrompt() const override;
  std::optional<gfx::Rect> GetViewBoundsInScreen() const override;
  bool ShouldFinalizeRequestAfterDecided() const override;
  std::vector<permissions::ElementAnchoredBubbleVariant> GetPromptVariants()
      const override;
  std::optional<permissions::feature_params::PermissionElementPromptPosition>
  GetPromptPosition() const override;

 private:
  void ShowBubble();

  const raw_ptr<content::WebContents> web_contents_ = nullptr;
  raw_ref<permissions::PermissionPrompt::Delegate> delegate_;
  base::TimeTicks permission_requested_time_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_PERMISSION_BUBBLE_QORAI_WALLET_PERMISSION_PROMPT_IMPL_H_
