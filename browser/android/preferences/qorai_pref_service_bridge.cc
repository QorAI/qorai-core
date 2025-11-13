/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <jni.h>

#include <string>

#include "base/android/jni_string.h"
#include "qorai/build/android/jni_headers/QoraiPrefServiceBridge_jni.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_perf_predictor/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/qorai_sync/qorai_sync_prefs.h"
#include "qorai/components/constants/pref_names.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/cookie_settings_factory.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/common/pref_names.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/prefs/pref_service.h"
#include "third_party/blink/public/common/peerconnection/webrtc_ip_handling_policy.h"
#include "url/gurl.h"

using base::android::ConvertUTF8ToJavaString;
using base::android::JavaParamRef;
using base::android::ScopedJavaLocalRef;
using qorai_shields::ControlType;

namespace {

Profile* GetOriginalProfile() {
  return ProfileManager::GetActiveUserProfile()->GetOriginalProfile();
}

enum WebRTCIPHandlingPolicy {
  DEFAULT,
  DEFAULT_PUBLIC_AND_PRIVATE_INTERFACES,
  DEFAULT_PUBLIC_INTERFACE_ONLY,
  DISABLE_NON_PROXIED_UDP,
};

WebRTCIPHandlingPolicy GetWebRTCIPHandlingPolicy(
    const std::string& preference) {
  if (preference == blink::kWebRTCIPHandlingDefaultPublicAndPrivateInterfaces)
    return DEFAULT_PUBLIC_AND_PRIVATE_INTERFACES;
  if (preference == blink::kWebRTCIPHandlingDefaultPublicInterfaceOnly)
    return DEFAULT_PUBLIC_INTERFACE_ONLY;
  if (preference == blink::kWebRTCIPHandlingDisableNonProxiedUdp)
    return DISABLE_NON_PROXIED_UDP;
  return DEFAULT;
}

std::string GetWebRTCIPHandlingPreference(WebRTCIPHandlingPolicy policy) {
  if (policy == DEFAULT_PUBLIC_AND_PRIVATE_INTERFACES)
    return blink::kWebRTCIPHandlingDefaultPublicAndPrivateInterfaces;
  if (policy == DEFAULT_PUBLIC_INTERFACE_ONLY)
    return blink::kWebRTCIPHandlingDefaultPublicInterfaceOnly;
  if (policy == DISABLE_NON_PROXIED_UDP)
    return blink::kWebRTCIPHandlingDisableNonProxiedUdp;
  return blink::kWebRTCIPHandlingDefault;
}

}  // namespace

namespace chrome {
namespace android {

// This file is deprecated, prefs should be accessed directly from Java
void JNI_QoraiPrefServiceBridge_SetCookiesBlockType(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type) {
  qorai_shields::SetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(GetOriginalProfile()),
      GetOriginalProfile()->GetPrefs(),
      qorai_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(), g_browser_process->local_state());
}

base::android::ScopedJavaLocalRef<jstring>
JNI_QoraiPrefServiceBridge_GetCookiesBlockType(JNIEnv* env) {
  qorai_shields::ControlType control_type = qorai_shields::GetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(GetOriginalProfile()),
      CookieSettingsFactory::GetForProfile(GetOriginalProfile()).get(), GURL());
  return base::android::ConvertUTF8ToJavaString(
      env, qorai_shields::ControlTypeToString(control_type));
}

void JNI_QoraiPrefServiceBridge_SetPlayYTVideoInBrowserEnabled(
    JNIEnv* env,
    jboolean enabled) {
  return GetOriginalProfile()->GetPrefs()->SetBoolean(
      kPlayYTVideoInBrowserEnabled, enabled);
}

jboolean JNI_QoraiPrefServiceBridge_GetPlayYTVideoInBrowserEnabled(
    JNIEnv* env) {
  return GetOriginalProfile()->GetPrefs()->GetBoolean(
      kPlayYTVideoInBrowserEnabled);
}

void JNI_QoraiPrefServiceBridge_SetDesktopModeEnabled(JNIEnv* env,
                                                      jboolean enabled) {
  return GetOriginalProfile()->GetPrefs()->SetBoolean(kDesktopModeEnabled,
                                                      enabled);
}

jboolean JNI_QoraiPrefServiceBridge_GetDesktopModeEnabled(JNIEnv* env) {
  return GetOriginalProfile()->GetPrefs()->GetBoolean(kDesktopModeEnabled);
}

