/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_PERMISSIONS_PERMISSION_MANAGER_FACTORY_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_PERMISSIONS_PERMISSION_MANAGER_FACTORY_H_

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace qorai_wallet {
class EthereumProviderImplUnitTest;
class SolanaProviderImplUnitTest;
class CardanoProviderImplUnitTest;
class QoraiWalletServiceUnitTest;
}  // namespace qorai_wallet

namespace permissions {
class QoraiWalletPermissionContextUnitTest;
}

#define BuildServiceInstanceForBrowserContext               \
  BuildServiceInstanceForBrowserContext_ChromiumImpl(       \
      content::BrowserContext* profile) const;              \
  friend qorai_wallet::EthereumProviderImplUnitTest;        \
  friend qorai_wallet::SolanaProviderImplUnitTest;          \
  friend qorai_wallet::CardanoProviderImplUnitTest;         \
  friend qorai_wallet::QoraiWalletServiceUnitTest;          \
  friend permissions::QoraiWalletPermissionContextUnitTest; \
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext

#include <chrome/browser/permissions/permission_manager_factory.h>  // IWYU pragma: export
#undef BuildServiceInstanceForBrowserContext

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_PERMISSIONS_PERMISSION_MANAGER_FACTORY_H_
