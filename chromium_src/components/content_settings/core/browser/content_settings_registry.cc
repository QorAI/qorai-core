/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#define QORAI_INIT QoraiInit();
#include <components/content_settings/core/browser/content_settings_registry.cc>
#undef QORAI_INIT

#include "base/containers/fixed_flat_map.h"
#include "qorai/components/qorai_shields/core/common/qorai_shield_constants.h"
#include "qorai/components/qorai_shields/core/common/qorai_shields_settings_values.h"
#include "qorai/components/psst/buildflags/buildflags.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings.mojom.h"
#include "net/base/features.h"

#if BUILDFLAG(ENABLE_PSST)
#include "qorai/components/psst/common/constants.h"
#include "qorai/components/psst/common/features.h"
#endif  // BUILDFLAG(ENABLE_PSST)

namespace content_settings {

namespace {
using enum ContentSettingsType;
constexpr auto kSettingsNames =
    base::MakeFixedFlatMap<ContentSettingsType, const char*>({
        {QORAI_WEBCOMPAT_NONE, "qorai-webcompat-none"},
        {QORAI_WEBCOMPAT_AUDIO, "qorai-webcompat-audio"},
        {QORAI_WEBCOMPAT_CANVAS, "qorai-webcompat-canvas"},
        {QORAI_WEBCOMPAT_DEVICE_MEMORY, "qorai-webcompat-device-memory"},
        {QORAI_WEBCOMPAT_EVENT_SOURCE_POOL,
         "qorai-webcompat-event-source-pool"},
        {QORAI_WEBCOMPAT_FONT, "qorai-webcompat-font"},
        {QORAI_WEBCOMPAT_HARDWARE_CONCURRENCY,
         "qorai-webcompat-hardware-concurrency"},
        {QORAI_WEBCOMPAT_KEYBOARD, "qorai-webcompat-keyboard"},
        {QORAI_WEBCOMPAT_LANGUAGE, "qorai-webcompat-language"},
        {QORAI_WEBCOMPAT_MEDIA_DEVICES, "qorai-webcompat-media-devices"},
        {QORAI_WEBCOMPAT_PLUGINS, "qorai-webcompat-plugins"},
        {QORAI_WEBCOMPAT_SCREEN, "qorai-webcompat-screen"},
        {QORAI_WEBCOMPAT_SPEECH_SYNTHESIS, "qorai-webcompat-speech-synthesis"},
        {QORAI_WEBCOMPAT_USB_DEVICE_SERIAL_NUMBER,
         "qorai-webcompat-usb-device-serial-number"},
        {QORAI_WEBCOMPAT_USER_AGENT, "qorai-webcompat-user-agent"},
        {QORAI_WEBCOMPAT_WEBGL, "qorai-webcompat-webgl"},
        {QORAI_WEBCOMPAT_WEBGL2, "qorai-webcompat-webgl2"},
        {QORAI_WEBCOMPAT_WEB_SOCKETS_POOL, "qorai-webcompat-web-sockets-pool"},
    });
}  // namespace

void ContentSettingsRegistry::QoraiInit() {
  Register(ContentSettingsType::QORAI_ADS, qorai_shields::kAds,
           CONTENT_SETTING_BLOCK, WebsiteSettingsInfo::SYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/{CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID |
               WebsiteSettingsRegistry::PLATFORM_IOS,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  Register(ContentSettingsType::QORAI_TRACKERS, qorai_shields::kTrackers,
           CONTENT_SETTING_BLOCK, WebsiteSettingsInfo::SYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/{CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID |
               WebsiteSettingsRegistry::PLATFORM_IOS,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  Register(ContentSettingsType::QORAI_HTTPS_UPGRADE,
           qorai_shields::kHTTPSUpgrades, CONTENT_SETTING_ASK,
           WebsiteSettingsInfo::SYNCABLE, /*allowlisted_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_ASK, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IF_LESS_PERMISSIVE,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  Register(ContentSettingsType::QORAI_HTTP_UPGRADABLE_RESOURCES,
           qorai_shields::kHTTPUpgradableResources, CONTENT_SETTING_BLOCK,
           WebsiteSettingsInfo::SYNCABLE, /*allowlisted_schemes=*/{},
           /*valid_settings=*/{CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  Register(ContentSettingsType::QORAI_REFERRERS, qorai_shields::kReferrers,
           CONTENT_SETTING_BLOCK, WebsiteSettingsInfo::SYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/{CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  /* The default value for QORAI_COOKIES specified during registration isn't
   * important because the GetCookieControlType function identifies the default
   * by looking for a (*,*) pattern and uses the COOKIES value.
   * QORAI_COOKIES is registered with CONTENT_SETTING_ALLOW for consistency with
   * the COOKIES type. */
  Register(
      ContentSettingsType::QORAI_COOKIES, qorai_shields::kCookies,
      CONTENT_SETTING_ALLOW, WebsiteSettingsInfo::SYNCABLE,
      /*allowlisted_schemes=*/{kChromeUIScheme, kChromeDevToolsScheme},
      /*valid_settings=*/
      {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK},
      WebsiteSettingsInfo::REQUESTING_ORIGIN_WITH_TOP_ORIGIN_EXCEPTIONS_SCOPE,
      WebsiteSettingsRegistry::DESKTOP |
          WebsiteSettingsRegistry::PLATFORM_ANDROID,
      ContentSettingsInfo::INHERIT_IN_INCOGNITO,
      PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  Register(ContentSettingsType::QORAI_FINGERPRINTING_V2,
           qorai_shields::kFingerprintingV2, CONTENT_SETTING_ASK,
           WebsiteSettingsInfo::SYNCABLE, /*allowlisted_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK, CONTENT_SETTING_ASK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID |
               WebsiteSettingsRegistry::PLATFORM_IOS,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  Register(ContentSettingsType::QORAI_SHIELDS, qorai_shields::kQoraiShields,
           CONTENT_SETTING_ALLOW, WebsiteSettingsInfo::SYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/{CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID |
               WebsiteSettingsRegistry::PLATFORM_IOS,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  Register(ContentSettingsType::QORAI_SPEEDREADER, "qoraiSpeedreader",
           // CONTENT_SETTING_ASK is used because the default is to defer to
           // the "use when possible" pref which looks at heuristics to
           // determine if the site looks like "readable". This will not
           // actually trigger a permission request
           CONTENT_SETTING_ASK, WebsiteSettingsInfo::SYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK, CONTENT_SETTING_ASK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  // Add CONTENT_SETTING_ASK for autoplay
  // Note ASK has been deprecated, only keeping it for
  // DiscardObsoleteAutoplayAsk test case
  content_settings_info_.erase(ContentSettingsType::AUTOPLAY);
  permission_settings_registry_->Unregister(ContentSettingsType::AUTOPLAY);
  website_settings_registry_->Unregister(ContentSettingsType::AUTOPLAY);
  Register(ContentSettingsType::AUTOPLAY, "autoplay", CONTENT_SETTING_ALLOW,
           WebsiteSettingsInfo::UNSYNCABLE, /*allowlisted_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK, CONTENT_SETTING_ASK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  // Register ethereum default value as Ask.
  Register(ContentSettingsType::QORAI_ETHEREUM, "qorai_ethereum",
           CONTENT_SETTING_ASK, WebsiteSettingsInfo::UNSYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK, CONTENT_SETTING_ASK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IF_LESS_PERMISSIVE,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  // Register solana default value as Ask.
  Register(ContentSettingsType::QORAI_SOLANA, "qorai_solana",
           CONTENT_SETTING_ASK, WebsiteSettingsInfo::UNSYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK, CONTENT_SETTING_ASK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IF_LESS_PERMISSIVE,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  // Register cardano default value as Ask.
  Register(ContentSettingsType::QORAI_CARDANO, "qorai_cardano",
           CONTENT_SETTING_ASK, WebsiteSettingsInfo::UNSYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK, CONTENT_SETTING_ASK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IF_LESS_PERMISSIVE,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  // Register google sign in social media permission default value as Ask.
  // This is INHERIT_IN_INCOGNITO because it sets cookie rules, and cookies
  // are INHERIT_IN_INCOGNITO.
  // See https://github.com/qorai/qorai-core/pull/15330#discussion_r1049643580
  Register(ContentSettingsType::QORAI_GOOGLE_SIGN_IN, "qorai_google_sign_in",
           CONTENT_SETTING_ASK, WebsiteSettingsInfo::UNSYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK, CONTENT_SETTING_ASK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  Register(ContentSettingsType::QORAI_REMEMBER_1P_STORAGE,
           "qorai_remember_1p_storage",
           net::features::kQoraiForgetFirstPartyStorageByDefault.Get()
               ? CONTENT_SETTING_BLOCK
               : CONTENT_SETTING_ALLOW,
           WebsiteSettingsInfo::UNSYNCABLE, {},
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  // Register localhost permission default value as Ask.
  Register(ContentSettingsType::QORAI_LOCALHOST_ACCESS,
           "qorai_localhost_access", CONTENT_SETTING_ASK,
           WebsiteSettingsInfo::UNSYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK, CONTENT_SETTING_ASK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IF_LESS_PERMISSIVE,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  // Register AI chat permission default value as Ask.
  Register(ContentSettingsType::QORAI_OPEN_AI_CHAT, "qorai_open_ai_chat",
           CONTENT_SETTING_ASK, WebsiteSettingsInfo::UNSYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK, CONTENT_SETTING_ASK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IF_LESS_PERMISSIVE,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_ORIGINS_ONLY);

  // Disable background sync by default (qorai/qorai-browser#4709)
  content_settings_info_.erase(ContentSettingsType::BACKGROUND_SYNC);
  permission_settings_registry_->Unregister(
      ContentSettingsType::BACKGROUND_SYNC);
  website_settings_registry_->Unregister(ContentSettingsType::BACKGROUND_SYNC);
  Register(ContentSettingsType::BACKGROUND_SYNC, "background-sync",
           CONTENT_SETTING_BLOCK, WebsiteSettingsInfo::UNSYNCABLE,
           /*allowlisted_schemes=*/{},
           /*valid_settings=*/{CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_ORIGINS_ONLY);

  // Disable WebNFC by default
  content_settings_info_.erase(ContentSettingsType::NFC);
  permission_settings_registry_->Unregister(ContentSettingsType::NFC);
  website_settings_registry_->Unregister(ContentSettingsType::NFC);
  Register(ContentSettingsType::NFC, "nfc-devices", CONTENT_SETTING_BLOCK,
           WebsiteSettingsInfo::UNSYNCABLE, /*allowlisted_primary_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_ASK, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IF_LESS_PERMISSIVE,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_ORIGINS_ONLY);

  // Disable motion sensors by default (qorai/qorai-browser#4789)
  content_settings_info_.erase(ContentSettingsType::SENSORS);
  permission_settings_registry_->Unregister(ContentSettingsType::SENSORS);
  website_settings_registry_->Unregister(ContentSettingsType::SENSORS);
  Register(ContentSettingsType::SENSORS, "sensors", CONTENT_SETTING_BLOCK,
           WebsiteSettingsInfo::UNSYNCABLE, /*allowlisted_schemes=*/{},
           /*valid_settings=*/{CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::DESKTOP |
               WebsiteSettingsRegistry::PLATFORM_ANDROID,
           ContentSettingsInfo::INHERIT_IN_INCOGNITO,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  // Disable idle detection by default (we used to disable feature flag
  // kIdleDetection, but it went away in cr121).
  content_settings_info_.erase(ContentSettingsType::IDLE_DETECTION);
  permission_settings_registry_->Unregister(
      ContentSettingsType::IDLE_DETECTION);
  website_settings_registry_->Unregister(ContentSettingsType::IDLE_DETECTION);
  Register(ContentSettingsType::IDLE_DETECTION, "idle-detection",
           CONTENT_SETTING_BLOCK, WebsiteSettingsInfo::UNSYNCABLE,
           /*allowlisted_primary_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_ASK, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
           WebsiteSettingsRegistry::ALL_PLATFORMS,
           ContentSettingsInfo::INHERIT_IF_LESS_PERMISSIVE,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_ORIGINS_ONLY);

  // Disable storage access by default (we used to disable feature flag
  // kPermissionStorageAccessAPI, but it went away in cr124).
  content_settings_info_.erase(ContentSettingsType::STORAGE_ACCESS);
  permission_settings_registry_->Unregister(
      ContentSettingsType::STORAGE_ACCESS);
  website_settings_registry_->Unregister(ContentSettingsType::STORAGE_ACCESS);
  content_settings_info_.erase(ContentSettingsType::TOP_LEVEL_STORAGE_ACCESS);
  permission_settings_registry_->Unregister(
      ContentSettingsType::TOP_LEVEL_STORAGE_ACCESS);
  website_settings_registry_->Unregister(
      ContentSettingsType::TOP_LEVEL_STORAGE_ACCESS);
  Register(ContentSettingsType::STORAGE_ACCESS, "storage-access",
           CONTENT_SETTING_BLOCK, WebsiteSettingsInfo::UNSYNCABLE,
           /*allowlisted_primary_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_ASK, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::REQUESTING_AND_TOP_SCHEMEFUL_SITE_SCOPE,
           WebsiteSettingsRegistry::ALL_PLATFORMS,
           ContentSettingsInfo::INHERIT_IF_LESS_PERMISSIVE,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);
  Register(ContentSettingsType::TOP_LEVEL_STORAGE_ACCESS,
           "top-level-storage-access", CONTENT_SETTING_BLOCK,
           WebsiteSettingsInfo::UNSYNCABLE,
           /*allowlisted_primary_schemes=*/{},
           /*valid_settings=*/
           {CONTENT_SETTING_ALLOW, CONTENT_SETTING_ASK, CONTENT_SETTING_BLOCK},
           WebsiteSettingsInfo::REQUESTING_ORIGIN_AND_TOP_SCHEMEFUL_SITE_SCOPE,
           WebsiteSettingsRegistry::ALL_PLATFORMS,
           ContentSettingsInfo::INHERIT_IF_LESS_PERMISSIVE,
           PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);

  permission_settings_registry_->Unregister(ContentSettingsType::HTTP_ALLOWED);
  website_settings_registry_->Unregister(ContentSettingsType::HTTP_ALLOWED);
  website_settings_registry_->Register(
      ContentSettingsType::HTTP_ALLOWED, "http-allowed", base::Value(),
      WebsiteSettingsInfo::UNSYNCABLE, WebsiteSettingsInfo::NOT_LOSSY,
      WebsiteSettingsInfo::GENERIC_SINGLE_ORIGIN_SCOPE,
      WebsiteSettingsRegistry::DESKTOP |
          WebsiteSettingsRegistry::PLATFORM_ANDROID |
          WebsiteSettingsRegistry::PLATFORM_IOS,
      WebsiteSettingsInfo::DONT_INHERIT_IN_INCOGNITO);

  for (auto settings_type = ContentSettingsType::QORAI_WEBCOMPAT_NONE;
       settings_type != ContentSettingsType::QORAI_WEBCOMPAT_ALL;
       settings_type = static_cast<ContentSettingsType>(
           static_cast<int32_t>(settings_type) + 1)) {
    const auto match = kSettingsNames.find(settings_type);
    if (match != kSettingsNames.end()) {
      Register(
          settings_type, match->second, CONTENT_SETTING_BLOCK,
          WebsiteSettingsInfo::UNSYNCABLE, /*allowlisted_schemes=*/{},
          /*valid_settings=*/
          {CONTENT_SETTING_ALLOW, CONTENT_SETTING_BLOCK},
          WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
          WebsiteSettingsRegistry::DESKTOP |
              WebsiteSettingsRegistry::PLATFORM_ANDROID,
          ContentSettingsInfo::INHERIT_IN_INCOGNITO,
          PermissionSettingsInfo::EXCEPTIONS_ON_SECURE_AND_INSECURE_ORIGINS);
    }
  }

  website_settings_registry_->Register(
      ContentSettingsType::QORAI_SHIELDS_METADATA,
      qorai_shields::kQoraiShieldsMetadata, base::Value(),
      WebsiteSettingsInfo::UNSYNCABLE, WebsiteSettingsInfo::NOT_LOSSY,
      WebsiteSettingsInfo::REQUESTING_SCHEMEFUL_SITE_ONLY_SCOPE,
      WebsiteSettingsRegistry::DESKTOP |
          WebsiteSettingsRegistry::PLATFORM_ANDROID,
      WebsiteSettingsInfo::DONT_INHERIT_IN_INCOGNITO);

  website_settings_registry_->Register(
      ContentSettingsType::QORAI_COSMETIC_FILTERING,
      qorai_shields::kCosmeticFiltering,
      qorai_shields::CosmeticFilteringSetting::DefaultValue(),
      WebsiteSettingsInfo::SYNCABLE, WebsiteSettingsInfo::NOT_LOSSY,
      WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
      WebsiteSettingsRegistry::DESKTOP |
          WebsiteSettingsRegistry::PLATFORM_ANDROID |
          WebsiteSettingsRegistry::PLATFORM_IOS,
      WebsiteSettingsInfo::INHERIT_IN_INCOGNITO);

  website_settings_registry_->Register(
      ContentSettingsType::QORAI_AUTO_SHRED, qorai_shields::kQoraiAutoShred,
      qorai_shields::AutoShredSetting::DefaultValue(),
      WebsiteSettingsInfo::UNSYNCABLE, WebsiteSettingsInfo::NOT_LOSSY,
      WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
      WebsiteSettingsRegistry::DESKTOP |
          WebsiteSettingsRegistry::PLATFORM_ANDROID |
          WebsiteSettingsRegistry::PLATFORM_IOS,
      WebsiteSettingsInfo::INHERIT_IN_INCOGNITO);

#if BUILDFLAG(ENABLE_PSST)
  if (base::FeatureList::IsEnabled(psst::features::kEnablePsst)) {
    website_settings_registry_->Register(
        ContentSettingsType::QORAI_PSST, psst::kQoraiPsst, base::Value(),
        WebsiteSettingsInfo::UNSYNCABLE, WebsiteSettingsInfo::NOT_LOSSY,
        WebsiteSettingsInfo::TOP_ORIGIN_ONLY_SCOPE,
        WebsiteSettingsRegistry::DESKTOP |
            WebsiteSettingsRegistry::PLATFORM_ANDROID,
        WebsiteSettingsInfo::DONT_INHERIT_IN_INCOGNITO);
  }
#endif  // BUILDFLAG(ENABLE_PSST)
}

}  // namespace content_settings
