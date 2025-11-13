/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/default_qorai_shields_handler.h"

#include <utility>
#include <vector>

#include "base/check.h"
#include "base/check_op.h"
#include "base/functional/bind.h"
#include "base/values.h"
#include "qorai/browser/qorai_shields/qorai_shields_settings_service_factory.h"
#include "qorai/browser/webcompat_reporter/webcompat_reporter_service_factory.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_settings_service.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/qorai_shields/core/common/qorai_shields_settings_values.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/webcompat_reporter/browser/webcompat_reporter_service.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/cookie_settings_factory.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "content/public/browser/web_ui.h"
#include "url/gurl.h"

using qorai_shields::ControlType;
using qorai_shields::ControlTypeFromString;
using qorai_shields::ControlTypeToString;

DefaultQoraiShieldsHandler::DefaultQoraiShieldsHandler() = default;
DefaultQoraiShieldsHandler::~DefaultQoraiShieldsHandler() = default;

void DefaultQoraiShieldsHandler::RegisterMessages() {
  profile_ = Profile::FromWebUI(web_ui());
  qorai_shields_settings_ =
      QoraiShieldsSettingsServiceFactory::GetForProfile(profile_);
  web_ui()->RegisterMessageCallback(
      "isAdControlEnabled",
      base::BindRepeating(&DefaultQoraiShieldsHandler::IsAdControlEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setAdControlType",
      base::BindRepeating(&DefaultQoraiShieldsHandler::SetAdControlType,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isFirstPartyCosmeticFilteringEnabled",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::IsFirstPartyCosmeticFilteringEnabled,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setCosmeticFilteringControlType",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::SetCosmeticFilteringControlType,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getCookieControlType",
      base::BindRepeating(&DefaultQoraiShieldsHandler::GetCookieControlType,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setCookieControlType",
      base::BindRepeating(&DefaultQoraiShieldsHandler::SetCookieControlType,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getFingerprintingControlType",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::GetFingerprintingControlType,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setFingerprintingControlType",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::SetFingerprintingControlType,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getFingerprintingBlockEnabled",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::GetFingerprintingBlockEnabled,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setFingerprintingBlockEnabled",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::SetFingerprintingBlockEnabled,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getHttpsUpgradeControlType",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::GetHttpsUpgradeControlType,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setHttpsUpgradeControlType",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::SetHttpsUpgradeControlType,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getNoScriptControlType",
      base::BindRepeating(&DefaultQoraiShieldsHandler::GetNoScriptControlType,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setNoScriptControlType",
      base::BindRepeating(&DefaultQoraiShieldsHandler::SetNoScriptControlType,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getForgetFirstPartyStorageEnabled",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::GetForgetFirstPartyStorageEnabled,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setForgetFirstPartyStorageEnabled",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::SetForgetFirstPartyStorageEnabled,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setContactInfoSaveFlag",
      base::BindRepeating(&DefaultQoraiShieldsHandler::SetContactInfoSaveFlag,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getContactInfo",
      base::BindRepeating(&DefaultQoraiShieldsHandler::GetContactInfo,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getHideBlockAllCookieTogle",
      base::BindRepeating(
          &DefaultQoraiShieldsHandler::GetHideBlockAllCookieFlag,
          base::Unretained(this)));

  content_settings_observation_.Observe(
      HostContentSettingsMapFactory::GetForProfile(profile_));
  cookie_settings_observation_.Observe(
      CookieSettingsFactory::GetForProfile(profile_).get());
}

void DefaultQoraiShieldsHandler::OnContentSettingChanged(
    const ContentSettingsPattern& primary_pattern,
    const ContentSettingsPattern& secondary_pattern,
    ContentSettingsTypeSet content_type_set) {
  if (!content_type_set.Contains(ContentSettingsType::COOKIES) &&
      !content_type_set.Contains(
          ContentSettingsType::QORAI_COSMETIC_FILTERING) &&
      !content_type_set.Contains(ContentSettingsType::QORAI_TRACKERS) &&
      !content_type_set.Contains(
          ContentSettingsType::QORAI_HTTP_UPGRADABLE_RESOURCES) &&
      !content_type_set.Contains(
          ContentSettingsType::QORAI_FINGERPRINTING_V2) &&
      !content_type_set.Contains(ContentSettingsType::QORAI_SHIELDS) &&
      !content_type_set.Contains(ContentSettingsType::QORAI_HTTPS_UPGRADE) &&
      !content_type_set.Contains(
          ContentSettingsType::QORAI_REMEMBER_1P_STORAGE)) {
    return;
  }

  if (primary_pattern != ContentSettingsPattern::Wildcard() &&
      secondary_pattern != ContentSettingsPattern::Wildcard()) {
    return;
  }

  if (!IsJavascriptAllowed()) {
    return;
  }
  FireWebUIListener("qorai-shields-settings-changed");
}

void DefaultQoraiShieldsHandler::OnThirdPartyCookieBlockingChanged(
    bool block_third_party_cookies) {
  if (!IsJavascriptAllowed()) {
    return;
  }
  FireWebUIListener("qorai-shields-settings-changed");
}

void DefaultQoraiShieldsHandler::IsAdControlEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);

  ControlType setting = qorai_shields::GetAdControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_), GURL());

  AllowJavascript();
  ResolveJavascriptCallback(args[0],
                            base::Value(setting == ControlType::BLOCK));
}

void DefaultQoraiShieldsHandler::SetAdControlType(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  bool value = args[0].GetBool();

  qorai_shields::SetAdControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      value ? ControlType::BLOCK : ControlType::ALLOW, GURL(),
      g_browser_process->local_state());
}

void DefaultQoraiShieldsHandler::IsFirstPartyCosmeticFilteringEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);

  bool enabled = qorai_shields::IsFirstPartyCosmeticFilteringEnabled(
      HostContentSettingsMapFactory::GetForProfile(profile_), GURL());

  AllowJavascript();
  ResolveJavascriptCallback(args[0], base::Value(enabled));
}

void DefaultQoraiShieldsHandler::SetCosmeticFilteringControlType(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  std::string value = args[0].GetString();

  qorai_shields::SetCosmeticFilteringControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      ControlTypeFromString(value), GURL(), g_browser_process->local_state(),
      profile_->GetPrefs());
}

