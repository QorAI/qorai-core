/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_QORAI_GLOBAL_VALUE_MAP_H_
#define QORAI_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_QORAI_GLOBAL_VALUE_MAP_H_

#include <memory>

#include "components/content_settings/core/browser/content_settings_global_value_map.h"
#include "components/content_settings/core/browser/content_settings_provider.h"
#include "components/content_settings/core/common/content_settings_types.h"

namespace content_settings {

class RuleIterator;

class QoraiGlobalValueMap : public GlobalValueMap {
 public:
  QoraiGlobalValueMap();
  QoraiGlobalValueMap(const QoraiGlobalValueMap&) = delete;
  QoraiGlobalValueMap& operator=(const QoraiGlobalValueMap&) = delete;
  ~QoraiGlobalValueMap();

  // Returns nullptr to indicate the RuleIterator is empty.
  std::unique_ptr<RuleIterator> GetRuleIterator(
      ContentSettingsType content_type) const;
  void SetPermissionSetting(ContentSettingsType content_type,
                            std::optional<PermissionSetting> setting);
  std::optional<PermissionSetting> GetPermissionSetting(
      ContentSettingsType content_type) const;
};

}  // namespace content_settings

#endif  // QORAI_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_QORAI_GLOBAL_VALUE_MAP_H_
