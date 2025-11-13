/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_PLAYLIST_TEST_PLAYLIST_UNITTEST_BASE_H_
#define QORAI_BROWSER_PLAYLIST_TEST_PLAYLIST_UNITTEST_BASE_H_

#include <memory>

#include "base/test/scoped_feature_list.h"
#include "qorai/components/playlist/core/common/features.h"
#include "components/prefs/testing_pref_service.h"
#include "content/public/test/test_renderer_host.h"

namespace content {
class BrowserContext;
}

namespace playlist {
class PlaylistUnitTestBase : public content::RenderViewHostTestHarness {
 public:
  PlaylistUnitTestBase();
  ~PlaylistUnitTestBase() override;

 protected:
  // testing::Test:
  void SetUp() override;

  // content::RenderViewHostTestHarness:
  std::unique_ptr<content::BrowserContext> CreateBrowserContext() override;

  base::test::ScopedFeatureList feature_list_{features::kPlaylist};
};
}  // namespace playlist

#endif  // QORAI_BROWSER_PLAYLIST_TEST_PLAYLIST_UNITTEST_BASE_H_
