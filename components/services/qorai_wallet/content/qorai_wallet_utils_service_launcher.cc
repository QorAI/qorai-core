/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/services/qorai_wallet/content/qorai_wallet_utils_service_launcher.h"

#include <utility>

#include "components/grit/qorai_components_strings.h"
#include "content/public/browser/service_process_host.h"

namespace qorai_wallet {

void LaunchQoraiWalletUtilsService(
    mojo::PendingReceiver<mojom::QoraiWalletUtilsService> receiver) {
  content::ServiceProcessHost::Launch(
      std::move(receiver),
      content::ServiceProcessHost::Options()
          .WithDisplayName(IDS_QORAI_WALLET_UTILITY_PROCESS_WALLET_UTILS_NAME)
          .Pass());
}

}  // namespace qorai_wallet