void DefaultQoraiShieldsHandler::GetCookieControlType(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);

  const ControlType setting = qorai_shields::GetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      CookieSettingsFactory::GetForProfile(profile_).get(), GURL());

  AllowJavascript();
  ResolveJavascriptCallback(args[0], base::Value(ControlTypeToString(setting)));
}

void DefaultQoraiShieldsHandler::GetHideBlockAllCookieFlag(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  const ControlType setting = qorai_shields::GetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      CookieSettingsFactory::GetForProfile(profile_).get(), GURL());

  const bool block_all_cookies_feature_enabled = base::FeatureList::IsEnabled(
      qorai_shields::features::kBlockAllCookiesToggle);

  AllowJavascript();
  ResolveJavascriptCallback(args[0],
                            base::Value(setting != ControlType::BLOCK &&
                                        !block_all_cookies_feature_enabled));
}

void DefaultQoraiShieldsHandler::SetCookieControlType(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  std::string value = args[0].GetString();

  qorai_shields::SetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      profile_->GetPrefs(), ControlTypeFromString(value), GURL(),
      g_browser_process->local_state());
}

void DefaultQoraiShieldsHandler::GetFingerprintingControlType(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);

  ControlType setting = qorai_shields::GetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_), GURL());

  AllowJavascript();
  ResolveJavascriptCallback(args[0], base::Value(ControlTypeToString(setting)));
}

void DefaultQoraiShieldsHandler::SetFingerprintingControlType(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  std::string value = args[0].GetString();

  qorai_shields::SetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      ControlTypeFromString(value), GURL(), g_browser_process->local_state(),
      profile_->GetPrefs());
}

