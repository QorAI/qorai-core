/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <memory>

#include "qorai/components/qorai_wallet/browser/qorai_wallet_service_delegate.h"
#include "build/build_config.h"
#include "content/public/browser/browser_context.h"

#if BUILDFLAG(IS_ANDROID)
#include "qorai/browser/qorai_wallet/qorai_wallet_service_delegate_impl_android.h"
#else
#include "qorai/browser/qorai_wallet/qorai_wallet_service_delegate_impl.h"
#endif

namespace qorai_wallet {

// static
std::unique_ptr<QorAIWalletServiceDelegate> QorAIWalletServiceDelegate::Create(
    content::BrowserContext* browser_context) {
  return std::make_unique<QorAIWalletServiceDelegateImpl>(browser_context);
}

}  // namespace qorai_wallet
