/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/webui/settings/site_settings_helper.h"

#include <string_view>
#include <vector>

#include "qorai/browser/qorai_wallet/qorai_wallet_context_utils.h"
#include "qorai/components/qorai_shields/core/common/qorai_shield_constants.h"
#include "qorai/components/content_settings/core/browser/qorai_content_settings_pref_provider.h"
#include "components/content_settings/core/common/content_settings_pattern.h"

#define HasRegisteredGroupName HasRegisteredGroupName_ChromiumImpl
#define GetVisiblePermissionCategories \
  GetVisiblePermissionCategories_ChromiumImpl

// clang-format off
#define QORAI_CONTENT_SETTINGS_TYPE_GROUP_NAMES_LIST                  \
  {ContentSettingsType::QORAI_ADS, nullptr},                          \
  {ContentSettingsType::QORAI_COSMETIC_FILTERING, nullptr},           \
  {ContentSettingsType::QORAI_TRACKERS, nullptr},                     \
  {ContentSettingsType::QORAI_HTTP_UPGRADABLE_RESOURCES, nullptr},    \
  {ContentSettingsType::QORAI_FINGERPRINTING_V2, nullptr},            \
  {ContentSettingsType::QORAI_SHIELDS, qorai_shields::kQoraiShields}, \
  {ContentSettingsType::QORAI_REFERRERS, nullptr},                    \
  {ContentSettingsType::QORAI_COOKIES, nullptr},                      \
  {ContentSettingsType::QORAI_SPEEDREADER, nullptr},                  \
  {ContentSettingsType::QORAI_ETHEREUM, "ethereum"},                  \
  {ContentSettingsType::QORAI_SOLANA, "solana"},                      \
  {ContentSettingsType::QORAI_GOOGLE_SIGN_IN, "googleSignIn"},        \
  {ContentSettingsType::QORAI_HTTPS_UPGRADE, nullptr},                \
  {ContentSettingsType::QORAI_REMEMBER_1P_STORAGE, nullptr},          \
  {ContentSettingsType::QORAI_LOCALHOST_ACCESS, "localhostAccess"},   \
  {ContentSettingsType::QORAI_OPEN_AI_CHAT, "qoraiOpenAIChat"},       \
  {ContentSettingsType::QORAI_AUTO_SHRED, nullptr},                   \
  {ContentSettingsType::QORAI_WEBCOMPAT_NONE, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_AUDIO, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_CANVAS, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_DEVICE_MEMORY, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_EVENT_SOURCE_POOL, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_FONT, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_HARDWARE_CONCURRENCY, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_KEYBOARD, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_LANGUAGE, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_MEDIA_DEVICES, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_PLUGINS, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_SCREEN, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_SPEECH_SYNTHESIS, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_USB_DEVICE_SERIAL_NUMBER, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_USER_AGENT, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_WEBGL, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_WEBGL2, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_WEB_SOCKETS_POOL, nullptr}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_ALL, nullptr}, \
  {ContentSettingsType::QORAI_SHIELDS_METADATA, nullptr}, \
  {ContentSettingsType::QORAI_CARDANO, "cardano"}, \
  {ContentSettingsType::QORAI_PSST, nullptr},
// clang-format on

#define QORAI_SITE_SETTINGS_HELPER_CONTENT_SETTINGS_TYPE_FROM_GROUP_NAME \
  if (name == "autoplay")                                                \
    return ContentSettingsType::AUTOPLAY;

#define QORAI_SITE_SETTINGS_HELPER_CONTENT_SETTINGS_TYPE_TO_GROUP_NAME \
  if (type == ContentSettingsType::AUTOPLAY)                           \
    return "autoplay";

#define QORAI_PROVIDER_TYPE_TO_SITE_SETTINGS_SOURCE \
  case ProviderType::kRemoteListProvider:           \
    return SiteSettingSource::kRemoteList;

#define QORAI_PROVIDER_TO_DEFAULT_SETTINGS_STRING \
  case ProviderType::kRemoteListProvider:         \
    return "remote_list";

#define QORAI_GET_EXCEPTION_FOR_PAGE                                  \
  QoraiGetExceptionForPage(content_type, profile, incognito, pattern, \
                           secondary_pattern, setting, exception);

#define kNumSources     \
  kRemoteList:          \
  return "remote-list"; \
  case SiteSettingSource::kNumSources

