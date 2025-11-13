/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/media_permission_rule.h"

#include <optional>

#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"
#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/permission_rule_feature.h"
#include "qorai/components/qorai_ads/core/internal/tabs/tab_manager.h"

namespace qorai_ads {

bool HasMediaPermission() {
  if (!kShouldOnlyServeAdsIfMediaIsNotPlaying.Get()) {
    return true;
  }

  std::optional<TabInfo> tab = TabManager::GetInstance().MaybeGetVisible();
  if (!tab) {
    return true;
  }

  if (!TabManager::GetInstance().IsPlayingMedia(tab->id)) {
    return true;
  }

  BLOG(2, "Media is playing");
  return false;
}

}  // namespace qorai_ads
