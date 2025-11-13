/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_OBSERVER_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_OBSERVER_MOCK_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/account/account_observer.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class AccountObserverMock : public AccountObserver {
 public:
  AccountObserverMock();

  AccountObserverMock(const AccountObserverMock&) = delete;
  AccountObserverMock& operator=(const AccountObserverMock&) = delete;

  ~AccountObserverMock() override;

  MOCK_METHOD(void, OnDidInitializeWallet, (const WalletInfo&));

  MOCK_METHOD(void, OnFailedToInitializeWallet, ());

  MOCK_METHOD(void, OnDidProcessDeposit, (const TransactionInfo&));

  MOCK_METHOD(void,
              OnFailedToProcessDeposit,
              (const std::string&, mojom::AdType, mojom::ConfirmationType));
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_OBSERVER_MOCK_H_
