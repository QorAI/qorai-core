/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_NEW_TAB_PAGE_AD_SERVING_DELEGATE_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_NEW_TAB_PAGE_AD_SERVING_DELEGATE_MOCK_H_

#include "qorai/components/qorai_ads/core/internal/serving/new_tab_page_ad_serving_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class NewTabPageAdServingDelegateMock : public NewTabPageAdServingDelegate {
 public:
  NewTabPageAdServingDelegateMock();

  NewTabPageAdServingDelegateMock(const NewTabPageAdServingDelegateMock&) =
      delete;
  NewTabPageAdServingDelegateMock& operator=(
      const NewTabPageAdServingDelegateMock&) = delete;

  ~NewTabPageAdServingDelegateMock() override;

  MOCK_METHOD(void, OnOpportunityAroseToServeNewTabPageAd, ());

  MOCK_METHOD(void, OnDidServeNewTabPageAd, (const NewTabPageAdInfo&));
  MOCK_METHOD(void, OnFailedToServeNewTabPageAd, ());
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_NEW_TAB_PAGE_AD_SERVING_DELEGATE_MOCK_H_
