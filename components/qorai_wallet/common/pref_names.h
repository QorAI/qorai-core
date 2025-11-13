/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_COMMON_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_WALLET_COMMON_PREF_NAMES_H_

namespace qorai_wallet {
namespace prefs {

// Used to enable/disable Qorai Wallet via a policy.
inline constexpr char kDisabledByPolicy[] = "qorai.wallet.disabled_by_policy";

}  // namespace prefs
}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_COMMON_PREF_NAMES_H_
