/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_CONTEXT_UTILS_H_
#define QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_CONTEXT_UTILS_H_

namespace content {
class BrowserContext;
}

namespace qorai_wallet {

bool IsAllowedForContext(content::BrowserContext* context);

}  // namespace qorai_wallet

#endif  // QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_CONTEXT_UTILS_H_
