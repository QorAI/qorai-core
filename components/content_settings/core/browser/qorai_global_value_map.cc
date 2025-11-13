/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/content_settings/core/browser/qorai_global_value_map.h"

#include <memory>

#include "qorai/components/content_settings/core/browser/qorai_content_settings_utils.h"
#include "components/content_settings/core/browser/content_settings_rule.h"
#include "components/content_settings/core/common/content_settings.h"

namespace content_settings {

QoraiGlobalValueMap::QoraiGlobalValueMap() = default;

QoraiGlobalValueMap::~QoraiGlobalValueMap() = default;

std::unique_ptr<RuleIterator> QoraiGlobalValueMap::GetRuleIterator(
    ContentSettingsType content_type) const {
  if (content_settings::IsShieldsContentSettingsType(content_type)) {
    return nullptr;
  }
  return GlobalValueMap::GetRuleIterator(content_type);
}

void QoraiGlobalValueMap::SetPermissionSetting(
    ContentSettingsType content_type,
    std::optional<PermissionSetting> setting) {
  return GlobalValueMap::SetPermissionSetting(content_type, setting);
}

std::optional<PermissionSetting> QoraiGlobalValueMap::GetPermissionSetting(
    ContentSettingsType content_type) const {
  return GlobalValueMap::GetPermissionSetting(content_type);
}

}  // namespace content_settings
