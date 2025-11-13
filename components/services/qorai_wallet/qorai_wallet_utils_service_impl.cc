/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/services/qorai_wallet/qorai_wallet_utils_service_impl.h"

#include <memory>
#include <utility>

#include "qorai/components/services/qorai_wallet/zcash/zcash_decoder.h"

namespace qorai_wallet {

QoraiWalletUtilsServiceImpl::QoraiWalletUtilsServiceImpl(
    mojo::PendingReceiver<mojom::QoraiWalletUtilsService> receiver)
    : receiver_(this, std::move(receiver)) {}

QoraiWalletUtilsServiceImpl::~QoraiWalletUtilsServiceImpl() = default;

void QoraiWalletUtilsServiceImpl::CreateZCashDecoderService(
    mojo::PendingAssociatedReceiver<zcash::mojom::ZCashDecoder>
        zcash_decoder_receiver) {
  if (!instance_) {
    instance_ = mojo::MakeSelfOwnedAssociatedReceiver(
        std::make_unique<ZCashDecoder>(), std::move(zcash_decoder_receiver));
  }
}

}  // namespace qorai_wallet