void DefaultQoraiShieldsHandler::GetFingerprintingBlockEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);

  ControlType setting = qorai_shields::GetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_), GURL());
  bool result = setting != ControlType::ALLOW;
  AllowJavascript();
  ResolveJavascriptCallback(args[0], base::Value(result));
}

void DefaultQoraiShieldsHandler::SetFingerprintingBlockEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  bool value = args[0].GetBool();

  qorai_shields::SetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      value ? ControlType::DEFAULT : ControlType::ALLOW, GURL(),
      g_browser_process->local_state());
}

void DefaultQoraiShieldsHandler::GetHttpsUpgradeControlType(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);

  ControlType setting = qorai_shields::GetHttpsUpgradeControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_), GURL());

  AllowJavascript();
  ResolveJavascriptCallback(args[0], base::Value(ControlTypeToString(setting)));
}

void DefaultQoraiShieldsHandler::SetHttpsUpgradeControlType(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  std::string value = args[0].GetString();

  qorai_shields::SetHttpsUpgradeControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      ControlTypeFromString(value), GURL(), g_browser_process->local_state());
}

void DefaultQoraiShieldsHandler::GetNoScriptControlType(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  ControlType setting = qorai_shields::GetNoScriptControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_), GURL());

  AllowJavascript();
  ResolveJavascriptCallback(args[0],
                            base::Value(setting != ControlType::ALLOW));
}

void DefaultQoraiShieldsHandler::SetNoScriptControlType(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  bool value = args[0].GetBool();

  qorai_shields::SetNoScriptControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      value ? ControlType::BLOCK : ControlType::ALLOW, GURL(),
      g_browser_process->local_state());
}

void DefaultQoraiShieldsHandler::SetContactInfoSaveFlag(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  if (!args[0].is_bool()) {
    return;
  }
  bool value = args[0].GetBool();

  auto* webcompat_reporter_service =
      webcompat_reporter::WebcompatReporterServiceFactory::GetServiceForContext(
          profile_);
  if (webcompat_reporter_service) {
    webcompat_reporter_service->SetContactInfoSaveFlag(value);
  }
}

void DefaultQoraiShieldsHandler::GetContactInfo(const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);
  AllowJavascript();

  auto* webcompat_reporter_service =
      webcompat_reporter::WebcompatReporterServiceFactory::GetServiceForContext(
          profile_);
  if (!webcompat_reporter_service) {
    base::Value::Dict params_dict;
    params_dict.Set("contactInfo", "");
    params_dict.Set("contactInfoSaveFlag", false);
    ResolveJavascriptCallback(args[0], std::move(params_dict));
    return;
  }

  webcompat_reporter_service->GetBrowserParams(
      base::BindOnce(&DefaultQoraiShieldsHandler::OnGetContactInfo,
                     weak_ptr_factory_.GetWeakPtr(), args[0].Clone()));
}
void DefaultQoraiShieldsHandler::OnGetContactInfo(
    base::Value javascript_callback,
    const std::optional<std::string>& contact_info,
    const bool contact_info_save_flag,
    const std::vector<std::string>& components) {
  base::Value::Dict params_dict;
  params_dict.Set("contactInfo", contact_info.value_or(""));
  params_dict.Set("contactInfoSaveFlag", contact_info_save_flag);
  ResolveJavascriptCallback(javascript_callback, std::move(params_dict));
}

void DefaultQoraiShieldsHandler::SetForgetFirstPartyStorageEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);

  bool value = args[0].GetBool();

  qorai_shields_settings_->SetForgetFirstPartyStorageEnabled(value, GURL());
}

void DefaultQoraiShieldsHandler::GetForgetFirstPartyStorageEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  CHECK(profile_);

  const bool result =
      qorai_shields_settings_->GetForgetFirstPartyStorageEnabled(GURL());

  AllowJavascript();
  ResolveJavascriptCallback(args[0], base::Value(result));
}
