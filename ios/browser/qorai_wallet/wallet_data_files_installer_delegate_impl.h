/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_QORAI_WALLET_WALLET_DATA_FILES_INSTALLER_DELEGATE_IMPL_H_
#define QORAI_IOS_BROWSER_QORAI_WALLET_WALLET_DATA_FILES_INSTALLER_DELEGATE_IMPL_H_

#include "qorai/components/qorai_wallet/browser/wallet_data_files_installer_delegate.h"

namespace qorai_wallet {

class WalletDataFilesInstallerDelegateImpl
    : public WalletDataFilesInstallerDelegate {
 public:
  WalletDataFilesInstallerDelegateImpl() = default;
  ~WalletDataFilesInstallerDelegateImpl() override = default;
  component_updater::ComponentUpdateService* GetComponentUpdater() override;
};

}  // namespace qorai_wallet

#endif  // QORAI_IOS_BROWSER_QORAI_WALLET_WALLET_DATA_FILES_INSTALLER_DELEGATE_IMPL_H_
