// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_shields/core/browser/qorai_shields_settings_service.h"

#include "qorai/components/qorai_shields/core/browser/qorai_shields_p3a.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/qorai_shields/core/common/qorai_shield_utils.h"
#include "qorai/components/content_settings/core/common/content_settings_util.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/prefs/pref_service.h"
#include "url/gurl.h"

namespace qorai_shields {

QoraiShieldsSettingsService::QoraiShieldsSettingsService(
    HostContentSettingsMap& host_content_settings_map,
    PrefService* local_state,
    PrefService* profile_prefs)
    : host_content_settings_map_(host_content_settings_map),
      local_state_(local_state),
      profile_prefs_(profile_prefs) {}

QoraiShieldsSettingsService::~QoraiShieldsSettingsService() = default;

void QoraiShieldsSettingsService::SetQoraiShieldsEnabled(bool is_enabled,
                                                         const GURL& url) {
  qorai_shields::SetQoraiShieldsEnabled(&*host_content_settings_map_,
                                        is_enabled, url, local_state_);
}

bool QoraiShieldsSettingsService::GetQoraiShieldsEnabled(const GURL& url) {
  return qorai_shields::GetQoraiShieldsEnabled(&*host_content_settings_map_,
                                               url);
}

void QoraiShieldsSettingsService::SetDefaultAdBlockMode(
    mojom::AdBlockMode mode) {
  SetAdBlockMode(mode, GURL());
}

mojom::AdBlockMode QoraiShieldsSettingsService::GetDefaultAdBlockMode() {
  return GetAdBlockMode(GURL());
}

void QoraiShieldsSettingsService::SetAdBlockMode(mojom::AdBlockMode mode,
                                                 const GURL& url) {
  ControlType control_type_ad;
  ControlType control_type_cosmetic;

  if (mode == mojom::AdBlockMode::ALLOW) {
    control_type_ad = ControlType::ALLOW;
  } else {
    control_type_ad = ControlType::BLOCK;
  }

  if (mode == mojom::AdBlockMode::AGGRESSIVE) {
    control_type_cosmetic = ControlType::BLOCK;  // aggressive
  } else if (mode == mojom::AdBlockMode::STANDARD) {
    control_type_cosmetic = ControlType::BLOCK_THIRD_PARTY;  // standard
  } else {
    control_type_cosmetic = ControlType::ALLOW;  // allow
  }

  qorai_shields::SetAdControlType(&*host_content_settings_map_, control_type_ad,
                                  url, local_state_);

  qorai_shields::SetCosmeticFilteringControlType(&*host_content_settings_map_,
                                                 control_type_cosmetic, url,
                                                 local_state_, profile_prefs_);
}

mojom::AdBlockMode QoraiShieldsSettingsService::GetAdBlockMode(
    const GURL& url) {
  ControlType control_type_ad =
      qorai_shields::GetAdControlType(&*host_content_settings_map_, url);

  ControlType control_type_cosmetic =
      qorai_shields::GetCosmeticFilteringControlType(
          &*host_content_settings_map_, url);

  if (control_type_ad == ControlType::ALLOW) {
    return mojom::AdBlockMode::ALLOW;
  }

  if (control_type_cosmetic == ControlType::BLOCK) {
    return mojom::AdBlockMode::AGGRESSIVE;
  } else {
    return mojom::AdBlockMode::STANDARD;
  }
}

void QoraiShieldsSettingsService::SetDefaultFingerprintMode(
    mojom::FingerprintMode mode) {
  SetFingerprintMode(mode, GURL());
}

mojom::FingerprintMode
QoraiShieldsSettingsService::GetDefaultFingerprintMode() {
  return GetFingerprintMode(GURL());
}

void QoraiShieldsSettingsService::SetFingerprintMode(
    mojom::FingerprintMode mode,
    const GURL& url) {
#if BUILDFLAG(IS_IOS)
  /// Strict FingerprintMode is not supported on iOS
  CHECK(mode != mojom::FingerprintMode::STRICT_MODE);
#endif

  ControlType control_type;

  if (mode == mojom::FingerprintMode::ALLOW_MODE) {
    control_type = ControlType::ALLOW;
  } else if (mode == mojom::FingerprintMode::STRICT_MODE) {
    control_type = ControlType::BLOCK;
  } else {
    control_type = ControlType::DEFAULT;  // STANDARD_MODE
  }

  qorai_shields::SetFingerprintingControlType(&*host_content_settings_map_,
                                              control_type, url, local_state_,
                                              profile_prefs_);
}

mojom::FingerprintMode QoraiShieldsSettingsService::GetFingerprintMode(
    const GURL& url) {
  ControlType control_type = qorai_shields::GetFingerprintingControlType(
      &*host_content_settings_map_, url);

  if (control_type == ControlType::ALLOW) {
    return mojom::FingerprintMode::ALLOW_MODE;
  } else if (control_type == ControlType::BLOCK) {
#if BUILDFLAG(IS_IOS)
    /// Strict FingerprintMode is not supported on iOS.
    /// In case of sync'd setting, return standard mode.
    return mojom::FingerprintMode::STANDARD_MODE;
#else
    return mojom::FingerprintMode::STRICT_MODE;
#endif
  } else {
    return mojom::FingerprintMode::STANDARD_MODE;
  }
}

void QoraiShieldsSettingsService::SetNoScriptEnabledByDefault(bool is_enabled) {
  SetNoScriptEnabled(is_enabled, GURL());
}

bool QoraiShieldsSettingsService::IsNoScriptEnabledByDefault() {
  return IsNoScriptEnabled(GURL());
}

void QoraiShieldsSettingsService::SetNoScriptEnabled(bool is_enabled,
                                                     const GURL& url) {
  ControlType control_type =
      is_enabled ? ControlType::BLOCK : ControlType::ALLOW;
  qorai_shields::SetNoScriptControlType(&*host_content_settings_map_,
                                        control_type, url, local_state_);
}

bool QoraiShieldsSettingsService::IsNoScriptEnabled(const GURL& url) {
  ControlType control_type =
      qorai_shields::GetNoScriptControlType(&*host_content_settings_map_, url);

  return control_type != ControlType::ALLOW;
}

#if !BUILDFLAG(IS_IOS)
bool QoraiShieldsSettingsService::GetForgetFirstPartyStorageEnabled(
    const GURL& url) {
  ContentSetting setting = host_content_settings_map_->GetContentSetting(
      url, url, ContentSettingsType::QORAI_REMEMBER_1P_STORAGE);

  return setting == CONTENT_SETTING_BLOCK;
}

void QoraiShieldsSettingsService::SetForgetFirstPartyStorageEnabled(
    bool is_enabled,
    const GURL& url) {
  auto primary_pattern = content_settings::CreateDomainPattern(url);

  if (!primary_pattern.IsValid()) {
    return;
  }

  host_content_settings_map_->SetContentSettingCustomScope(
      primary_pattern, ContentSettingsPattern::Wildcard(),
      ContentSettingsType::QORAI_REMEMBER_1P_STORAGE,
      is_enabled ? CONTENT_SETTING_BLOCK : CONTENT_SETTING_ALLOW);

  MaybeRecordShieldsUsageP3A(kChangedPerSiteShields, local_state_);
  RecordForgetFirstPartySetting(&*host_content_settings_map_);
}
#endif

void QoraiShieldsSettingsService::SetDefaultAutoShredMode(
    mojom::AutoShredMode mode) {
  SetAutoShredMode(mode, GURL());
}

mojom::AutoShredMode QoraiShieldsSettingsService::GetDefaultAutoShredMode() {
  return GetAutoShredMode(GURL());
}

void QoraiShieldsSettingsService::SetAutoShredMode(mojom::AutoShredMode mode,
                                                   const GURL& url) {
  // Shred and AutoShred delete data at the eTLD+1 boundary, because that’s
  // the Web’s cookie boundary, so we must use the domain pattern to align
  // with how browsers enforce storage boundaries.
  auto primary_pattern = content_settings::CreateDomainPattern(url);

  if (!primary_pattern.IsValid()) {
    return;
  }

  host_content_settings_map_->SetWebsiteSettingCustomScope(
      primary_pattern, ContentSettingsPattern::Wildcard(),
      AutoShredSetting::kContentSettingsType, AutoShredSetting::ToValue(mode));
}

mojom::AutoShredMode QoraiShieldsSettingsService::GetAutoShredMode(
    const GURL& url) {
  return AutoShredSetting::FromValue(
      host_content_settings_map_->GetWebsiteSetting(
          url, GURL(), AutoShredSetting::kContentSettingsType));
}

bool QoraiShieldsSettingsService::IsJsBlockingEnforced(const GURL& url) {
  const auto js_content_settings_overridden_data =
      GetJsContentSettingOverriddenData(url);
  return js_content_settings_overridden_data &&
         js_content_settings_overridden_data->status ==
             ::ContentSetting::CONTENT_SETTING_BLOCK;
}

mojom::ContentSettingsOverriddenDataPtr
QoraiShieldsSettingsService::GetJsContentSettingOverriddenData(
    const GURL& url) {
  content_settings::SettingInfo info;
  const auto rule = host_content_settings_map_->GetContentSetting(
      url, GURL(), content_settings::mojom::ContentSettingsType::JAVASCRIPT,
      &info);

  // No override
  if (info.source == content_settings::SettingSource::kUser) {
    return nullptr;
  }

  return mojom::ContentSettingsOverriddenData::New(
      rule, ConvertSettingsSource(info.source));
}

}  // namespace qorai_shields
