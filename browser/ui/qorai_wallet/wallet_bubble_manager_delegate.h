/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_WALLET_WALLET_BUBBLE_MANAGER_DELEGATE_H_
#define QORAI_BROWSER_UI_QORAI_WALLET_WALLET_BUBBLE_MANAGER_DELEGATE_H_

#include <stdint.h>

#include <memory>
#include <vector>

class GURL;

namespace content {
class WebContents;
}  // namespace content

namespace qorai_wallet {

class WalletBubbleManagerDelegate {
 public:
  static std::unique_ptr<WalletBubbleManagerDelegate> MaybeCreate(
      content::WebContents* web_contents,
      const GURL& webui_url);

  WalletBubbleManagerDelegate(const WalletBubbleManagerDelegate&) = delete;
  WalletBubbleManagerDelegate& operator=(const WalletBubbleManagerDelegate&) =
      delete;

  virtual ~WalletBubbleManagerDelegate() = default;

  virtual void ShowBubble() = 0;
  virtual void CloseBubble() = 0;
  virtual bool IsShowingBubble() = 0;
  virtual bool IsBubbleClosedForTesting() = 0;
  virtual content::WebContents* GetWebContentsForTesting() = 0;
  virtual const std::vector<int32_t>& GetPopupIdsForTesting() = 0;
  virtual void CloseOnDeactivate(bool close) = 0;

 protected:
  WalletBubbleManagerDelegate() = default;
};

}  // namespace qorai_wallet

#endif  // QORAI_BROWSER_UI_QORAI_WALLET_WALLET_BUBBLE_MANAGER_DELEGATE_H_
