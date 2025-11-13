/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/scoped_txs_update.h"

#include "qorai/components/qorai_wallet/browser/tx_storage_delegate.h"

namespace qorai_wallet {

ScopedTxsUpdate::ScopedTxsUpdate(TxStorageDelegate& delegate)
    : delegate_(delegate) {}

ScopedTxsUpdate::~ScopedTxsUpdate() {
  delegate_->ScheduleWrite();
}

base::Value::Dict& ScopedTxsUpdate::Get() {
  return delegate_->GetTxs();
}

}  // namespace qorai_wallet
