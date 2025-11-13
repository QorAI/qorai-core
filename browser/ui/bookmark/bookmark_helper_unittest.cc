/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/bookmark/bookmark_helper.h"

#include "qorai/browser/ui/bookmark/bookmark_prefs_service_factory.h"
#include "components/bookmarks/browser/bookmark_utils.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"

TEST(BookmarkStateUnittest, SetState) {
  sync_preferences::TestingPrefServiceSyncable service;
  BookmarkPrefsServiceFactory::GetInstance()->RegisterProfilePrefs(
      service.registry());
  bookmarks::RegisterProfilePrefs(service.registry());
  // By default only NTP is enabled.
  EXPECT_EQ(qorai::GetBookmarkBarState(&service),
            qorai::BookmarkBarState::kNtp);

  // Show bookmark bar always.
  qorai::SetBookmarkState(qorai::BookmarkBarState::kAlways, &service);
  EXPECT_EQ(qorai::GetBookmarkBarState(&service),
            qorai::BookmarkBarState::kAlways);

  // Never show bookmark bar.
  qorai::SetBookmarkState(qorai::BookmarkBarState::kNever, &service);
  EXPECT_EQ(qorai::GetBookmarkBarState(&service),
            qorai::BookmarkBarState::kNever);
}