namespace {
// Forward declaration.
void QoraiGetExceptionForPage(ContentSettingsType type,
                              Profile* profile,
                              bool incognito,
                              const ContentSettingsPattern& pattern,
                              const ContentSettingsPattern& secondary_pattern,
                              const ContentSetting& setting,
                              base::Value::Dict& exception);
}  // namespace

#include <chrome/browser/ui/webui/settings/site_settings_helper.cc>

#undef kNumSources
#undef QORAI_PROVIDER_TYPE_TO_SITE_SETTINGS_SOURCE
#undef QORAI_PROVIDER_TO_DEFAULT_SETTINGS_STRING
#undef QORAI_CONTENT_SETTINGS_TYPE_GROUP_NAMES_LIST
#undef QORAI_SITE_SETTINGS_HELPER_CONTENT_SETTINGS_TYPE_FROM_GROUP_NAME
#undef QORAI_SITE_SETTINGS_HELPER_CONTENT_SETTINGS_TYPE_TO_GROUP_NAME
#undef GetVisiblePermissionCategories
#undef HasRegisteredGroupName
#undef QORAI_GET_EXCEPTION_FOR_PAGE

namespace site_settings {

bool HasRegisteredGroupName(ContentSettingsType type) {
  if (type == ContentSettingsType::AUTOPLAY) {
    return true;
  }
  if (type == ContentSettingsType::QORAI_GOOGLE_SIGN_IN) {
    return true;
  }
  if (type == ContentSettingsType::QORAI_LOCALHOST_ACCESS) {
    return true;
  }
  if (type == ContentSettingsType::QORAI_ETHEREUM) {
    return true;
  }
  if (type == ContentSettingsType::QORAI_SOLANA) {
    return true;
  }
  if (type == ContentSettingsType::QORAI_CARDANO) {
    return true;
  }
  if (type == ContentSettingsType::QORAI_SHIELDS) {
    return true;
  }
  return HasRegisteredGroupName_ChromiumImpl(type);
}

std::vector<ContentSettingsType> GetVisiblePermissionCategories(
    const std::string& origin,
    Profile* profile) {
  auto types = GetVisiblePermissionCategories_ChromiumImpl(origin, profile);

  // Add Qorai-specific content settings types
  types.push_back(ContentSettingsType::AUTOPLAY);
  types.push_back(ContentSettingsType::QORAI_GOOGLE_SIGN_IN);
  types.push_back(ContentSettingsType::QORAI_LOCALHOST_ACCESS);
  types.push_back(ContentSettingsType::QORAI_OPEN_AI_CHAT);

  // Only add Web3-related content settings if wallet is allowed
  if (qorai_wallet::IsAllowedForContext(profile)) {
    types.push_back(ContentSettingsType::QORAI_ETHEREUM);
    types.push_back(ContentSettingsType::QORAI_SOLANA);
    types.push_back(ContentSettingsType::QORAI_CARDANO);
  }

  return types;
}
}  // namespace site_settings

namespace {
void QoraiGetExceptionForPage(ContentSettingsType type,
                              Profile* profile,
                              bool incognito,
                              const ContentSettingsPattern& pattern,
                              const ContentSettingsPattern& secondary_pattern,
                              const ContentSetting& setting,
                              base::Value::Dict& exception) {
  constexpr char kQoraiCookieType[] = "qoraiCookieType";

  // Update the RawSiteException.qoraiCookieType declaration in
  // site_settings_prefs_browser_proxy.ts if you want to change or add values.
  constexpr char kShieldsDown[] = "shields down";
  constexpr char kShieldsSettings[] = "shields settings";
  constexpr char kGoogleSignIn[] = "google sign-in";

  if (type == ContentSettingsType::COOKIES) {
    auto* map = HostContentSettingsMapFactory::GetForProfile(profile);
    auto* provider = static_cast<content_settings::QoraiPrefProvider*>(
        map->GetPrefProvider());
    switch (provider->GetCookieType(pattern, secondary_pattern, setting,
                                    incognito)) {
      case content_settings::QoraiPrefProvider::CookieType::kRegularCookie:
        break;
      case content_settings::QoraiPrefProvider::CookieType::kShieldsDownCookie:
        exception.Set(kQoraiCookieType, kShieldsDown);
        break;
      case content_settings::QoraiPrefProvider::CookieType::
          kCustomShieldsCookie:
        exception.Set(kQoraiCookieType, kShieldsSettings);
        break;
      case content_settings::QoraiPrefProvider::CookieType::kGoogleSignInCookie:
        exception.Set(kQoraiCookieType, kGoogleSignIn);
        break;
    }
  }
}

}  // namespace
