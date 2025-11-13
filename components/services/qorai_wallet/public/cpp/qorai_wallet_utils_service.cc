/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/services/qorai_wallet/public/cpp/qorai_wallet_utils_service.h"

#include <utility>

#include "base/no_destructor.h"
#include "build/build_config.h"

#if BUILDFLAG(IS_IOS)
#include "qorai/components/services/qorai_wallet/public/cpp/qorai_wallet_utils_service_in_process_launcher.h"
#else
#include "qorai/components/services/qorai_wallet/content/qorai_wallet_utils_service_launcher.h"
#endif

namespace qorai_wallet {

QoraiWalletUtilsService::QoraiWalletUtilsService() = default;
QoraiWalletUtilsService::~QoraiWalletUtilsService() = default;

// static
QoraiWalletUtilsService* QoraiWalletUtilsService::GetInstance() {
  static base::NoDestructor<QoraiWalletUtilsService> service;
  return service.get();
}

void QoraiWalletUtilsService::CreateZCashDecoder(
    mojo::PendingAssociatedReceiver<zcash::mojom::ZCashDecoder> receiver) {
  MaybeLaunchService();
  qorai_wallet_utils_service_->CreateZCashDecoderService(std::move(receiver));
}

void QoraiWalletUtilsService::MaybeLaunchService() {
#if BUILDFLAG(IS_IOS)
  LaunchInProcessQoraiWalletUtilsService(
      qorai_wallet_utils_service_.BindNewPipeAndPassReceiver());
  qorai_wallet_utils_service_.reset_on_disconnect();
#else
  LaunchQoraiWalletUtilsService(
      qorai_wallet_utils_service_.BindNewPipeAndPassReceiver());
  qorai_wallet_utils_service_.reset_on_disconnect();
  // 10 minutes is a default wallet lock time
  qorai_wallet_utils_service_.reset_on_idle_timeout(base::Minutes(10));
#endif
}

}  // namespace qorai_wallet
