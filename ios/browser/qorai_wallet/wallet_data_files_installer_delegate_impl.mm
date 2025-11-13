/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/qorai_wallet/wallet_data_files_installer_delegate_impl.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"

namespace qorai_wallet {

component_updater::ComponentUpdateService*
WalletDataFilesInstallerDelegateImpl::GetComponentUpdater() {
  return GetApplicationContext()->GetComponentUpdateService();
}

}  // namespace qorai_wallet
