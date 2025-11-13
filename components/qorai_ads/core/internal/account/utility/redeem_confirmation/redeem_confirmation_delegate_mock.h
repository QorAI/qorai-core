/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REDEEM_CONFIRMATION_DELEGATE_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REDEEM_CONFIRMATION_DELEGATE_MOCK_H_

#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/redeem_confirmation_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class RedeemConfirmationDelegateMock : public RedeemConfirmationDelegate {
 public:
  RedeemConfirmationDelegateMock();

  RedeemConfirmationDelegateMock(const RedeemConfirmationDelegateMock&) =
      delete;
  RedeemConfirmationDelegateMock& operator=(
      const RedeemConfirmationDelegateMock&) = delete;

  ~RedeemConfirmationDelegateMock() override;

  MOCK_METHOD(void, OnDidRedeemConfirmation, (const ConfirmationInfo&));
  MOCK_METHOD(void,
              OnFailedToRedeemConfirmation,
              (const ConfirmationInfo&, bool));
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REDEEM_CONFIRMATION_DELEGATE_MOCK_H_
