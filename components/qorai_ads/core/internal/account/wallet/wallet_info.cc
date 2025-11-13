/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/wallet/wallet_info.h"

namespace qorai_ads {

bool WalletInfo::IsValid() const {
  return !payment_id.empty() && !public_key_base64.empty() &&
         !secret_key_base64.empty();
}

}  // namespace qorai_ads
