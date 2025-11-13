/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_KEYRING_SERVICE_MIGRATIONS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_KEYRING_SERVICE_MIGRATIONS_H_

#include "components/prefs/pref_service.h"

namespace qorai_wallet {

void MigrateDerivedAccountIndex(PrefService* profile_prefs);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_KEYRING_SERVICE_MIGRATIONS_H_
