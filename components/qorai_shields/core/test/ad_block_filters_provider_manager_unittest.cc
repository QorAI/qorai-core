// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_shields/core/browser/ad_block_filters_provider_manager.h"
#include "testing/gtest/include/gtest/gtest.h"

#include "qorai/components/qorai_shields/content/test/test_filters_provider.h"

class FiltersProviderManagerTestObserver
    : public qorai_shields::AdBlockFiltersProvider::Observer {
 public:
  FiltersProviderManagerTestObserver() = default;

  // AdBlockFiltersProvider::Observer
  void OnChanged(bool is_default_engine) override { changed_count += 1; }

  int changed_count = 0;
};

TEST(AdBlockFiltersProviderManagerTest, WaitUntilInitialized) {
  FiltersProviderManagerTestObserver test_observer;
  qorai_shields::AdBlockFiltersProviderManager::GetInstance()->AddObserver(
      &test_observer);

  qorai_shields::TestFiltersProvider provider1("", true, 0, false);
  qorai_shields::TestFiltersProvider provider2("", true, 0, false);
  qorai_shields::TestFiltersProvider provider3("", true, 0, false);

  provider1.Initialize();
  EXPECT_EQ(test_observer.changed_count, 0);
  provider2.Initialize();
  EXPECT_EQ(test_observer.changed_count, 0);
  provider3.Initialize();
  EXPECT_EQ(test_observer.changed_count, 1);
}
