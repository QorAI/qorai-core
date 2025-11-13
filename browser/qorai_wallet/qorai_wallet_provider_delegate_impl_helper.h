/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_PROVIDER_DELEGATE_IMPL_HELPER_H_
#define QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_PROVIDER_DELEGATE_IMPL_HELPER_H_

#include "base/functional/callback.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom-forward.h"
#include "build/build_config.h"

namespace content {
class WebContents;
}

// UI helper functions which are platform-dependent.
namespace qorai_wallet {

// Show wallet panel, which handles permission UI, sign message confirmation,
// ...etc.
void ShowPanel(content::WebContents* web_contents);

// Show native QorAI Wallet backup UI - Used only by Android.
void ShowWalletBackup();

// Show native QorAI Wallet unlock screen - Used only by Android.
void UnlockWallet();

// Show wallet onboarding page.
void ShowWalletOnboarding(content::WebContents* web_contents);

// Show account creation page for keyring id
void ShowAccountCreation(content::WebContents* web_contents,
                         qorai_wallet::mojom::CoinType coin_type);

// Triggers when any kind interaction from a DApp is detected
void WalletInteractionDetected(content::WebContents* web_contents);

// Check are web3 notifications allowed or not. Used on Android to
// show or not a permissions prompt dialog
bool IsWeb3NotificationAllowed();

void SetCallbackForNewSetupNeededForTesting(base::OnceCallback<void()>);

void SetCallbackForAccountCreationForTesting(
    base::OnceCallback<void(std::string_view)>);

}  // namespace qorai_wallet

#endif  // QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_PROVIDER_DELEGATE_IMPL_HELPER_H_
