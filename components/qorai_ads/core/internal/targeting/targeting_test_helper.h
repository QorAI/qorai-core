/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_TARGETING_TEST_HELPER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_TARGETING_TEST_HELPER_H_

#include "base/memory/raw_ref.h"
#include "base/test/task_environment.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_test_helper.h"
#include "qorai/components/qorai_ads/core/internal/targeting/contextual/text_classification/text_classification_test_helper.h"

namespace qorai_ads {

struct IntentUserModelInfo;
struct InterestUserModelInfo;
struct LatentInterestUserModelInfo;
struct UserModelInfo;

namespace test {

class TargetingHelper final {
 public:
  explicit TargetingHelper(base::test::TaskEnvironment& task_environment);

  TargetingHelper(const TargetingHelper&) = delete;
  TargetingHelper& operator=(const TargetingHelper&) = delete;

  ~TargetingHelper();

  void Mock();
  static UserModelInfo Expectation();

  void MockIntent();
  static IntentUserModelInfo IntentExpectation();

  void MockLatentInterest();
  static LatentInterestUserModelInfo LatentInterestExpectation();

  void MockInterest();
  static InterestUserModelInfo InterestExpectation();

 private:
  PurchaseIntentHelper purchase_intent_;
  TextClassificationHelper text_classification_;

  const raw_ref<base::test::TaskEnvironment> task_environment_;
};

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_TARGETING_TEST_HELPER_H_