jlong JNI_QoraiPrefServiceBridge_GetTrackersBlockedCount(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile) {
  Profile* profile = Profile::FromJavaObject(j_profile);
  return profile->GetPrefs()->GetUint64(kTrackersBlocked);
}

jlong JNI_QoraiPrefServiceBridge_GetAdsBlockedCount(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile) {
  Profile* profile = Profile::FromJavaObject(j_profile);
  return profile->GetPrefs()->GetUint64(kAdsBlocked);
}

jlong JNI_QoraiPrefServiceBridge_GetDataSaved(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile) {
  Profile* profile = Profile::FromJavaObject(j_profile);
  return profile->GetPrefs()->GetUint64(
      qorai_perf_predictor::prefs::kBandwidthSavedBytes);
}

void JNI_QoraiPrefServiceBridge_SetOldTrackersBlockedCount(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile,
    jlong count) {
  if (count <= 0) {
    return;
  }
  Profile* profile = Profile::FromJavaObject(j_profile);
  profile->GetPrefs()->SetUint64(
      kTrackersBlocked,
      count + profile->GetPrefs()->GetUint64(kTrackersBlocked));
}

void JNI_QoraiPrefServiceBridge_SetOldAdsBlockedCount(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile,
    jlong count) {
  if (count <= 0) {
    return;
  }
  Profile* profile = Profile::FromJavaObject(j_profile);
  profile->GetPrefs()->SetUint64(
      kAdsBlocked, count + profile->GetPrefs()->GetUint64(kAdsBlocked));
}

void JNI_QoraiPrefServiceBridge_SetOldHttpsUpgradesCount(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile,
    jlong count) {
  if (count <= 0) {
    return;
  }
  Profile* profile = Profile::FromJavaObject(j_profile);
  profile->GetPrefs()->SetUint64(
      kHttpsUpgrades, count + profile->GetPrefs()->GetUint64(kHttpsUpgrades));
}

void JNI_QoraiPrefServiceBridge_ResetPromotionLastFetchStamp(JNIEnv* env) {
  GetOriginalProfile()->GetPrefs()->SetUint64(
      qorai_rewards::prefs::kPromotionLastFetchStamp, 0);
}

jboolean JNI_QoraiPrefServiceBridge_GetBooleanForContentSetting(JNIEnv* env,
                                                                jint type) {
  HostContentSettingsMap* content_settings =
      HostContentSettingsMapFactory::GetForProfile(GetOriginalProfile());
  switch (content_settings->GetDefaultContentSetting((ContentSettingsType)type,
                                                     nullptr)) {
    case CONTENT_SETTING_ALLOW:
      return true;
    case CONTENT_SETTING_BLOCK:
    default:
      return false;
  }
}

jint JNI_QoraiPrefServiceBridge_GetWebrtcPolicy(JNIEnv* env) {
  return static_cast<int>(
      GetWebRTCIPHandlingPolicy(GetOriginalProfile()->GetPrefs()->GetString(
          prefs::kWebRTCIPHandlingPolicy)));
}

void JNI_QoraiPrefServiceBridge_SetWebrtcPolicy(JNIEnv* env, jint policy) {
  GetOriginalProfile()->GetPrefs()->SetString(
      prefs::kWebRTCIPHandlingPolicy,
      GetWebRTCIPHandlingPreference((WebRTCIPHandlingPolicy)policy));
}

void JNI_QoraiPrefServiceBridge_SetNewsOptIn(JNIEnv* env, jboolean value) {
  GetOriginalProfile()->GetPrefs()->SetBoolean(
      qorai_news::prefs::kQoraiNewsOptedIn, value);
}

jboolean JNI_QoraiPrefServiceBridge_GetNewsOptIn(JNIEnv* env) {
  return GetOriginalProfile()->GetPrefs()->GetBoolean(
      qorai_news::prefs::kQoraiNewsOptedIn);
}

void JNI_QoraiPrefServiceBridge_SetShowNews(JNIEnv* env, jboolean value) {
  GetOriginalProfile()->GetPrefs()->SetBoolean(
      qorai_news::prefs::kNewTabPageShowToday, value);
}

jboolean JNI_QoraiPrefServiceBridge_GetShowNews(JNIEnv* env) {
  return GetOriginalProfile()->GetPrefs()->GetBoolean(
      qorai_news::prefs::kNewTabPageShowToday);
}

}  // namespace android
}  // namespace chrome
