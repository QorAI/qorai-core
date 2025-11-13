/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_DELEGATE_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_DELEGATE_MOCK_H_

#include "qorai/components/qorai_ads/core/internal/account/confirmations/confirmations_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class ConfirmationsDelegateMock : public ConfirmationDelegate {
 public:
  ConfirmationsDelegateMock();

  ConfirmationsDelegateMock(const ConfirmationsDelegateMock&) = delete;
  ConfirmationsDelegateMock& operator=(const ConfirmationsDelegateMock&) =
      delete;

  ~ConfirmationsDelegateMock() override;

  MOCK_METHOD(void, OnDidConfirm, (const ConfirmationInfo&));
  MOCK_METHOD(void, OnFailedToConfirm, (const ConfirmationInfo&));
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_DELEGATE_MOCK_H_
