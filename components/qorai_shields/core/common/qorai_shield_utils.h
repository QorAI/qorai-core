// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CORE_COMMON_QORAI_SHIELD_UTILS_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CORE_COMMON_QORAI_SHIELD_UTILS_H_

#include <map>

#include "qorai/components/qorai_shields/core/common/shields_settings.mojom-data-view.h"
#include "components/content_settings/core/common/content_settings.h"

class GURL;

namespace qorai_shields {

struct ShieldsSettingCounts {
  int allow;
  int standard;
  int aggressive;
};

ContentSetting GetQoraiFPContentSettingFromRules(
    const ContentSettingsForOneType& fp_rules,
    const GURL& primary_url);

ContentSetting GetQoraiWebcompatContentSettingFromRules(
    const std::map<ContentSettingsType, ContentSettingsForOneType>&
        webcompat_rules,
    const GURL& primary_url,
    const ContentSettingsType content_settings_type);

ShieldsSettingCounts GetSettingCountFromRules(
    const ContentSettingsForOneType& fp_rules);

ShieldsSettingCounts GetSettingCountFromCosmeticFilteringRules(
    const ContentSettingsForOneType& fp_rules);

mojom::ContentSettingSource ConvertSettingsSource(
    const content_settings::SettingSource source);

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CORE_COMMON_QORAI_SHIELD_UTILS_H_
